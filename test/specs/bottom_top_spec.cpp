#include "argon.hpp"
#include "cppspec.hpp"
#include <algorithm>
#include <array>
#include <cstdint>
#include <limits>

// clang-format off

// Scalar references for Helium's bottom/top (even/odd lane) widening and narrowing. Every platform must match them.

template <typename T>
using Wide = argon::helpers::NextLarger_t<T>;
template <typename T>
using Narrow = argon::helpers::NextSmaller_t<T>;

/// Lanes covering the type's extremes, zero, ±1 and some mid-range values.
template <typename T>
std::array<T, Argon<T>::lanes> sample(int seed) {
  constexpr size_t lanes = Argon<T>::lanes;
  const T values[] = {std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), T(0), T(1), T(-1),
                      T(std::numeric_limits<T>::max() / 3), T(std::numeric_limits<T>::min() / 5), T(97)};
  std::array<T, lanes> out{};
  for (size_t i = 0; i < lanes; ++i) out[i] = values[(i * 3 + seed) % 8];
  return out;
}

template <typename T>
auto widen_ref(const std::array<T, Argon<T>::lanes>& in, size_t parity) {
  std::array<Wide<T>, Argon<T>::lanes / 2> out{};
  for (size_t i = 0; i < out.size(); ++i) out[i] = static_cast<Wide<T>>(in[2 * i + parity]);
  return out;
}

/// What a narrow lane receives: the shifted (optionally rounded) wide value, optionally saturated, truncated.
template <typename W>
Narrow<W> narrow_ref(W w, int shift, bool round, bool saturate) {
  using N = Narrow<W>;
  int64_t v = static_cast<int64_t>(w);
  if constexpr (std::is_unsigned_v<W>) v = static_cast<int64_t>(static_cast<uint64_t>(w));
  if (round && shift > 0) v += int64_t{1} << (shift - 1);
  v >>= shift;  // arithmetic for signed W; the value is non-negative for unsigned W
  if (saturate) v = std::clamp<int64_t>(v, std::numeric_limits<N>::min(), std::numeric_limits<N>::max());
  return static_cast<N>(v);
}

template <typename W>
auto insert_ref(std::array<Narrow<W>, Argon<Narrow<W>>::lanes> dest, const std::array<W, Argon<W>::lanes>& wide,
                size_t parity, int shift, bool round, bool saturate) {
  for (size_t i = 0; i < wide.size(); ++i) dest[2 * i + parity] = narrow_ref(wide[i], shift, round, saturate);
  return dest;
}

template <typename T>
void check_widen(auto& self) {
  auto in = sample<T>(0);
  auto v = Argon<T>::Load(in.data());
  expect(v.WidenBottom().to_array()).to_equal(widen_ref(in, 0));
  expect(v.WidenTop().to_array()).to_equal(widen_ref(in, 1));
  auto shifted = widen_ref(in, 1);
  for (auto& x : shifted) x = static_cast<Wide<T>>(x << 3);
  expect(v.template ShiftLeftLongTop<3>().to_array()).to_equal(shifted);
}

template <typename T>
void check_multiply_long(auto& self) {
  auto a_in = sample<T>(0), b_in = sample<T>(5);
  auto a = Argon<T>::Load(a_in.data()), b = Argon<T>::Load(b_in.data());
  auto bottom = widen_ref(a_in, 0), top = widen_ref(a_in, 1);
  auto b_bottom = widen_ref(b_in, 0), b_top = widen_ref(b_in, 1);
  for (size_t i = 0; i < bottom.size(); ++i) {
    bottom[i] = static_cast<Wide<T>>(bottom[i] * b_bottom[i]);
    top[i] = static_cast<Wide<T>>(top[i] * b_top[i]);
  }
  expect(a.MultiplyLongBottom(b).to_array()).to_equal(bottom);
  expect(a.MultiplyLongTop(b).to_array()).to_equal(top);
}

template <typename W>
void check_narrow(auto& self) {
  using N = Narrow<W>;
  auto wide_in = sample<W>(2);
  auto dest_in = sample<N>(4);
  auto w = Argon<W>::Load(wide_in.data());
  auto d = Argon<N>::Load(dest_in.data());
  expect(w.NarrowBottom(d).to_array()).to_equal(insert_ref<W>(dest_in, wide_in, 0, 0, false, false));
  expect(w.NarrowTop(d).to_array()).to_equal(insert_ref<W>(dest_in, wide_in, 1, 0, false, false));
  expect(w.SaturateNarrowBottom(d).to_array()).to_equal(insert_ref<W>(dest_in, wide_in, 0, 0, false, true));
  expect(w.SaturateNarrowTop(d).to_array()).to_equal(insert_ref<W>(dest_in, wide_in, 1, 0, false, true));
  constexpr int n = 3;
  expect(w.template ShiftRightNarrowBottom<n>(d).to_array()).to_equal(insert_ref<W>(dest_in, wide_in, 0, n, false, false));
  expect(w.template ShiftRightNarrowTop<n>(d).to_array()).to_equal(insert_ref<W>(dest_in, wide_in, 1, n, false, false));
  expect(w.template ShiftRightRoundNarrowBottom<n>(d).to_array()).to_equal(insert_ref<W>(dest_in, wide_in, 0, n, true, false));
  expect(w.template ShiftRightRoundNarrowTop<n>(d).to_array()).to_equal(insert_ref<W>(dest_in, wide_in, 1, n, true, false));
  expect(w.template ShiftRightSaturateNarrowBottom<n>(d).to_array()).to_equal(insert_ref<W>(dest_in, wide_in, 0, n, false, true));
  expect(w.template ShiftRightSaturateNarrowTop<n>(d).to_array()).to_equal(insert_ref<W>(dest_in, wide_in, 1, n, false, true));
  expect(w.template ShiftRightRoundSaturateNarrowBottom<n>(d).to_array()).to_equal(insert_ref<W>(dest_in, wide_in, 0, n, true, true));
  expect(w.template ShiftRightRoundSaturateNarrowTop<n>(d).to_array()).to_equal(insert_ref<W>(dest_in, wide_in, 1, n, true, true));
}

template <typename T>
void check_round_trip(auto& self) {
  auto in = sample<T>(1);
  auto v = Argon<T>::Load(in.data());
  auto rebuilt = v.WidenTop().NarrowTop(v.WidenBottom().NarrowBottom(Argon<T>{T(0)}));
  expect(rebuilt.to_array()).to_equal(in);
}

auto describe_widen = describe("WidenBottom / WidenTop / ShiftLeftLong", ${
  it("widens int8 lanes", _{ check_widen<int8_t>(self); });
  it("widens uint8 lanes", _{ check_widen<uint8_t>(self); });
  it("widens int16 lanes", _{ check_widen<int16_t>(self); });
  it("widens uint16 lanes", _{ check_widen<uint16_t>(self); });
});

auto describe_multiply_long = describe("MultiplyLongBottom / MultiplyLongTop", ${
  it("multiplies int8 lanes", _{ check_multiply_long<int8_t>(self); });
  it("multiplies uint8 lanes", _{ check_multiply_long<uint8_t>(self); });
  it("multiplies int16 lanes", _{ check_multiply_long<int16_t>(self); });
  it("multiplies uint16 lanes", _{ check_multiply_long<uint16_t>(self); });
  it("multiplies int32 lanes into int64", _{ check_multiply_long<int32_t>(self); });
  it("multiplies uint32 lanes into uint64", _{ check_multiply_long<uint32_t>(self); });
});

auto describe_narrow = describe("Narrow{Bottom,Top} and the shifting / saturating forms", ${
  it("narrows int16 into int8", _{ check_narrow<int16_t>(self); });
  it("narrows uint16 into uint8", _{ check_narrow<uint16_t>(self); });
  it("narrows int32 into int16", _{ check_narrow<int32_t>(self); });
  it("narrows uint32 into uint16", _{ check_narrow<uint32_t>(self); });
});

auto describe_round_trip = describe("Widen then narrow", ${
  it("reassembles int8 lanes", _{ check_round_trip<int8_t>(self); });
  it("reassembles uint16 lanes", _{ check_round_trip<uint16_t>(self); });
});

CPPSPEC_MAIN(
  describe_widen,
  describe_multiply_long,
  describe_narrow,
  describe_round_trip
);
