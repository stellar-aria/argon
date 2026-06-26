#include "argon.hpp"
#include "cppspec.hpp"
#include "helpers/type_matrix.hpp"
#include <array>

// clang-format off

// Coverage for long (widening), narrowing, and absolute-difference arithmetic.

// ── AddLong / SubtractLong / SubtractAbsoluteLong (ArgonHalf -> widened) ─────

auto describe_add_long = describe("AddLong", ${
  it("widens int16 -> int32 while adding", _{
    std::array<int16_t, 4> a_arr = {1, 2, 3, 4};
    std::array<int16_t, 4> b_arr = {10, 20, 30, 40};
    auto a = ArgonHalf<int16_t>::Load(a_arr.data());
    auto b = ArgonHalf<int16_t>::Load(b_arr.data());
    auto result = a.AddLong(b).to_array();
    expect(result).to_equal(std::array<int32_t, 4>{11, 22, 33, 44});
  });

  it("does not overflow when widening near-max uint8 -> uint16", _{
    std::array<uint8_t, 8> a_arr; a_arr.fill(200u);
    std::array<uint8_t, 8> b_arr; b_arr.fill(200u);  // 400 fits in uint16
    auto a = ArgonHalf<uint8_t>::Load(a_arr.data());
    auto b = ArgonHalf<uint8_t>::Load(b_arr.data());
    auto result = a.AddLong(b).to_array();
    for (auto v : result)
      expect(v).to_equal(uint16_t{400});
  });
});

auto describe_subtract_long = describe("SubtractLong", ${
  it("widens int16 -> int32 while subtracting", _{
    std::array<int16_t, 4> a_arr = {50, 60, 70, 80};
    std::array<int16_t, 4> b_arr = {10, 20, 30, 40};
    auto a = ArgonHalf<int16_t>::Load(a_arr.data());
    auto b = ArgonHalf<int16_t>::Load(b_arr.data());
    auto result = a.SubtractLong(b).to_array();
    expect(result).to_equal(std::array<int32_t, 4>{40, 40, 40, 40});
  });
});

auto describe_subtract_absolute_long = describe("SubtractAbsoluteLong", ${
  it("widens uint8 -> uint16 while taking |a - b|", _{
    std::array<uint8_t, 8> a_arr = {10, 200, 30, 40, 50, 60, 70, 80};
    std::array<uint8_t, 8> b_arr = {30, 5, 30, 100, 50, 0, 255, 80};
    auto a = ArgonHalf<uint8_t>::Load(a_arr.data());
    auto b = ArgonHalf<uint8_t>::Load(b_arr.data());
    auto result = a.SubtractAbsoluteLong(b).to_array();
    expect(result).to_equal(std::array<uint16_t, 8>{20, 195, 0, 60, 0, 60, 185, 0});
  });
});

// ── AddNarrow / AddRoundNarrow / SubtractNarrow / SubtractRoundNarrow ────────
// These map to NEON ...HN ("returning high narrow"): the result is the *high*
// half of each (a OP b) lane, narrowed to the next-smaller type.

auto describe_add_narrow = describe("AddNarrow", ${
  it("returns the high half of (a + b), int32 -> int16", _{
    auto a = Argon<int32_t>{0x00010000, 0x00020000, 0x00030000, 0x00040000};
    auto b = Argon<int32_t>::FromScalar(0);
    auto result = a.AddNarrow(b).to_array();  // (a+b) >> 16
    expect(result).to_equal(std::array<int16_t, 4>{1, 2, 3, 4});
  });
});

auto describe_add_round_narrow = describe("AddRoundNarrow", ${
  it("rounds before taking the high half, int32 -> int16", _{
    // 0x00018000 >> 16 == 1, but rounded (+0x8000) it carries to 2
    auto a = Argon<int32_t>::FromScalar(0x00018000);
    auto b = Argon<int32_t>::FromScalar(0);
    auto result = a.AddRoundNarrow(b).to_array();
    for (auto v : result)
      expect((int)v).to_equal(2);
  });
});

auto describe_subtract_narrow = describe("SubtractNarrow", ${
  it("returns the high half of (a - b), int32 -> int16", _{
    auto a = Argon<int32_t>::FromScalar(0x00050000);
    auto b = Argon<int32_t>::FromScalar(0x00010000);
    auto result = a.SubtractNarrow(b).to_array();  // (a-b) >> 16 == 4
    for (auto v : result)
      expect((int)v).to_equal(4);
  });
});

auto describe_subtract_round_narrow = describe("SubtractRoundNarrow", ${
  it("rounds before taking the high half, int32 -> int16", _{
    auto a = Argon<int32_t>::FromScalar(0x0005C000);
    auto b = Argon<int32_t>::FromScalar(0x00010000);  // diff 0x0004C000 -> round -> 5
    auto result = a.SubtractRoundNarrow(b).to_array();
    for (auto v : result)
      expect((int)v).to_equal(5);
  });
});

// ── AddHalveRound / SubtractAbs / SubtractAbsAdd (base Vector ops) ───────────

auto describe_add_halve_round = describe("AddHalveRound", ${
  it("computes round((a + b) / 2) for int32", _{
    auto a = Argon<int32_t>{3, 5, 7, 9};
    auto b = Argon<int32_t>::FromScalar(2);
    auto result = a.AddHalveRound(b).to_array();  // round({5,7,9,11}/2)
    expect(result).to_equal(std::array<int32_t, 4>{3, 4, 5, 6});
  });
});

auto describe_subtract_abs = describe("SubtractAbs", ${
  it("computes |a - b| for int32", _{
    auto a = Argon<int32_t>{10, 5, 20, 3};
    auto b = Argon<int32_t>{3, 12, 20, 8};
    auto result = a.SubtractAbs(b).to_array();
    expect(result).to_equal(std::array<int32_t, 4>{7, 7, 0, 5});
  });
});

auto describe_subtract_abs_add = describe("SubtractAbsAdd", ${
  it("computes a + |b - c| for int32", _{
    auto a = Argon<int32_t>::FromScalar(100);
    auto b = Argon<int32_t>{10, 5, 20, 3};
    auto c = Argon<int32_t>{3, 12, 20, 8};
    auto result = a.SubtractAbsAdd(b, c).to_array();  // 100 + {7,7,0,5}
    expect(result).to_equal(std::array<int32_t, 4>{107, 107, 100, 105});
  });
});

CPPSPEC_MAIN(
  describe_add_long,
  describe_subtract_long,
  describe_subtract_absolute_long,
  describe_add_narrow,
  describe_add_round_narrow,
  describe_subtract_narrow,
  describe_subtract_round_narrow,
  describe_add_halve_round,
  describe_subtract_abs,
  describe_subtract_abs_add
);
