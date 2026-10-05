#include "argon.hpp"
#include "cppspec.hpp"
#include <array>
#include <cstdint>
#include <limits>

// clang-format off

// Lanes 2i, 2i+1 are (re, im). Values are small integers so float results are exact on every platform, fused or not.

auto describe_add = describe("ComplexAddRotate90 / 270", ${
  it("adds i·b and −i·b to int32 pairs", _{
    auto a = Argon<int32_t>{1, 2, 10, 20};
    auto b = Argon<int32_t>{3, 4, -5, 6};
    expect(a.ComplexAddRotate90(b).to_array()).to_equal(std::array<int32_t, 4>{1 - 4, 2 + 3, 10 - 6, 20 - 5});
    expect(a.ComplexAddRotate270(b).to_array()).to_equal(std::array<int32_t, 4>{1 + 4, 2 - 3, 10 + 6, 20 + 5});
  });

  it("works on int16, uint8 and float pairs", _{
    auto a16 = Argon<int16_t>{1, 2, 3, 4, 5, 6, 7, 8};
    auto b16 = Argon<int16_t>{10, 20, 30, 40, 50, 60, 70, 80};
    expect(a16.ComplexAddRotate90(b16).to_array()).to_equal(std::array<int16_t, 8>{-19, 12, -37, 34, -55, 56, -73, 78});
    auto a8 = Argon<uint8_t>{100};
    auto b8 = Argon<uint8_t>{1};
    std::array<uint8_t, 16> expected{};
    for (size_t i = 0; i < 16; ++i) expected[i] = i % 2 ? 101 : 99;
    expect(a8.ComplexAddRotate90(b8).to_array()).to_equal(expected);
    auto af = Argon<float>{1.0f, 2.0f, 3.0f, 4.0f};
    auto bf = Argon<float>{0.5f, -1.0f, 2.0f, 0.0f};
    expect(af.ComplexAddRotate270(bf).to_array()).to_equal(std::array<float, 4>{0.0f, 1.5f, 3.0f, 2.0f});
  });

  it("halves without overflowing", _{
    constexpr int32_t big = std::numeric_limits<int32_t>::max();
    auto a = Argon<int32_t>{big, big, -big, 4};
    auto b = Argon<int32_t>{big, -big, 2, big};
    // re = (a.re ∓ b.im) / 2, im = (a.im ± b.re) / 2, rounded toward −∞ like vhadd/vhsub
    // pair 0 sums big + big, which only fits halved; pair 1: (−big − big)/2 = −big, (4 + 2)/2 = 3
    expect(a.ComplexAddRotate90Halve(b).to_array()).to_equal(std::array<int32_t, 4>{big, big, -big, 3});
    expect(a.ComplexAddRotate270Halve(b).to_array()).to_equal(std::array<int32_t, 4>{0, 0, 0, 1});
  });
});

auto describe_multiply = describe("Complex multiplication", ${
  it("multiplies pairs", _{
    // (1+2i)(3+4i) = −5+10i; (2−1i)(0+3i) = 3+6i
    auto a = Argon<float>{1.0f, 2.0f, 2.0f, -1.0f};
    auto b = Argon<float>{3.0f, 4.0f, 0.0f, 3.0f};
    expect(a.ComplexMultiply(b).to_array()).to_equal(std::array<float, 4>{-5.0f, 10.0f, 3.0f, 6.0f});
  });

  it("multiplies by the conjugate", _{
    // (1+2i)(3−4i) = 11+2i; (2−1i)(0−3i) = −3−6i
    auto a = Argon<float>{1.0f, 2.0f, 2.0f, -1.0f};
    auto b = Argon<float>{3.0f, 4.0f, 0.0f, 3.0f};
    expect(a.ComplexMultiplyConjugate(b).to_array()).to_equal(std::array<float, 4>{11.0f, 2.0f, -3.0f, -6.0f});
  });

  it("accumulates each rotation like vcmla", _{
    auto acc = Argon<float>{100.0f, 200.0f, 100.0f, 200.0f};
    auto b = Argon<float>{1.0f, 2.0f, 3.0f, 4.0f};
    auto c = Argon<float>{5.0f, 6.0f, 7.0f, 8.0f};
    // rot0: re += b.re·c.re, im += b.re·c.im
    expect(acc.ComplexMultiplyAdd<0>(b, c).to_array()).to_equal(std::array<float, 4>{105, 206, 121, 224});
    // rot90: re −= b.im·c.im, im += b.im·c.re
    expect(acc.ComplexMultiplyAdd<90>(b, c).to_array()).to_equal(std::array<float, 4>{88, 210, 68, 228});
    // rot180: re −= b.re·c.re, im −= b.re·c.im
    expect(acc.ComplexMultiplyAdd<180>(b, c).to_array()).to_equal(std::array<float, 4>{95, 194, 79, 176});
    // rot270: re += b.im·c.im, im −= b.im·c.re
    expect(acc.ComplexMultiplyAdd<270>(b, c).to_array()).to_equal(std::array<float, 4>{112, 190, 132, 172});
  });
});

CPPSPEC_MAIN(
  describe_add,
  describe_multiply
);
