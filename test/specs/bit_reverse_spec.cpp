#include "argon.hpp"
#include "cppspec.hpp"
#include <array>
#include <cstdint>

// clang-format off

// Expected values measured on QEMU's Cortex-M55 (vbrsr).

auto describe_bit_reverse = describe("BitReverse", ${
  it("reverses the low bits of uint32 lanes", _{
    auto v = Argon<uint32_t>{1u, 2u, 6u, 0xF0000003u};
    expect(v.BitReverse(0).to_array()).to_equal(std::array<uint32_t, 4>{0, 0, 0, 0});
    expect(v.BitReverse(1).to_array()).to_equal(std::array<uint32_t, 4>{1, 0, 0, 1});
    expect(v.BitReverse(3).to_array()).to_equal(std::array<uint32_t, 4>{4, 2, 3, 6});
    expect(v.BitReverse(8).to_array()).to_equal(std::array<uint32_t, 4>{0x80, 0x40, 0x60, 0xC0});
    expect(v.BitReverse(31).to_array()).to_equal(std::array<uint32_t, 4>{0x40000000, 0x20000000, 0x30000000, 0x60000007});
    expect(v.BitReverse(32).to_array()).to_equal(std::array<uint32_t, 4>{0x80000000, 0x40000000, 0x60000000, 0xC000000F});
    expect(v.BitReverse(33).to_array()).to_equal(v.BitReverse(32).to_array());
  });

  it("reverses uint8 and uint16 lanes", _{
    std::array<uint8_t, 16> in{1, 2, 3, 0x81};
    auto b = Argon<uint8_t>::Load(in.data());
    auto r3 = b.BitReverse(3).to_array();
    expect(std::array<uint8_t, 4>{r3[0], r3[1], r3[2], r3[3]}).to_equal(std::array<uint8_t, 4>{4, 2, 6, 4});
    auto r8 = b.BitReverse(8).to_array();
    expect(std::array<uint8_t, 4>{r8[0], r8[1], r8[2], r8[3]}).to_equal(std::array<uint8_t, 4>{0x80, 0x40, 0xC0, 0x81});
    auto h = Argon<uint16_t>{1, 2, 3, 0x8001, 0x00F0, 7, 0, 0xFFFF};
    expect(h.BitReverse(16).to_array()).to_equal(std::array<uint16_t, 8>{0x8000, 0x4000, 0xC000, 0x8001, 0x0F00, 0xE000, 0, 0xFFFF});
    expect(h.BitReverse(4).to_array()).to_equal(std::array<uint16_t, 8>{8, 4, 12, 8, 0, 14, 0, 15});
  });

  it("shifts signed lanes logically", _{
    auto s = Argon<int32_t>{static_cast<int32_t>(0xF0000003u), 1, 2, 3};
    expect(s.BitReverse(31).to_array()[0]).to_equal(int32_t{0x60000007});
  });

  it("gives the bit-reversed order of an 8-point FFT", _{
    auto idx = Argon<uint16_t>::Iota(0).BitReverse(3);
    expect(idx.to_array()).to_equal(std::array<uint16_t, 8>{0, 4, 2, 6, 1, 5, 3, 7});
  });
});

CPPSPEC_MAIN(describe_bit_reverse);
