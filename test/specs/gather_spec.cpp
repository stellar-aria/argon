#include "argon.hpp"
#include "cppspec.hpp"

// clang-format off
auto gather = describe("gather", ${
  std::array<int32_t, 25> data;
  before_each([&]() { std::iota(data.begin(), data.end(), 0); });

  it("Gathers into a new vector from the specified indices", _{
    auto vec = Argon<int32_t>::LoadGatherOffsetIndex(data.data(), Argon<uint32_t>{0u, 5u, 4u, 1u});
    expect(vec.to_array()).to_equal(std::array<int32_t, 4>{0, 5, 4, 1});
  });

  it("Gathers into multiple new vectors from the specified indices", _{
    auto [vec0, vec1] = Argon<int32_t>::LoadGatherOffsetIndexInterleaved<2>(data.data(), Argon<uint32_t>{0u, 5u, 4u, 1u});
    expect(vec0.to_array()).to_equal(std::array<int32_t, 4>{0, 10, 8, 2});
    expect(vec1.to_array()).to_equal(std::array<int32_t, 4>{1, 11, 9, 3});
  });
});

CPPSPEC_MAIN(gather);
