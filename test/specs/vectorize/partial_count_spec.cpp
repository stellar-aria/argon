#include "argon.hpp"
#include "argon/vectorize/for_each.hpp"
#include "argon/vectorize/interleaved.hpp"
#include "argon/vectorize/load.hpp"
#include "argon/vectorize/load_store.hpp"
#include "argon/vectorize/store.hpp"
#include "argon/vectorize/store_interleaved.hpp"
#include "cppspec.hpp"
#include <array>
#include <cstdint>
#include <span>
#include <vector>

// clang-format off

// Every partial count, 1 to lanes - 1, of every lane width: a partial vector moves in pieces (on NEON, the low
// doubleword at once when the count covers it, then lane by lane), so each count takes a different path.

template <typename T>
constexpr std::ptrdiff_t lanes_of = std::ptrdiff_t{Argon<T>::lanes};

template <typename T>
T value_at(std::ptrdiff_t i) { return static_cast<T>(i % 61 + 1); }

constexpr int sentinel = 99;

// for_each: d[i] += a[i], nothing written past n; the partial step's out-of-range lanes load as zero.
template <typename T>
void check_flat(auto& self) {
  constexpr auto L = lanes_of<T>;
  for (std::ptrdiff_t n = 0; n < 3 * L; ++n) {
    std::vector<T> a(n + L, T(sentinel)), d(n + L, T(sentinel));
    for (std::ptrdiff_t i = 0; i < n; ++i) { a[i] = value_at<T>(i); d[i] = value_at<T>(3 * i); }
    auto expected = d;
    for (std::ptrdiff_t i = 0; i < n; ++i) expected[i] = static_cast<T>(d[i] + a[i]);
    std::array<T, Argon<T>::lanes> partial{}, expected_partial{};
    for (std::ptrdiff_t i = n - n % L; i < n; ++i) expected_partial[i % L] = a[i];
    argon::vectorize::for_each<T>(n, [&](auto step) {
      const auto v = step.Load(a.data());
      if (step.count() < L) partial = v.to_array();
      step.Store(d.data(), step.Load(d.data()) + v);
    });
    expect(d).to_equal(expected);
    expect(partial).to_equal(expected_partial);
  }
}

// for_each with LoadWiden / StoreNarrow: out[i] = in[i] + 1 through lanes of the wider type W.
template <typename N, typename W>
void check_widen(auto& self) {
  constexpr auto L = lanes_of<W>;
  for (std::ptrdiff_t n = 0; n < 3 * L; ++n) {
    std::vector<N> in(n + L, N(sentinel)), out(n + L, N(sentinel));
    for (std::ptrdiff_t i = 0; i < n; ++i) in[i] = value_at<N>(i);
    auto expected = out;
    for (std::ptrdiff_t i = 0; i < n; ++i) expected[i] = static_cast<N>(in[i] + 1);
    argon::vectorize::for_each<W>(n, [&](auto step) {
      step.StoreNarrow(out.data(), step.LoadWiden(in.data()) + Argon<W>{W{1}});
    });
    expect(out).to_equal(expected);
  }
}

// Rotate each frame's channels, (c0, c1, ..., cS-1) -> (c1, ..., cS-1, c0), and add the channel index.
template <typename T, size_t S>
std::vector<T> rotated(const std::vector<T>& data, std::ptrdiff_t frames) {
  auto expected = data;
  for (std::ptrdiff_t f = 0; f < frames; ++f)
    for (size_t c = 0; c < S; ++c) expected[f * S + c] = static_cast<T>(data[f * S + (c + 1) % S] + T(c));
  return expected;
}

template <typename T, size_t S, typename Frame>
Frame rotate(const Frame& in) {
  Frame out;
  for (size_t c = 0; c < S; ++c) out[c] = in[(c + 1) % S] + Argon<T>{static_cast<T>(c)};
  return out;
}

// for_each_interleaved: rotate every frame, nothing written past the last; out-of-range lanes load as zero.
template <typename T, size_t S>
void check_interleaved(auto& self) {
  constexpr auto L = lanes_of<T>;
  for (std::ptrdiff_t frames = 0; frames < 3 * L; ++frames) {
    std::vector<T> data(frames * S + L * S, T(sentinel));
    for (std::ptrdiff_t i = 0; i < frames * std::ptrdiff_t{S}; ++i) data[i] = value_at<T>(i);
    const auto expected = rotated<T, S>(data, frames);
    std::array<std::array<T, Argon<T>::lanes>, S> partial{}, expected_partial{};
    for (std::ptrdiff_t f = frames - frames % L; f < frames; ++f)
      for (size_t c = 0; c < S; ++c) expected_partial[c][f % L] = data[f * S + c];
    argon::vectorize::for_each_interleaved<T, S>(frames, [&](auto step) {
      const auto in = step.Load(data.data());
      if (step.count() < L)
        for (size_t c = 0; c < S; ++c) partial[c] = in[c].to_array();
      step.Store(data.data(), rotate<T, S>(in));
    });
    expect(data).to_equal(expected);
    expect(partial).to_equal(expected_partial);
  }
}

// with_tail() views: load (zeroed out-of-range lanes), store and load_store (nothing written past n).
template <typename T>
void check_views(auto& self) {
  constexpr auto L = lanes_of<T>;
  for (std::ptrdiff_t n = 0; n < 3 * L; ++n) {
    std::vector<T> data(n + L, T(sentinel));
    for (std::ptrdiff_t i = 0; i < n; ++i) data[i] = value_at<T>(i);
    const std::span<T> range{data.data(), size_t(n)};

    std::array<T, Argon<T>::lanes> partial{}, expected_partial{};
    for (std::ptrdiff_t i = n - n % L; i < n; ++i) expected_partial[i % L] = data[i];
    for (auto p : argon::vectorize::load(range).with_tail())
      if (!p.full()) partial = p->to_array();
    expect(partial).to_equal(expected_partial);

    auto expected = data;
    for (std::ptrdiff_t i = 0; i < n; ++i) expected[i] = static_cast<T>(data[i] + 1);
    for (auto& p : argon::vectorize::load_store(range).with_tail()) *p = *p + Argon<T>{T{1}};
    expect(data).to_equal(expected);

    for (std::ptrdiff_t i = 0; i < n; ++i) expected[i] = T{5};
    for (auto& p : argon::vectorize::store(range).with_tail()) p = Argon<T>{T{5}};
    expect(data).to_equal(expected);
  }
}

// interleaved<S>().with_tail() and store_interleaved<S>().with_tail(): every partial frame count.
template <typename T, size_t S>
void check_interleaved_views(auto& self) {
  constexpr auto L = lanes_of<T>;
  for (std::ptrdiff_t frames = 0; frames < 3 * L; ++frames) {
    const std::ptrdiff_t n = frames * std::ptrdiff_t{S};
    std::vector<T> data(n + L * S, T(sentinel));
    for (std::ptrdiff_t i = 0; i < n; ++i) data[i] = value_at<T>(i);
    auto expected = rotated<T, S>(data, frames);
    for (auto& p : argon::vectorize::interleaved<S, T>(data.data(), size_t(n)).with_tail()) *p = rotate<T, S>(*p);
    expect(data).to_equal(expected);

    for (std::ptrdiff_t i = 0; i < n; ++i) expected[i] = static_cast<T>(i % std::ptrdiff_t{S} + 1);
    for (auto& p : argon::vectorize::store_interleaved<T, S>(std::span{data.data(), size_t(n)}).with_tail()) {
      std::array<Argon<T>, S> channels;
      for (size_t c = 0; c < S; ++c) channels[c] = Argon<T>{static_cast<T>(c + 1)};
      p = channels;
    }
    expect(data).to_equal(expected);
  }
}

auto describe_partial_counts = describe("every partial count", ${
  it("for_each, uint8", _{ check_flat<uint8_t>(self); });
  it("for_each, int16", _{ check_flat<int16_t>(self); });
  it("for_each, int32", _{ check_flat<int32_t>(self); });
  it("for_each, float", _{ check_flat<float>(self); });

  it("for_each widening int16 to int32", _{ check_widen<int16_t, int32_t>(self); });
  it("for_each widening uint8 to uint16", _{ check_widen<uint8_t, uint16_t>(self); });
  it("for_each widening int8 to int32", _{ check_widen<int8_t, int32_t>(self); });

  it("for_each_interleaved, stride 2, uint8", _{ check_interleaved<uint8_t, 2>(self); });
  it("for_each_interleaved, stride 2, int32", _{ check_interleaved<int32_t, 2>(self); });
  it("for_each_interleaved, stride 3, int16", _{ check_interleaved<int16_t, 3>(self); });
  it("for_each_interleaved, stride 3, float", _{ check_interleaved<float, 3>(self); });
  it("for_each_interleaved, stride 4, uint8", _{ check_interleaved<uint8_t, 4>(self); });
  it("for_each_interleaved, stride 4, int32", _{ check_interleaved<int32_t, 4>(self); });

  it("with_tail() views, uint8", _{ check_views<uint8_t>(self); });
  it("with_tail() views, int16", _{ check_views<int16_t>(self); });
  it("with_tail() views, int32", _{ check_views<int32_t>(self); });
  it("with_tail() views, float", _{ check_views<float>(self); });

  it("interleaved with_tail() views, stride 2, int16", _{ check_interleaved_views<int16_t, 2>(self); });
  it("interleaved with_tail() views, stride 3, uint8", _{ check_interleaved_views<uint8_t, 3>(self); });
  it("interleaved with_tail() views, stride 4, float", _{ check_interleaved_views<float, 4>(self); });
});

CPPSPEC_MAIN(describe_partial_counts);
