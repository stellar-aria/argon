#include "argon.hpp"
#include "cppspec.hpp"
#include "helpers/type_matrix.hpp"

// clang-format off

// ── Bitwise ops ────────────────────────────────────────────────────────────

auto describe_bitwise_and = describe("BitwiseAnd", ${
  it("AND of uint8 vectors", _{
    std::array<uint8_t, 16> a_arr, b_arr;
    a_arr.fill(0xFFu);
    b_arr.fill(0xF0u);
    auto a = Argon<uint8_t>::Load(a_arr.data());
    auto b = Argon<uint8_t>::Load(b_arr.data());
    auto result = (a & b).to_array();
    for (auto v : result)
      expect(v).to_equal(uint8_t{0xF0});
  });

  it("AND of uint32 vectors", _{
    std::array<uint32_t, 4> a_arr = {0xFFFFFFFFu, 0x0Fu, 0xF0u, 0u};
    std::array<uint32_t, 4> b_arr = {0xF0F0F0F0u, 0xFFu, 0xFFu, 0xFFu};
    auto a = Argon<uint32_t>::Load(a_arr.data());
    auto b = Argon<uint32_t>::Load(b_arr.data());
    auto result = a.BitwiseAnd(b).to_array();
    expect(result).to_equal(std::array<uint32_t, 4>{0xF0F0F0F0u, 0x0Fu, 0xF0u, 0u});
  });
});

auto describe_bitwise_or = describe("BitwiseOr", ${
  it("OR of uint16 vectors", _{
    std::array<uint16_t, 8> a_arr, b_arr;
    a_arr.fill(0x00FFu);
    b_arr.fill(0xFF00u);
    auto a = Argon<uint16_t>::Load(a_arr.data());
    auto b = Argon<uint16_t>::Load(b_arr.data());
    auto result = (a | b).to_array();
    for (auto v : result)
      expect(v).to_equal(uint16_t{0xFFFF});
  });
});

auto describe_bitwise_xor = describe("BitwiseXor", ${
  it("XOR is its own inverse for uint32", _{
    auto a_arr = argon::test::iota_array<uint32_t, 4>(1u);
    auto a = Argon<uint32_t>::Load(a_arr.data());
    auto b = a ^ a;
    auto result = b.to_array();
    for (auto v : result)
      expect(v).to_equal(uint32_t{0});
  });
});

auto describe_bitwise_not = describe("BitwiseNot", ${
  it("NOT inverts all bits for uint8", _{
    std::array<uint8_t, 16> a_arr;
    a_arr.fill(0u);
    auto a = Argon<uint8_t>::Load(a_arr.data());
    auto result = (~a).to_array();
    for (auto v : result)
      expect(v).to_equal(uint8_t{0xFF});
  });
});

// ── Shift ops ──────────────────────────────────────────────────────────────

auto describe_shift_left = describe("ShiftLeft", ${
  it("shifts uint16 left by 2", _{
    std::array<uint16_t, 8> a_arr;
    a_arr.fill(1u);
    auto a = Argon<uint16_t>::Load(a_arr.data());
    auto result = a.template ShiftLeft<2>().to_array();
    for (auto v : result)
      expect(v).to_equal(uint16_t{4});
  });

  it("shifts int32 left by 4", _{
    std::array<int32_t, 4> a_arr = {1, 2, 3, 4};
    auto a = Argon<int32_t>::Load(a_arr.data());
    auto result = a.template ShiftLeft<4>().to_array();
    expect(result).to_equal(std::array<int32_t, 4>{16, 32, 48, 64});
  });
});

auto describe_shift_right = describe("ShiftRight", ${
  it("logical-shifts uint32 right by 1", _{
    std::array<uint32_t, 4> a_arr = {8u, 16u, 32u, 64u};
    auto a = Argon<uint32_t>::Load(a_arr.data());
    auto result = a.template ShiftRight<1>().to_array();
    expect(result).to_equal(std::array<uint32_t, 4>{4u, 8u, 16u, 32u});
  });

  it("arithmetic-shifts int32 right by 1 (sign-extends)", _{
    std::array<int32_t, 4> a_arr = {-8, -4, 4, 8};
    auto a = Argon<int32_t>::Load(a_arr.data());
    auto result = a.template ShiftRight<1>().to_array();
    expect(result).to_equal(std::array<int32_t, 4>{-4, -2, 2, 4});
  });
});

// ── Bit-counting ops ───────────────────────────────────────────────────────

auto describe_count_leading_zeros = describe("CountLeadingZeroBits", ${
  it("counts leading zeros for uint32", _{
    std::array<uint32_t, 4> a_arr = {0x80000000u, 0x40000000u, 0x00000001u, 0xFFFFFFFFu};
    auto a = Argon<uint32_t>::Load(a_arr.data());
    auto result = a.CountLeadingZeroBits().to_array();
    expect((int)result[0]).to_equal(0);   // 1 at MSB
    expect((int)result[1]).to_equal(1);   // 1 at bit 30
    expect((int)result[2]).to_equal(31);  // only LSB set
    expect((int)result[3]).to_equal(0);   // all ones
  });

  it("counts leading zeros for uint8", _{
    std::array<uint8_t, 16> a_arr;
    a_arr.fill(0x10u); // 00010000
    auto a = Argon<uint8_t>::Load(a_arr.data());
    auto result = a.CountLeadingZeroBits().to_array();
    for (auto v : result)
      expect((int)v).to_equal(3);
  });
});

auto describe_count_active_bits = describe("CountActiveBits (Popcount)", ${
  it("counts set bits for uint8", _{
    std::array<uint8_t, 16> a_arr;
    a_arr.fill(0xFFu);
    auto a = Argon<uint8_t>::Load(a_arr.data());
    auto result = a.CountActiveBits().to_array();
    for (auto v : result)
      expect((int)v).to_equal(8);
  });

  it("popcount of zero is zero", _{
    std::array<uint8_t, 16> a_arr;
    a_arr.fill(0u);
    auto a = Argon<uint8_t>::Load(a_arr.data());
    auto result = a.CountActiveBits().to_array();
    for (auto v : result)
      expect((int)v).to_equal(0);
  });
});

auto describe_count_leading_sign_bits = describe("CountLeadingSignBits", ${
  it("counts leading sign bits for int32", _{
    // Most-positive int32: 0x7FFFFFFF — all sign-extension bits are 0 → leading_sign = 0
    // All-negative int32:  0x80000000 — leading_sign = 0
    // 0x3FFFFFFF — bit 30 transitions 0→1 → 1 leading sign (bit 31)
    std::array<int32_t, 4> a_arr = {0x3FFFFFFF, -2, -1, 1};
    auto a = Argon<int32_t>::Load(a_arr.data());
    auto result = a.CountLeadingSignBits().to_array();
    expect((int)result[0]).to_equal(1);  // one leading copy of sign
    expect((int)result[1]).to_equal(30); // 0xFFFFFFFE: 30 copies of 1 before the 0
    expect((int)result[2]).to_equal(31); // 0xFFFFFFFF: all ones, 31 leading sign bits
    expect((int)result[3]).to_equal(30); // 0x00000001: 30 leading zeros before LSB
  });
});

// ── BitwiseAndNot / OrNot / Clear ──────────────────────────────────────────

auto describe_bitwise_and_not = describe("BitwiseAndNot", ${
  it("computes a & ~b for uint32", _{
    std::array<uint32_t, 4> a_arr = {0xFFu, 0xF0u, 0xAAu, 0xFFFFu};
    std::array<uint32_t, 4> b_arr = {0x0Fu, 0x0Fu, 0x0Fu, 0xFF00u};
    auto a = Argon<uint32_t>::Load(a_arr.data());
    auto b = Argon<uint32_t>::Load(b_arr.data());
    auto result = a.BitwiseAndNot(b).to_array();
    expect(result).to_equal(std::array<uint32_t, 4>{0xF0u, 0xF0u, 0xA0u, 0xFFu});
  });
});

auto describe_bitwise_or_not = describe("BitwiseOrNot", ${
  it("computes a | ~b for uint8", _{
    std::array<uint8_t, 16> a_arr; a_arr.fill(0x0Fu);
    std::array<uint8_t, 16> b_arr; b_arr.fill(0x0Fu);  // ~b == 0xF0
    auto a = Argon<uint8_t>::Load(a_arr.data());
    auto b = Argon<uint8_t>::Load(b_arr.data());
    auto result = a.BitwiseOrNot(b).to_array();
    for (auto v : result)
      expect((int)v).to_equal(0xFF);  // 0x0F | 0xF0
  });
});

auto describe_bitwise_clear = describe("BitwiseClear", ${
  it("clears the bits of b from a (alias of BitwiseAndNot)", _{
    std::array<uint32_t, 4> a_arr = {0xFFu, 0xF0u, 0xAAu, 0xFFFFu};
    std::array<uint32_t, 4> b_arr = {0x0Fu, 0x0Fu, 0x0Fu, 0xFF00u};
    auto a = Argon<uint32_t>::Load(a_arr.data());
    auto b = Argon<uint32_t>::Load(b_arr.data());
    auto result = a.BitwiseClear(b).to_array();
    expect(result).to_equal(std::array<uint32_t, 4>{0xF0u, 0xF0u, 0xA0u, 0xFFu});
  });
});

// ── BitwiseSelect ──────────────────────────────────────────────────────────

auto describe_bitwise_select = describe("BitwiseSelect", ${
  it("selects lanes from two uint32 vectors using a mask", _{
    std::array<uint32_t, 4> mask_arr  = {0xFFFFFFFFu, 0u, 0xFFFFFFFFu, 0u};
    std::array<uint32_t, 4> true_arr  = {100u, 200u, 300u, 400u};
    std::array<uint32_t, 4> false_arr = {10u, 20u, 30u, 40u};
    auto mask  = Argon<uint32_t>::Load(mask_arr.data());
    auto tv    = Argon<uint32_t>::Load(true_arr.data());
    auto fv    = Argon<uint32_t>::Load(false_arr.data());
    auto result = mask.BitwiseSelect(tv, fv).to_array();
    expect(result).to_equal(std::array<uint32_t, 4>{100u, 20u, 300u, 40u});
  });
});

CPPSPEC_MAIN(
  describe_bitwise_and,
  describe_bitwise_or,
  describe_bitwise_xor,
  describe_bitwise_not,
  describe_shift_left,
  describe_shift_right,
  describe_count_leading_zeros,
  describe_count_active_bits,
  describe_count_leading_sign_bits,
  describe_bitwise_and_not,
  describe_bitwise_or_not,
  describe_bitwise_clear,
  describe_bitwise_select
);
