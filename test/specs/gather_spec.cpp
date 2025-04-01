#include "argon.hpp"
#include "cppspec.hpp"

// clang-format off
auto gather = describe("gather", ${
  std::array<int, 25> data;
  before_each([&]() { std::iota(data.begin(), data.end(), 0); });

  it("Gathers into a new vector from the specified indices", _{
    auto vec = Argon<int>::LoadGather(data.data(), uint32x4_t{0, 5, 4, 1});
    expect(vec.to_array()).to_equal(std::array{0, 5, 4, 1});
  });

  it("Gathers into multiple new vectors from the specified indices", _{
    auto [vec0, vec1] = Argon<int>::LoadGatherInterleaved<2>(data.data(), uint32x4_t{0, 5, 4, 1});
    expect(vec0.to_array()).to_equal(std::array{0, 5, 4, 1});
    expect(vec1.to_array()).to_equal(std::array{1, 6, 5, 2});
  });
});

CPPSPEC_SPEC(gather);
