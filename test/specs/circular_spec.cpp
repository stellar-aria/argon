#include "argon.hpp"
#include "cppspec.hpp"
#include <array>
#include <cstdint>

// clang-format off

// Expected values measured on QEMU's Cortex-M55 (viwdup / vdwdup); every platform must match them.

auto describe_up = describe("CircularIndices", ${
  it("wraps to zero at the buffer size", _{
    uint32_t offset = 4;
    expect(Argon<uint32_t>::CircularIndices(offset, 6).to_array()).to_equal(std::array<uint32_t, 4>{4, 5, 0, 1});
    expect(offset).to_equal(uint32_t{2});
  });

  it("steps by 2", _{
    uint32_t offset = 0;
    expect(Argon<uint32_t>::CircularIndices<2>(offset, 6).to_array()).to_equal(std::array<uint32_t, 4>{0, 2, 4, 0});
    expect(offset).to_equal(uint32_t{2});
  });

  it("wraps more than once when the buffer is shorter than a vector", _{
    uint32_t offset = 3;
    expect(Argon<uint16_t>::CircularIndices(offset, 5).to_array())
        .to_equal(std::array<uint16_t, 8>{3, 4, 0, 1, 2, 3, 4, 0});
    expect(offset).to_equal(uint32_t{1});
  });

  it("produces uint8 indices", _{
    uint32_t offset = 250;
    std::array<uint8_t, 16> expected{};
    for (size_t i = 0; i < 16; ++i) expected[i] = static_cast<uint8_t>((250 + i) % 256);
    expect(Argon<uint8_t>::CircularIndices(offset, 256).to_array()).to_equal(expected);
    expect(offset).to_equal(uint32_t{10});
  });

  it("never wraps when the offset is not a multiple of the step, as the instruction does", _{
    uint32_t offset = 5;
    expect(Argon<uint32_t>::CircularIndices<4>(offset, 8).to_array()).to_equal(std::array<uint32_t, 4>{5, 9, 13, 17});
    expect(offset).to_equal(uint32_t{21});
  });

  it("drives a gather through a delay line", _{
    std::array<int32_t, 10> line = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
    uint32_t read = 7;
    auto taps = Argon<int32_t>::LoadGatherOffsetIndex(line.data(), Argon<uint32_t>::CircularIndices(read, 10));
    expect(taps.to_array()).to_equal(std::array<int32_t, 4>{70, 80, 90, 0});
    taps = Argon<int32_t>::LoadGatherOffsetIndex(line.data(), Argon<uint32_t>::CircularIndices(read, 10));
    expect(taps.to_array()).to_equal(std::array<int32_t, 4>{10, 20, 30, 40});
  });
});

auto describe_down = describe("CircularIndicesDown", ${
  it("wraps from zero back to the end", _{
    uint32_t offset = 1;
    expect(Argon<uint32_t>::CircularIndicesDown(offset, 6).to_array()).to_equal(std::array<uint32_t, 4>{1, 0, 5, 4});
    expect(offset).to_equal(uint32_t{3});
  });

  it("steps by 2", _{
    uint32_t offset = 0;
    expect(Argon<uint32_t>::CircularIndicesDown<2>(offset, 6).to_array()).to_equal(std::array<uint32_t, 4>{0, 4, 2, 0});
    expect(offset).to_equal(uint32_t{4});
  });
});

CPPSPEC_MAIN(
  describe_up,
  describe_down
);
