#include "argon.hpp"
#include "cppspec.hpp"
#include "helpers/type_matrix.hpp"
#include <array>

// clang-format off

// Coverage for the shift family beyond the basic ShiftLeft/ShiftRight already
// exercised in bitwise_spec.cpp and convert_spec.cpp (ShiftRightNarrow).

// ── ShiftLeftRound ──────────────────────────────────────────────────────────
// ShiftLeftRound takes a per-lane *signed* shift count; negative counts shift
// right with rounding (VRSHL), positive counts shift left (rounding is a no-op).

auto describe_shift_left_round = describe("ShiftLeftRound", ${
  it("left-shifts by a positive per-lane count", _{
    auto a = Argon<int32_t>{1, 2, 3, 4};
    auto result = a.ShiftLeftRound(Argon<int32_t>{2, 2, 2, 2}).to_array();
    expect(result).to_equal(std::array<int32_t, 4>{4, 8, 12, 16});
  });

  it("right-shifts with rounding for negative counts", _{
    // round(x / 2) == (x + 1) >> 1 for these values
    auto a = Argon<int32_t>{4, 5, 6, 7};
    auto result = a.ShiftLeftRound(Argon<int32_t>{-1, -1, -1, -1}).to_array();
    expect(result).to_equal(std::array<int32_t, 4>{2, 3, 3, 4});
  });
});

// ── ShiftLeftRoundSaturate ──────────────────────────────────────────────────

auto describe_shift_left_round_saturate = describe("ShiftLeftRoundSaturate", ${
  it("saturates int8 overflow on a left shift", _{
    auto a = Argon<int8_t>::FromScalar(64);
    auto result = a.ShiftLeftRoundSaturate(Argon<int8_t>::FromScalar(1)).to_array();
    for (auto v : result)
      expect((int)v).to_equal((int)std::numeric_limits<int8_t>::max());  // 64<<1 == 128 -> 127
  });
});

// ── ShiftLeftSaturate<n> ────────────────────────────────────────────────────

auto describe_shift_left_saturate = describe("ShiftLeftSaturate", ${
  it("saturates int8 to INT8_MAX on overflow", _{
    auto a = Argon<int8_t>::FromScalar(100);
    auto result = a.template ShiftLeftSaturate<1>().to_array();  // 100<<1 == 200 -> 127
    for (auto v : result)
      expect((int)v).to_equal((int)std::numeric_limits<int8_t>::max());
  });

  it("saturates negative int8 to INT8_MIN on overflow", _{
    auto a = Argon<int8_t>::FromScalar(-100);
    auto result = a.template ShiftLeftSaturate<1>().to_array();  // -200 -> -128
    for (auto v : result)
      expect((int)v).to_equal((int)std::numeric_limits<int8_t>::min());
  });
});

// ── ShiftLeftInsert<n> ──────────────────────────────────────────────────────
// result = (b << n) | (this & ((1 << n) - 1)) — keeps the low n bits of the
// receiver and inserts b shifted left (the receiver is the SLI destination).

auto describe_shift_left_insert = describe("ShiftLeftInsert", ${
  it("keeps the receiver's low n bits and inserts b shifted left", _{
    auto a = Argon<uint16_t>::FromScalar(0x0007u);  // low nibble 0x0007 is kept
    auto b = Argon<uint16_t>::FromScalar(0x0010u);  // 0x0010 << 4 == 0x0100
    auto result = a.template ShiftLeftInsert<4>(b).to_array();  // 0x0100 | 0x0007
    for (auto v : result)
      expect(v).to_equal(uint16_t{0x0107});
  });
});

// ── ShiftRightRound<n> ──────────────────────────────────────────────────────

auto describe_shift_right_round = describe("ShiftRightRound", ${
  it("rounds to nearest on a right shift", _{
    auto a = Argon<int32_t>{5, 4, 6, 8};
    auto result = a.template ShiftRightRound<1>().to_array();  // (x + 1) >> 1
    expect(result).to_equal(std::array<int32_t, 4>{3, 2, 3, 4});
  });
});

// ── ShiftRightAccumulate<n> ─────────────────────────────────────────────────
// result = a + (b >> n)

auto describe_shift_right_accumulate = describe("ShiftRightAccumulate", ${
  it("adds the right-shifted b to a", _{
    auto a = Argon<int32_t>::FromScalar(100);
    auto b = Argon<int32_t>{16, 32, 64, 128};
    auto result = a.template ShiftRightAccumulate<2>(b).to_array();  // 100 + {4,8,16,32}
    expect(result).to_equal(std::array<int32_t, 4>{104, 108, 116, 132});
  });
});

// ── ShiftRightAccumulateRound<n> ────────────────────────────────────────────
// result = a + round(b >> n)

auto describe_shift_right_accumulate_round = describe("ShiftRightAccumulateRound", ${
  it("adds the rounded right-shifted b to a", _{
    auto a = Argon<int32_t>::FromScalar(100);
    auto b = Argon<int32_t>::FromScalar(6);
    auto result = a.template ShiftRightAccumulateRound<2>(b).to_array();  // 100 + round(6/4)=2
    for (auto v : result)
      expect(v).to_equal(int32_t{102});
  });
});

// ── ShiftRightInsert<n> ─────────────────────────────────────────────────────
// result = (this & high-n-bits-mask) | (b >> n) — keeps the high n bits of the
// receiver and inserts b shifted right (the receiver is the SRI destination).

auto describe_shift_right_insert = describe("ShiftRightInsert", ${
  it("keeps the receiver's high n bits and inserts b shifted right", _{
    auto a = Argon<uint16_t>::FromScalar(0xABCDu);  // high nibble 0xA000 is kept
    auto b = Argon<uint16_t>::FromScalar(0x1230u);  // 0x1230 >> 4 == 0x0123
    auto result = a.template ShiftRightInsert<4>(b).to_array();  // 0xA000 | 0x0123
    for (auto v : result)
      expect(v).to_equal(uint16_t{0xA123});
  });
});

// ── ShiftLeftLong<n> (ArgonHalf -> next-larger) ─────────────────────────────

auto describe_shift_left_long = describe("ShiftLeftLong", ${
  it("shifts left by n and widens uint8 -> uint16", _{
    std::array<uint8_t, 8> data = {1, 2, 3, 4, 5, 6, 7, 8};
    auto a = ArgonHalf<uint8_t>::Load(data.data());
    auto result = a.template ShiftLeftLong<2>().to_array();  // *4, widened
    expect(result).to_equal(std::array<uint16_t, 8>{4, 8, 12, 16, 20, 24, 28, 32});
  });
});

// ── ShiftRightRoundNarrow<n> (Argon -> ArgonHalf) ───────────────────────────

auto describe_shift_right_round_narrow = describe("ShiftRightRoundNarrow", ${
  it("rounds, right-shifts, and narrows uint16 -> uint8", _{
    auto a = Argon<uint16_t>::FromScalar(31u);
    auto result = a.template ShiftRightRoundNarrow<1>().to_array();  // round(31/2)=16
    for (auto v : result)
      expect((int)v).to_equal(16);
  });
});

// ── ShiftRightSaturateNarrow<n> (Argon -> ArgonHalf) ────────────────────────

auto describe_shift_right_saturate_narrow = describe("ShiftRightSaturateNarrow", ${
  it("narrows uint16 -> uint8 in range", _{
    auto a = Argon<uint16_t>::FromScalar(0x0FF0u);
    auto result = a.template ShiftRightSaturateNarrow<4>().to_array();  // 0xFF == 255
    for (auto v : result)
      expect((int)v).to_equal(255);
  });

  it("saturates uint16 -> uint8 on overflow", _{
    auto a = Argon<uint16_t>::FromScalar(0x1000u);
    auto result = a.template ShiftRightSaturateNarrow<4>().to_array();  // 0x100 -> 255
    for (auto v : result)
      expect((int)v).to_equal(255);
  });
});

// ── ShiftRightRoundSaturateNarrow<n> (Argon -> ArgonHalf) ───────────────────

auto describe_shift_right_round_saturate_narrow = describe("ShiftRightRoundSaturateNarrow", ${
  it("rounds, saturates, and narrows uint16 -> uint8", _{
    auto a = Argon<uint16_t>::FromScalar(0x0FFEu);
    auto result = a.template ShiftRightRoundSaturateNarrow<4>().to_array();  // round(4094/16)=256 -> 255
    for (auto v : result)
      expect((int)v).to_equal(255);
  });
});

CPPSPEC_MAIN(
  describe_shift_left_round,
  describe_shift_left_round_saturate,
  describe_shift_left_saturate,
  describe_shift_left_insert,
  describe_shift_right_round,
  describe_shift_right_accumulate,
  describe_shift_right_accumulate_round,
  describe_shift_right_insert,
  describe_shift_left_long,
  describe_shift_right_round_narrow,
  describe_shift_right_saturate_narrow,
  describe_shift_right_round_saturate_narrow
);
