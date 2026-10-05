#include "argon.hpp"
#include "cppspec.hpp"
#include "helpers/type_matrix.hpp"

// clang-format off

// ── Equal / NotEqual ───────────────────────────────────────────────────────
// Comparisons return argon::Predicate; to_array() gives each lane's active state.

auto describe_equal = describe("Equal", ${
  it("is active exactly in the equal int32 lanes", _{
    auto a = Argon<int32_t>{5, 6, 7, 8};
    auto b = Argon<int32_t>{5, 0, 7, 0};
    expect((a == b).to_array()).to_equal(std::array<bool, 4>{true, false, true, false});
  });

  it("is active exactly in the equal uint8 lanes", _{
    std::array<uint8_t, 16> a_arr{}, b_arr{};
    std::array<bool, 16> expected{};
    for (size_t i = 0; i < 16; ++i) {
      a_arr[i] = static_cast<uint8_t>(i);
      b_arr[i] = static_cast<uint8_t>(i % 3 == 0 ? i : 99);
      expected[i] = i % 3 == 0;
    }
    auto a = Argon<uint8_t>::Load(a_arr.data());
    auto b = Argon<uint8_t>::Load(b_arr.data());
    expect((a == b).to_array()).to_equal(expected);
  });

  it("expands to an all-ones / all-zeros mask with ToMask", _{
    auto a = Argon<int32_t>{5, 6, 7, 8};
    auto b = Argon<int32_t>{5, 0, 7, 0};
    expect((a == b).ToMask().to_array()).to_equal(std::array<uint32_t, 4>{0xFFFFFFFFu, 0u, 0xFFFFFFFFu, 0u});
  });
});

auto describe_not_equal = describe("NotEqual", ${
  it("is active exactly in the unequal uint16 lanes", _{
    auto a = Argon<uint16_t>{1, 2, 3, 4, 5, 6, 7, 8};
    auto b = Argon<uint16_t>{1, 0, 3, 0, 5, 0, 7, 0};
    expect((a != b).to_array()).to_equal(std::array<bool, 8>{false, true, false, true, false, true, false, true});
  });
});

// ── Ordered comparisons ────────────────────────────────────────────────────

auto describe_less_than = describe("LessThan", ${
  it("compares signed int32 lanes", _{
    auto a = Argon<int32_t>{-1, 2, 3, -4};
    auto b = Argon<int32_t>{0, 2, -3, 4};
    expect((a < b).to_array()).to_equal(std::array<bool, 4>{true, false, false, true});
  });

  it("compares float lanes", _{
    auto a = Argon<float>{-1.0f, 0.5f, 2.0f, 0.0f};
    auto b = Argon<float>{0.0f, 0.5f, 1.0f, 0.25f};
    expect((a < b).to_array()).to_equal(std::array<bool, 4>{true, false, false, true});
  });

  it("compares unsigned uint16 lanes as unsigned", _{
    auto a = Argon<uint16_t>{1, 0xFFFF, 3, 4, 5, 6, 7, 0x8000};
    auto b = Argon<uint16_t>{2, 1, 3, 5, 4, 7, 6, 1};
    expect((a < b).to_array()).to_equal(std::array<bool, 8>{true, false, false, true, false, true, false, false});
  });
});

auto describe_greater_than = describe("GreaterThan", ${
  it("compares unsigned uint32 lanes as unsigned", _{
    auto a = Argon<uint32_t>{10u, 0x80000000u, 1u, 5u};
    auto b = Argon<uint32_t>{5u, 1u, 2u, 5u};
    expect((a > b).to_array()).to_equal(std::array<bool, 4>{true, true, false, false});
  });

  it("compares signed int8 lanes as signed", _{
    std::array<int8_t, 16> a_arr{}, b_arr{};
    std::array<bool, 16> expected{};
    for (size_t i = 0; i < 16; ++i) {
      a_arr[i] = static_cast<int8_t>(i % 2 ? -100 : 100);
      b_arr[i] = 0;
      expected[i] = i % 2 == 0;
    }
    auto a = Argon<int8_t>::Load(a_arr.data());
    auto b = Argon<int8_t>::Load(b_arr.data());
    expect((a > b).to_array()).to_equal(expected);
  });
});

auto describe_less_than_or_equal = describe("LessThanOrEqual", ${
  it("is active where a <= b", _{
    auto a = Argon<int32_t>{7, 8, 6, 7};
    auto b = Argon<int32_t>{7, 7, 7, 8};
    expect(a.LessThanOrEqual(b).to_array()).to_equal(std::array<bool, 4>{true, false, true, true});
  });
});

auto describe_greater_than_or_equal = describe("GreaterThanOrEqual", ${
  it("is active where a >= b", _{
    auto a = Argon<float>{7.0f, 8.0f, 6.0f, 7.0f};
    auto b = Argon<float>{7.0f, 7.0f, 7.0f, 8.0f};
    expect(a.GreaterThanOrEqual(b).to_array()).to_equal(std::array<bool, 4>{true, true, false, false});
  });
});

// ── Max / Min ──────────────────────────────────────────────────────────────

auto describe_max = describe("Max", ${
  it("max of int32 vectors selects larger lane-wise", _{
    std::array<int32_t, 4> a_arr = {1, 8, 3, 6};
    std::array<int32_t, 4> b_arr = {5, 2, 7, 4};
    auto a = Argon<int32_t>::Load(a_arr.data());
    auto b = Argon<int32_t>::Load(b_arr.data());
    auto result = a.Max(b).to_array();
    expect(result).to_equal(std::array<int32_t, 4>{5, 8, 7, 6});
  });
});

auto describe_min = describe("Min", ${
  it("min of float vectors selects smaller lane-wise", _{
    std::array<float, 4> a_arr = {1.0f, 8.0f, 3.0f, 6.0f};
    std::array<float, 4> b_arr = {5.0f, 2.0f, 7.0f, 4.0f};
    auto a = Argon<float>::Load(a_arr.data());
    auto b = Argon<float>::Load(b_arr.data());
    auto result = a.Min(b).to_array();
    expect(result).to_equal(std::array<float, 4>{1.0f, 2.0f, 3.0f, 4.0f});
  });
});

// ── Ternary / BitwiseSelect blend ─────────────────────────────────────────

auto describe_ternary = describe("Ternary blend via mask", ${
  it("selects either int32 value per lane based on comparison result", _{
    std::array<int32_t, 4> a_arr = {1, 20, 3, 40};
    std::array<int32_t, 4> b_arr = {10, 2, 30, 4};
    auto a = Argon<int32_t>::Load(a_arr.data());
    auto b = Argon<int32_t>::Load(b_arr.data());
    // mask: lanes where a > b
    auto mask = a.GreaterThan(b).ToMask();
    auto ua = a.template As<uint32_t>();
    auto ub = b.template As<uint32_t>();
    auto selected = mask.BitwiseSelect(ua, ub).template As<int32_t>().to_array();
    // lane 0: 1 >  10? no  → 10
    // lane 1: 20> 2?  yes → 20
    // lane 2: 3 > 30? no  → 30
    // lane 3: 40> 4?  yes → 40
    expect(selected).to_equal(std::array<int32_t, 4>{10, 20, 30, 40});
  });
});

CPPSPEC_MAIN(
  describe_equal,
  describe_not_equal,
  describe_less_than,
  describe_greater_than,
  describe_less_than_or_equal,
  describe_greater_than_or_equal,
  describe_max,
  describe_min,
  describe_ternary
);
