#include "argon.hpp"
#include "cppspec.hpp"
#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <limits>

// clang-format off

template <typename T>
std::array<T, Argon<T>::lanes> sample(int seed) {
  const T values[] = {T(3), std::numeric_limits<T>::max(), T(0), T(1), T(-1), T(std::numeric_limits<T>::max() / 3),
                      T(97), std::numeric_limits<T>::min()};
  std::array<T, Argon<T>::lanes> out{};
  for (size_t i = 0; i < out.size(); ++i) out[i] = values[(i * 3 + seed) % 8];
  return out;
}

template <typename T>
std::make_unsigned_t<T> magnitude(T x) {
  using U = std::make_unsigned_t<T>;
  return x < 0 ? static_cast<U>(U{0} - static_cast<U>(x)) : static_cast<U>(x);
}

template <typename T>
void check_reduce(auto& self) {
  auto in = sample<T>(0);
  auto v = Argon<T>::Load(in.data());
  expect(v.ReduceMax()).to_equal(*std::max_element(in.begin(), in.end()));
  expect(v.ReduceMin()).to_equal(*std::min_element(in.begin(), in.end()));
}

template <typename T>
void check_abs(auto& self) {
  using U = std::make_unsigned_t<T>;
  auto in = sample<T>(2);
  auto v = Argon<T>::Load(in.data());
  U max_mag = 0, min_mag = std::numeric_limits<U>::max();
  for (auto x : in) { max_mag = std::max(max_mag, magnitude(x)); min_mag = std::min(min_mag, magnitude(x)); }
  expect(v.ReduceMaxAbs()).to_equal(max_mag);
  expect(v.ReduceMinAbs()).to_equal(min_mag);
  expect(v.ReduceMaxAbs(std::numeric_limits<U>::max())).to_equal(std::numeric_limits<U>::max());
  expect(v.ReduceMinAbs(U{0})).to_equal(U{0});

  auto peak_in = sample<T>(5);
  std::array<U, Argon<T>::lanes> peak{}, expected_max{}, expected_min{};
  for (size_t i = 0; i < peak.size(); ++i) {
    peak[i] = magnitude(peak_in[i]);
    expected_max[i] = std::max(peak[i], magnitude(in[i]));
    expected_min[i] = std::min(peak[i], magnitude(in[i]));
  }
  auto p = Argon<U>::Load(peak.data());
  expect(p.MaxAbs(v).to_array()).to_equal(expected_max);
  expect(p.MinAbs(v).to_array()).to_equal(expected_min);
}

auto describe_reduce = describe("ReduceMax / ReduceMin", ${
  it("int8", _{ check_reduce<int8_t>(self); });
  it("uint8", _{ check_reduce<uint8_t>(self); });
  it("int16", _{ check_reduce<int16_t>(self); });
  it("uint16", _{ check_reduce<uint16_t>(self); });
  it("int32", _{ check_reduce<int32_t>(self); });
  it("uint32", _{ check_reduce<uint32_t>(self); });
});

auto describe_abs = describe("ReduceMaxAbs / ReduceMinAbs / MaxAbs / MinAbs", ${
  it("int8, including the magnitude of INT8_MIN", _{ check_abs<int8_t>(self); });
  it("int16", _{ check_abs<int16_t>(self); });
  it("int32", _{ check_abs<int32_t>(self); });
  it("tracks a running peak", _{
    auto peak = Argon<uint16_t>{0};
    peak = peak.MaxAbs(Argon<int16_t>{3, -7, 2, 0, -1, 5, 1, -32768});
    peak = peak.MaxAbs(Argon<int16_t>{-4, 6, 1, 9, 0, -5, 2, 1});
    expect(peak.to_array()).to_equal(std::array<uint16_t, 8>{4, 7, 2, 9, 1, 5, 2, 32768});
    expect(Argon<int16_t>{3, -7, 2, 0, -1, 5, 1, -32768}.ReduceMaxAbs()).to_equal(uint16_t{32768});
  });
});

CPPSPEC_MAIN(
  describe_reduce,
  describe_abs
);
