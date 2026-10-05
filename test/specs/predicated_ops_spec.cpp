#include "argon.hpp"
#include "cppspec.hpp"
#include <array>

// clang-format off

using P32 = argon::Predicate<Argon<int32_t>::vector_type>;
using P8  = argon::Predicate<Argon<uint8_t>::vector_type>;

// ── Merging (_m) forms ─────────────────────────────────────────────────────

auto describe_merging = describe("Predicated operations (merging)", ${
  it("Add takes the inactive lanes from the fallback", _{
    auto a = Argon<int32_t>{1, 2, 3, 4};
    auto r = a.Add(Argon<int32_t>{10}, P32::FirstN(2), Argon<int32_t>{-1});
    expect(r.to_array()).to_equal(std::array<int32_t, 4>{11, 12, -1, -1});
  });

  it("_z is _m with a zero fallback", _{
    auto a = Argon<float>{1.0f, 2.0f, 3.0f, 4.0f};
    auto active = a > Argon<float>{2.0f};
    auto r = a.Multiply(Argon<float>{2.0f}, active, Argon<float>{0.0f});
    expect(r.to_array()).to_equal(std::array<float, 4>{0.0f, 0.0f, 6.0f, 8.0f});
  });

  it("covers Subtract, Max, Min and SubtractAbs", _{
    auto a = Argon<int16_t>{1, 9, 3, 7, 5, 5, 0, -8};
    auto b = Argon<int16_t>{4};
    auto keep = a;
    auto active = argon::Predicate<Argon<int16_t>::vector_type>::FirstN(4);
    expect(a.Subtract(b, active, keep).to_array()).to_equal(std::array<int16_t, 8>{-3, 5, -1, 3, 5, 5, 0, -8});
    expect(a.Max(b, active, keep).to_array()).to_equal(std::array<int16_t, 8>{4, 9, 4, 7, 5, 5, 0, -8});
    expect(a.Min(b, active, keep).to_array()).to_equal(std::array<int16_t, 8>{1, 4, 3, 4, 5, 5, 0, -8});
    expect(a.SubtractAbs(b, active, keep).to_array()).to_equal(std::array<int16_t, 8>{3, 5, 1, 3, 5, 5, 0, -8});
  });

  it("covers float Max/Min, matching the unpredicated forms", _{
    auto a = Argon<float>{1.0f, 5.0f, -2.0f, 3.0f};
    auto b = Argon<float>{2.0f};
    auto all = argon::Predicate<Argon<float>::vector_type>::True();
    expect(a.Max(b, all, a).to_array()).to_equal(a.Max(b).to_array());
    expect(a.Min(b, all, a).to_array()).to_equal(a.Min(b).to_array());
  });

  it("covers the bitwise operations", _{
    auto a = Argon<uint8_t>{0b1100};
    auto b = Argon<uint8_t>{0b1010};
    auto fallback = Argon<uint8_t>{0xFF};
    auto active = P8::FirstN(1);
    expect(a.BitwiseAnd(b, active, fallback).to_array()[0]).to_equal(uint8_t{0b1000});
    expect(a.BitwiseOr(b, active, fallback).to_array()[0]).to_equal(uint8_t{0b1110});
    expect(a.BitwiseXor(b, active, fallback).to_array()[0]).to_equal(uint8_t{0b0110});
    expect(a.BitwiseAndNot(b, active, fallback).to_array()[0]).to_equal(uint8_t{0b0100});
    expect(a.BitwiseAnd(b, active, fallback).to_array()[1]).to_equal(uint8_t{0xFF});
  });

  it("covers Negate and Absolute, including unsigned Negate", _{
    auto a = Argon<int32_t>{-1, 2, -3, 4};
    expect(a.Negate(P32::FirstN(2), a).to_array()).to_equal(std::array<int32_t, 4>{1, -2, -3, 4});
    expect(a.Absolute(P32::FirstN(3), Argon<int32_t>{0}).to_array()).to_equal(std::array<int32_t, 4>{1, 2, 3, 0});
    auto u = Argon<uint32_t>{1u, 2u, 3u, 4u};
    expect(u.Negate(P32::FirstN(1), u).to_array()).to_equal(std::array<uint32_t, 4>{0xFFFFFFFFu, 2u, 3u, 4u});
  });
});

// ── Don't-care (_x) forms ──────────────────────────────────────────────────

auto describe_dont_care = describe("Predicated operations (don't care)", ${
  it("compute the active lanes", _{
    auto a = Argon<int32_t>{1, 2, 3, 4};
    auto active = P32::FirstN(3);
    auto r = a.Add(Argon<int32_t>{100}, active);
    auto arr = r.to_array();
    expect(arr[0]).to_equal(101);
    expect(arr[1]).to_equal(102);
    expect(arr[2]).to_equal(103);
    auto n = a.Negate(active).to_array();
    expect(n[0]).to_equal(-1);
    expect(n[2]).to_equal(-3);
  });
});

// ── Predicated comparisons ─────────────────────────────────────────────────

auto describe_predicated_compare = describe("Predicated comparisons", ${
  it("are active only where both the predicate and the comparison hold", _{
    auto x  = Argon<int32_t>{1, 5, 9, 12};
    auto in_range = x.LessThan(Argon<int32_t>{10}, x > Argon<int32_t>{2});
    expect(in_range.to_array()).to_equal(std::array<bool, 4>{false, true, true, false});
  });

  it("match active & comparison for every comparison and type", _{
    auto a = Argon<uint16_t>{1, 2, 3, 4, 5, 6, 7, 8};
    auto b = Argon<uint16_t>{4};
    auto active = argon::Predicate<Argon<uint16_t>::vector_type>::FirstN(6);
    expect(a.Equal(b, active).to_array()).to_equal((active & (a == b)).to_array());
    expect(a.GreaterThan(b, active).to_array()).to_equal((active & (a > b)).to_array());
    expect(a.GreaterThanOrEqual(b, active).to_array()).to_equal((active & (a >= b)).to_array());
    expect(a.LessThan(b, active).to_array()).to_equal((active & (a < b)).to_array());
    expect(a.LessThanOrEqual(b, active).to_array()).to_equal((active & (a <= b)).to_array());
    auto f = Argon<float>{-1.0f, 0.0f, 1.0f, 2.0f};
    auto fa = argon::Predicate<Argon<float>::vector_type>::FirstN(3);
    expect(f.GreaterThan(Argon<float>{0.0f}, fa).to_array()).to_equal(std::array<bool, 4>{false, false, true, false});
  });
});

CPPSPEC_MAIN(
  describe_merging,
  describe_dont_care,
  describe_predicated_compare
);
