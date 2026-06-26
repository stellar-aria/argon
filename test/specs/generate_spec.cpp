#include "argon.hpp"
#include "cppspec.hpp"
#include "helpers/type_matrix.hpp"
#include <array>

// clang-format off

// Coverage for the lane-generator factories Generate / GenerateWithIndex.

// ── Generate ────────────────────────────────────────────────────────────────

auto describe_generate = describe("Generate", ${
  it("fills lanes from a stateful generator, in lane order", _{
    int counter = 0;
    auto v = Argon<int32_t>::Generate([&counter]() { return ++counter; }).to_array();
    expect(v).to_equal(std::array<int32_t, 4>{1, 2, 3, 4});
  });

  it("fills every lane with a constant (float)", _{
    auto v = Argon<float>::Generate([]() { return 2.5f; }).to_array();
    for (auto x : v)
      expect(x).to_equal(2.5f);
  });
});

// ── GenerateWithIndex ───────────────────────────────────────────────────────

auto describe_generate_with_index = describe("GenerateWithIndex", ${
  it("fills each lane from its index (int32 squares)", _{
    auto v = Argon<int32_t>::GenerateWithIndex([](int32_t i) { return i * i; }).to_array();
    expect(v).to_equal(std::array<int32_t, 4>{0, 1, 4, 9});
  });

  it("fills each lane from its index (uint8)", _{
    auto v = Argon<uint8_t>::GenerateWithIndex([](uint8_t i) -> uint8_t { return i * 2; }).to_array();
    for (size_t i = 0; i < Argon<uint8_t>::lanes; ++i)
      expect((int)v[i]).to_equal((int)(i * 2));
  });
});

CPPSPEC_MAIN(
  describe_generate,
  describe_generate_with_index
);
