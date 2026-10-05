#include "argon.hpp"
#include "cppspec.hpp"
#include <array>

// clang-format off

using P32 = argon::Predicate<Argon<int32_t>::vector_type>;
using P16 = argon::Predicate<Argon<uint16_t>::vector_type>;
using P8  = argon::Predicate<Argon<uint8_t>::vector_type>;

// ── Construction ───────────────────────────────────────────────────────────

auto describe_construction = describe("Predicate construction", ${
  it("True() activates every lane and False() none", _{
    expect(P32::True().to_array()).to_equal(std::array<bool, 4>{true, true, true, true});
    expect(P32::False().to_array()).to_equal(std::array<bool, 4>{false, false, false, false});
  });

  it("FirstN activates the leading lanes of int32 vectors", _{
    expect(P32::FirstN(0).to_array()).to_equal(std::array<bool, 4>{false, false, false, false});
    expect(P32::FirstN(1).to_array()).to_equal(std::array<bool, 4>{true, false, false, false});
    expect(P32::FirstN(3).to_array()).to_equal(std::array<bool, 4>{true, true, true, false});
    expect(P32::FirstN(4).to_array()).to_equal(std::array<bool, 4>{true, true, true, true});
  });

  it("FirstN saturates at the lane count", _{
    expect(P32::FirstN(5).All()).to_be_true();
    expect(P8::FirstN(1000).All()).to_be_true();
  });

  it("FirstN activates the leading lanes of uint16 and uint8 vectors", _{
    expect(P16::FirstN(5).to_array()).to_equal(std::array<bool, 8>{true, true, true, true, true, false, false, false});
    expect(P8::FirstN(9).Count()).to_equal(size_t{9});
    expect(P8::FirstN(9).Active(8)).to_be_true();
    expect(P8::FirstN(9).Active(9)).to_be_false();
  });

  it("FromMask treats any nonzero lane as active", _{
    auto p = P32::FromMask(Argon<uint32_t>{0u, 1u, 0x80000000u, 0u});
    expect(p.to_array()).to_equal(std::array<bool, 4>{false, true, true, false});
  });

  it("ToMask expands to all-ones and all-zeros lanes", _{
    expect(P16::FirstN(2).ToMask().to_array())
        .to_equal(std::array<uint16_t, 8>{0xFFFF, 0xFFFF, 0, 0, 0, 0, 0, 0});
  });
});

// ── Logic ──────────────────────────────────────────────────────────────────

auto describe_logic = describe("Predicate logic", ${
  it("combines lanes with &, |, ^ and ~", _{
    auto a = Argon<int32_t>{1, 2, 3, 4};
    auto gt1 = a > Argon<int32_t>{1};  // {F, T, T, T}
    auto lt4 = a < Argon<int32_t>{4};  // {T, T, T, F}
    expect((gt1 & lt4).to_array()).to_equal(std::array<bool, 4>{false, true, true, false});
    expect((gt1 | lt4).to_array()).to_equal(std::array<bool, 4>{true, true, true, true});
    expect((gt1 ^ lt4).to_array()).to_equal(std::array<bool, 4>{true, false, false, true});
    expect((~gt1).to_array()).to_equal(std::array<bool, 4>{true, false, false, false});
  });

  it("keeps uint8 lanes independent", _{
    auto p = P8::FirstN(10) & ~P8::FirstN(3);
    expect(p.Count()).to_equal(size_t{7});
    expect(p.Active(2)).to_be_false();
    expect(p.Active(3)).to_be_true();
    expect(p.Active(9)).to_be_true();
    expect(p.Active(10)).to_be_false();
  });
});

// ── Queries ────────────────────────────────────────────────────────────────

auto describe_queries = describe("Predicate queries", ${
  it("Any / All / None / Count report the active lanes", _{
    expect(P32::False().Any()).to_be_false();
    expect(P32::False().None()).to_be_true();
    expect(P32::FirstN(1).Any()).to_be_true();
    expect(P32::FirstN(1).All()).to_be_false();
    expect(P32::FirstN(1).Count()).to_equal(size_t{1});
    expect(P32::True().All()).to_be_true();
    expect(P32::True().Count()).to_equal(size_t{4});
    expect(P16::FirstN(7).Count()).to_equal(size_t{7});
  });

  it("detects a single active lane anywhere", _{
    for (int lane = 0; lane < 4; ++lane) {
      std::array<int32_t, 4> arr = {0, 0, 0, 0};
      arr[lane] = 1;
      auto p = Argon<int32_t>::Load(arr.data()) == Argon<int32_t>{1};
      expect(p.Any()).to_be_true();
      expect(p.Count()).to_equal(size_t{1});
      expect(p.Active(lane)).to_be_true();
    }
  });
});

// ── Selection ──────────────────────────────────────────────────────────────

auto describe_select = describe("Predicate Select", ${
  it("selects int32 lanes", _{
    auto a = Argon<int32_t>{1, 20, 3, 40};
    auto b = Argon<int32_t>{10, 2, 30, 4};
    expect((a > b).Select(a, b).to_array()).to_equal(std::array<int32_t, 4>{10, 20, 30, 40});
  });

  it("selects float lanes from an int32 comparison", _{
    auto p = Argon<int32_t>{1, 0, 1, 0} == Argon<int32_t>{1};
    auto r = p.Select(Argon<float>{1.5f}, Argon<float>{-1.5f});
    expect(r.to_array()).to_equal(std::array<float, 4>{1.5f, -1.5f, 1.5f, -1.5f});
  });

  it("selects uint8 lanes", _{
    auto r = P8::FirstN(3).Select(Argon<uint8_t>{1}, Argon<uint8_t>{0});
    std::array<uint8_t, 16> expected{};
    expected[0] = expected[1] = expected[2] = 1;
    expect(r.to_array()).to_equal(expected);
  });

  it("selects through argon::ternary with vectors and scalars", _{
    auto a = Argon<float>{1.0f, 5.0f, -2.0f, 0.5f};
    expect(argon::ternary(a > Argon<float>{0.75f}, a, Argon<float>{0.0f}).to_array())
        .to_equal(std::array<float, 4>{1.0f, 5.0f, 0.0f, 0.0f});
    expect(argon::ternary(a < 0.75f, 1.0f, 2.0f).to_array()).to_equal(std::array<float, 4>{2.0f, 2.0f, 1.0f, 1.0f});
  });
});

// ── Compatibility ──────────────────────────────────────────────────────────

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
auto describe_compat = describe("Predicate compatibility", ${
  it("still converts implicitly to the mask vector (deprecated)", _{
    Argon<uint32_t> mask = Argon<int32_t>{1, 2, 3, 4} > Argon<int32_t>{2};
    expect(mask.to_array()).to_equal(std::array<uint32_t, 4>{0u, 0u, 0xFFFFFFFFu, 0xFFFFFFFFu});
  });
});
#pragma GCC diagnostic pop

#ifndef ARGON_PLATFORM_MVE
auto describe_half = describe("Predicate on ArgonHalf", ${
  it("compares and selects 64-bit vectors", _{
    auto a = ArgonHalf<int32_t>{1, 5};
    auto b = ArgonHalf<int32_t>{3, 3};
    auto p = a > b;
    expect(p.to_array()).to_equal(std::array<bool, 2>{false, true});
    expect(p.Count()).to_equal(size_t{1});
    expect(p.Select(a, b).to_array()).to_equal(std::array<int32_t, 2>{3, 5});
  });
});
#define NEON_ONLY_SPECS , describe_half
#else
#define NEON_ONLY_SPECS
#endif

CPPSPEC_MAIN(
  describe_construction,
  describe_logic,
  describe_queries,
  describe_select,
  describe_compat
  NEON_ONLY_SPECS
);
