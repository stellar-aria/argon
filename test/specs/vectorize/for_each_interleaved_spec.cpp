#include "argon.hpp"
#include "argon/vectorize/for_each.hpp"
#include "cppspec.hpp"
#include <cstdint>
#include <vector>

// clang-format off

constexpr std::ptrdiff_t frame_counts[] = {0, 1, 3, 4, 5, 7, 8, 9, 15, 16, 17, 33};

// Rotate the channels of each frame (c0, c1, ..., cS-1) -> (c1, ..., cS-1, c0) and add the frame's channel index.
template <typename T, size_t S>
void check_rotate(auto& self) {
  for (auto frames : frame_counts) {
    const std::ptrdiff_t n = frames * std::ptrdiff_t{S};
    std::vector<T> data(n + 2 * S), expected;
    for (std::ptrdiff_t i = 0; i < std::ptrdiff_t(data.size()); ++i) data[i] = static_cast<T>(i % 97);
    expected = data;
    for (std::ptrdiff_t f = 0; f < frames; ++f)
      for (size_t c = 0; c < S; ++c) expected[f * S + c] = static_cast<T>(data[f * S + (c + 1) % S] + T(c));
    argon::vectorize::for_each_interleaved<T, S>(frames, [&](auto step) {
      auto in = step.Load(data.data());
      decltype(in) out;
      for (size_t c = 0; c < S; ++c) out[c] = in[(c + 1) % S] + Argon<T>{static_cast<T>(c)};
      step.Store(data.data(), out);
    });
    expect(data).to_equal(expected);
  }
}

auto describe_for_each_interleaved = describe("vectorize::for_each_interleaved", ${
  it("stride 2, int16", _{ check_rotate<int16_t, 2>(self); });
  it("stride 2, float", _{ check_rotate<float, 2>(self); });
  it("stride 3, uint8", _{ check_rotate<uint8_t, 3>(self); });
  it("stride 3, int32", _{ check_rotate<int32_t, 3>(self); });
  it("stride 4, uint16", _{ check_rotate<uint16_t, 4>(self); });
  it("stride 4, float", _{ check_rotate<float, 4>(self); });

  it("swaps stereo channels", _{
    std::vector<int16_t> stereo = {1, -1, 2, -2, 3, -3, 4, -4, 5, -5};
    argon::vectorize::for_each_interleaved<int16_t, 2>(5, [&](auto step) {
      auto [left, right] = step.Load(stereo.data());
      step.Store(stereo.data(), {right, left});
    });
    expect(stereo).to_equal(std::vector<int16_t>{-1, 1, -2, 2, -3, 3, -4, 4, -5, 5});
  });

  it("reports frame index and count", _{
    std::vector<std::ptrdiff_t> counts;
    argon::vectorize::for_each_interleaved<float, 3>(9, [&](auto step) { counts.push_back(step.count()); });
    expect(counts).to_equal(std::vector<std::ptrdiff_t>{4, 4, 1});
  });
});

CPPSPEC_MAIN(describe_for_each_interleaved);
