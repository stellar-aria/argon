#include "argon.hpp"
#include "cppspec.hpp"
#include <array>
#include <cstdint>

// clang-format off

// Expected values measured on QEMU's Cortex-M55 (vadc, vsbc, vshlc). Lane 0 is the least significant word.

auto describe_add = describe("AddWithCarry", ${
  it("adds as 128-bit numbers", _{
    auto a = Argon<uint32_t>{0xFFFFFFFFu, 0xFFFFFFFFu, 0u, 0xFFFFFFFFu};
    auto b = Argon<uint32_t>{1u, 0u, 0u, 1u};
    uint32_t carry = 0;
    expect(a.AddWithCarry(b, carry).to_array()).to_equal(std::array<uint32_t, 4>{0, 0, 1, 0});
    expect(carry).to_equal(uint32_t{1});
    carry = 1;
    expect(a.AddWithCarry(b, carry).to_array()).to_equal(std::array<uint32_t, 4>{1, 0, 1, 0});
    expect(carry).to_equal(uint32_t{1});
  });

  it("chains across vectors (256-bit add)", _{
    auto lo_a = Argon<uint32_t>{0xFFFFFFFFu}, hi_a = Argon<uint32_t>{0u};
    auto lo_b = Argon<uint32_t>{1u, 0u, 0u, 0u}, hi_b = Argon<uint32_t>{0u};
    uint32_t carry = 0;
    auto lo = lo_a.AddWithCarry(lo_b, carry);
    auto hi = hi_a.AddWithCarry(hi_b, carry);
    expect(lo.to_array()).to_equal(std::array<uint32_t, 4>{0, 0, 0, 0});
    expect(hi.to_array()).to_equal(std::array<uint32_t, 4>{1, 0, 0, 0});
    expect(carry).to_equal(uint32_t{0});
  });

  it("works on int32 lanes", _{
    uint32_t carry = 0;
    auto r = Argon<int32_t>{-1, 0, 0, 0}.AddWithCarry(Argon<int32_t>{1, 0, 0, 0}, carry);
    expect(r.to_array()).to_equal(std::array<int32_t, 4>{0, 1, 0, 0});
    expect(carry).to_equal(uint32_t{0});
  });
});

auto describe_subtract = describe("SubtractWithBorrow", ${
  it("subtracts as 128-bit numbers", _{
    auto x = Argon<uint32_t>{0u, 5u, 0u, 0u};
    auto y = Argon<uint32_t>{1u, 0u, 0u, 0u};
    uint32_t borrow = 0;
    expect(x.SubtractWithBorrow(y, borrow).to_array()).to_equal(std::array<uint32_t, 4>{0xFFFFFFFF, 4, 0, 0});
    expect(borrow).to_equal(uint32_t{0});
    borrow = 1;
    expect(x.SubtractWithBorrow(y, borrow).to_array()).to_equal(std::array<uint32_t, 4>{0xFFFFFFFE, 4, 0, 0});
    expect(borrow).to_equal(uint32_t{0});
  });

  it("borrows out of the top on underflow", _{
    uint32_t borrow = 0;
    auto r = Argon<uint32_t>{1u, 0u, 0u, 0u}.SubtractWithBorrow(Argon<uint32_t>{0u, 5u, 0u, 0u}, borrow);
    expect(r.to_array()).to_equal(std::array<uint32_t, 4>{1, 0xFFFFFFFB, 0xFFFFFFFF, 0xFFFFFFFF});
    expect(borrow).to_equal(uint32_t{1});
  });
});

auto describe_shift = describe("ShiftLeftWithCarry", ${
  it("shifts the whole vector left, carrying bits between words", _{
    auto v = Argon<uint32_t>{0x80000001u, 2u, 3u, 0xC0000004u};
    uint32_t carry = 0xABCDEF;
    expect(v.ShiftLeftWithCarry<4>(carry).to_array()).to_equal(std::array<uint32_t, 4>{0x1F, 0x28, 0x30, 0x40});
    expect(carry).to_equal(uint32_t{0xC});
    carry = 5;
    expect(v.ShiftLeftWithCarry<1>(carry).to_array()).to_equal(std::array<uint32_t, 4>{3, 5, 6, 0x80000008});
    expect(carry).to_equal(uint32_t{1});
    carry = 0x12345678;
    expect(v.ShiftLeftWithCarry<32>(carry).to_array()).to_equal(std::array<uint32_t, 4>{0x12345678, 0x80000001, 2, 3});
    expect(carry).to_equal(uint32_t{0xC0000004});
  });

  it("treats a uint8 vector as the same 128 bits", _{
    std::array<uint8_t, 16> bytes{};
    bytes[0] = 0x81;  // word 0 = 0x00000081
    uint32_t carry = 1;
    auto r = Argon<uint8_t>::Load(bytes.data()).ShiftLeftWithCarry<1>(carry).to_array();
    expect(r[0]).to_equal(uint8_t{0x03});
    expect(r[1]).to_equal(uint8_t{0x01});
    expect(carry).to_equal(uint32_t{0});
  });
});

CPPSPEC_MAIN(
  describe_add,
  describe_subtract,
  describe_shift
);
