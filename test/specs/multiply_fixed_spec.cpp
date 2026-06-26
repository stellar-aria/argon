#include "argon.hpp"
#include "cppspec.hpp"
#include "helpers/type_matrix.hpp"
#include <array>

// clang-format off

// Coverage for the widening and Q-format fixed-point multiply family.

// ── MultiplySubtract (base Vector op): a - (b * c) ──────────────────────────

auto describe_multiply_subtract = describe("MultiplySubtract", ${
  it("computes a - (b * c) for int32", _{
    auto a = Argon<int32_t>::FromScalar(100);
    auto b = Argon<int32_t>{2, 3, 4, 5};
    auto c = Argon<int32_t>{1, 2, 3, 4};
    auto result = a.MultiplySubtract(b, c).to_array();  // 100 - {2,6,12,20}
    expect(result).to_equal(std::array<int32_t, 4>{98, 94, 88, 80});
  });
});

// ── MultiplyLong (ArgonHalf -> widened): a * b ──────────────────────────────

auto describe_multiply_long = describe("MultiplyLong", ${
  it("widens int16 -> int32 while multiplying", _{
    std::array<int16_t, 4> a_arr = {100, 200, 300, 400};
    std::array<int16_t, 4> b_arr = {2, 3, 4, 5};
    auto a = ArgonHalf<int16_t>::Load(a_arr.data());
    auto b = ArgonHalf<int16_t>::Load(b_arr.data());
    auto result = a.MultiplyLong(b).to_array();
    expect(result).to_equal(std::array<int32_t, 4>{200, 600, 1200, 2000});
  });
});

// ── MultiplyAddLong / MultiplySubtractLong (Argon accumulator + narrow b,c) ──

auto describe_multiply_add_long = describe("MultiplyAddLong", ${
  it("accumulates a + (b * c) widening int16 -> int32", _{
    std::array<int16_t, 4> b_arr = {2, 3, 4, 5};
    std::array<int16_t, 4> c_arr = {10, 10, 10, 10};
    auto a = Argon<int32_t>::FromScalar(1000);
    auto b = ArgonHalf<int16_t>::Load(b_arr.data());
    auto c = ArgonHalf<int16_t>::Load(c_arr.data());
    auto result = a.MultiplyAddLong(b, c).to_array();  // 1000 + {20,30,40,50}
    expect(result).to_equal(std::array<int32_t, 4>{1020, 1030, 1040, 1050});
  });
});

auto describe_multiply_subtract_long = describe("MultiplySubtractLong", ${
  it("computes a - (b * c) widening int16 -> int32", _{
    std::array<int16_t, 4> b_arr = {2, 3, 4, 5};
    std::array<int16_t, 4> c_arr = {10, 10, 10, 10};
    auto a = Argon<int32_t>::FromScalar(1000);
    auto b = ArgonHalf<int16_t>::Load(b_arr.data());
    auto c = ArgonHalf<int16_t>::Load(c_arr.data());
    auto result = a.MultiplySubtractLong(b, c).to_array();  // 1000 - {20,30,40,50}
    expect(result).to_equal(std::array<int32_t, 4>{980, 970, 960, 950});
  });
});

// ── MultiplyDoubleSaturateLong / ...AddSaturateLong: saturate(2 * b * c) ─────

auto describe_multiply_double_saturate_long = describe("MultiplyDoubleSaturateLong", ${
  it("computes saturate(2 * a * b) widening int16 -> int32", _{
    std::array<int16_t, 4> a_arr = {2, 3, 4, 5};
    std::array<int16_t, 4> b_arr = {10, 10, 10, 10};
    auto a = ArgonHalf<int16_t>::Load(a_arr.data());
    auto b = ArgonHalf<int16_t>::Load(b_arr.data());
    auto result = a.MultiplyDoubleSaturateLong(b).to_array();  // 2 * {20,30,40,50}
    expect(result).to_equal(std::array<int32_t, 4>{40, 60, 80, 100});
  });

  it("saturates 2 * INT16_MIN * INT16_MIN to INT32_MAX", _{
    std::array<int16_t, 4> a_arr; a_arr.fill(std::numeric_limits<int16_t>::min());
    std::array<int16_t, 4> b_arr; b_arr.fill(std::numeric_limits<int16_t>::min());
    auto a = ArgonHalf<int16_t>::Load(a_arr.data());
    auto b = ArgonHalf<int16_t>::Load(b_arr.data());
    auto result = a.MultiplyDoubleSaturateLong(b).to_array();  // 2*2^30 == 2^31 -> saturates
    for (auto v : result)
      expect(v).to_equal(std::numeric_limits<int32_t>::max());
  });
});

auto describe_multiply_double_add_saturate_long = describe("MultiplyDoubleAddSaturateLong", ${
  it("computes a + saturate(2 * b * c) widening int16 -> int32", _{
    std::array<int16_t, 4> b_arr = {2, 3, 4, 5};
    std::array<int16_t, 4> c_arr = {10, 10, 10, 10};
    auto a = Argon<int32_t>::FromScalar(1000);
    auto b = ArgonHalf<int16_t>::Load(b_arr.data());
    auto c = ArgonHalf<int16_t>::Load(c_arr.data());
    auto result = a.MultiplyDoubleAddSaturateLong(b, c).to_array();  // 1000 + 2*{20,30,40,50}
    expect(result).to_equal(std::array<int32_t, 4>{1040, 1060, 1080, 1100});
  });
});

// ── MultiplyFixedQMax (VQDMULH): saturate((2 * a * b) >> 16) for int16 ───────

auto describe_multiply_fixed_qmax = describe("MultiplyFixedQMax", ${
  it("multiplies two Q15 values: 0.5 * 0.5 == 0.25", _{
    // 0x4000 == 0.5 in Q15; result 0x2000 == 0.25
    auto a = Argon<int16_t>::FromScalar(0x4000);
    auto b = Argon<int16_t>::FromScalar(0x4000);
    auto result = a.MultiplyFixedQMax(b).to_array();
    for (auto v : result)
      expect((int)v).to_equal(0x2000);
  });

  it("saturates (-1.0) * (-1.0) to Q15 max", _{
    auto a = Argon<int16_t>::FromScalar(std::numeric_limits<int16_t>::min());  // -1.0
    auto b = Argon<int16_t>::FromScalar(std::numeric_limits<int16_t>::min());
    auto result = a.MultiplyFixedQMax(b).to_array();  // +1.0 unrepresentable -> saturates
    for (auto v : result)
      expect(v).to_equal(std::numeric_limits<int16_t>::max());
  });
});

// ── MultiplyRoundFixedQMax (VQRDMULH): rounds before the high narrow ─────────

auto describe_multiply_round_fixed_qmax = describe("MultiplyRoundFixedQMax", ${
  it("rounds the Q15 product up where the truncating form would not", _{
    // 2*0x4001*0x4000 == 0x20008000; truncated >>16 == 0x2000, rounded == 0x2001
    auto a = Argon<int16_t>::FromScalar(0x4001);
    auto b = Argon<int16_t>::FromScalar(0x4000);
    auto result = a.MultiplyRoundFixedQMax(b).to_array();
    for (auto v : result)
      expect((int)v).to_equal(0x2001);
  });
});

// ── MultiplyAddFixedQMax / MultiplyRoundAddFixedQMax: a + QMax(b, c) ─────────

auto describe_multiply_add_fixed_qmax = describe("MultiplyAddFixedQMax", ${
  it("accumulates a + QMax(b, c)", _{
    auto a = Argon<int16_t>::FromScalar(100);
    auto b = Argon<int16_t>::FromScalar(0x4000);
    auto c = Argon<int16_t>::FromScalar(0x4000);
    auto result = a.MultiplyAddFixedQMax(b, c).to_array();  // 100 + 0x2000
    for (auto v : result)
      expect((int)v).to_equal(100 + 0x2000);
  });
});

auto describe_multiply_round_add_fixed_qmax = describe("MultiplyRoundAddFixedQMax", ${
  it("accumulates a + RoundQMax(b, c)", _{
    auto a = Argon<int16_t>::FromScalar(100);
    auto b = Argon<int16_t>::FromScalar(0x4001);
    auto c = Argon<int16_t>::FromScalar(0x4000);
    auto result = a.MultiplyRoundAddFixedQMax(b, c).to_array();  // 100 + 0x2001
    for (auto v : result)
      expect((int)v).to_equal(100 + 0x2001);
  });
});

CPPSPEC_MAIN(
  describe_multiply_subtract,
  describe_multiply_long,
  describe_multiply_add_long,
  describe_multiply_subtract_long,
  describe_multiply_double_saturate_long,
  describe_multiply_double_add_saturate_long,
  describe_multiply_fixed_qmax,
  describe_multiply_round_fixed_qmax,
  describe_multiply_add_fixed_qmax,
  describe_multiply_round_add_fixed_qmax
);
