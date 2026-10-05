#include "argon.hpp"
#include "cppspec.hpp"
#include <array>

// clang-format off

// ── if_ / else_ ────────────────────────────────────────────────────────────

auto describe_if_else = describe("if_ / else_", ${
  it("takes the if_ value where the condition holds and the else_ value elsewhere", _{
    auto x = Argon<int32_t>{1, 5, 2, 8};
    auto r = argon::if_(x > Argon<int32_t>{3}, Argon<int32_t>{100}).else_(Argon<int32_t>{-100});
    expect(r.to_array()).to_equal(std::array<int32_t, 4>{-100, 100, -100, 100});
  });

  it("accepts scalars for either branch", _{
    auto x = Argon<float>{0.25f, 0.75f, 0.5f, 1.0f};
    auto r = argon::if_(x < 0.5f, 0.0f).else_(1.0f);
    expect(r.to_array()).to_equal(std::array<float, 4>{0.0f, 1.0f, 1.0f, 1.0f});
  });

  it("accepts callables for either branch", _{
    auto x = Argon<int32_t>{1, 2, 3, 4};
    auto r = argon::if_(x == Argon<int32_t>{2}, [&] { return x * 10; }).else_([&] { return x; });
    expect(r.to_array()).to_equal(std::array<int32_t, 4>{1, 20, 3, 4});
  });
});

// ── else_if_ chains ────────────────────────────────────────────────────────

auto describe_else_if = describe("else_if_", ${
  it("clamps with an if / else-if / else chain", _{
    auto x  = Argon<int32_t>{-5, 3, 12, 7};
    auto lo = Argon<int32_t>{0};
    auto hi = Argon<int32_t>{10};
    auto r = argon::if_(x < lo, lo).else_if_(x > hi, hi).else_(x);
    expect(r.to_array()).to_equal(std::array<int32_t, 4>{0, 3, 10, 7});
  });

  it("gives each lane the first condition that holds for it", _{
    auto x = Argon<int32_t>{1, 5, 15, 25};
    auto r = argon::if_(x > Argon<int32_t>{20}, 3)
                 .else_if_(x > Argon<int32_t>{10}, 2)
                 .else_if_(x > Argon<int32_t>{0}, 1)
                 .else_(0);
    expect(r.to_array()).to_equal(std::array<int32_t, 4>{1, 1, 2, 3});
  });

  it("does not let a later condition override an earlier one", _{
    auto x = Argon<int32_t>{1, 2, 3, 4};
    auto r = argon::if_(x > Argon<int32_t>{2}, 100).else_if_(x > Argon<int32_t>{0}, 200).else_(300);
    expect(r.to_array()).to_equal(std::array<int32_t, 4>{200, 200, 100, 100});
  });

  it("works on uint8 lanes", _{
    std::array<uint8_t, 16> arr{};
    std::array<uint8_t, 16> expected{};
    for (size_t i = 0; i < 16; ++i) {
      arr[i] = static_cast<uint8_t>(i);
      expected[i] = i < 4 ? 1 : (i < 8 ? 2 : 3);
    }
    auto x = Argon<uint8_t>::Load(arr.data());
    auto r = argon::if_(x < Argon<uint8_t>{4}, uint8_t{1}).else_if_(x < Argon<uint8_t>{8}, uint8_t{2}).else_(uint8_t{3});
    expect(r.to_array()).to_equal(expected);
  });
});

// ── Predicate logic sugar ──────────────────────────────────────────────────

auto describe_logic_sugar = describe("Predicate && || !", ${
  it("match & | ~", _{
    auto x = Argon<int32_t>{1, 2, 3, 4};
    auto a = x > Argon<int32_t>{1};
    auto b = x < Argon<int32_t>{4};
    expect((a && b).to_array()).to_equal((a & b).to_array());
    expect((a || b).to_array()).to_equal((a | b).to_array());
    expect((!a).to_array()).to_equal((~a).to_array());
  });

  it("compose inside a chain", _{
    auto x = Argon<int32_t>{1, 5, 9, 12};
    auto r = argon::if_(x > Argon<int32_t>{2} && x < Argon<int32_t>{10}, 1).else_(0);
    expect(r.to_array()).to_equal(std::array<int32_t, 4>{0, 1, 1, 0});
  });
});

#ifndef ARGON_PLATFORM_MVE
auto describe_half = describe("if_ / else_ on ArgonHalf", ${
  it("chains on 64-bit vectors", _{
    auto x = ArgonHalf<int32_t>{-1, 4};
    auto r = argon::if_(x < ArgonHalf<int32_t>{0}, 0).else_(x);
    expect(r.to_array()).to_equal(std::array<int32_t, 2>{0, 4});
  });
});
#define NEON_ONLY_SPECS , describe_half
#else
#define NEON_ONLY_SPECS
#endif

CPPSPEC_MAIN(
  describe_if_else,
  describe_else_if,
  describe_logic_sugar
  NEON_ONLY_SPECS
);
