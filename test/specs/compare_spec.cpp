#include "argon.hpp"
#include "cppspec.hpp"
#include "helpers/type_matrix.hpp"

// clang-format off

// ── Equal / NotEqual ───────────────────────────────────────────────────────

auto describe_equal = describe("Equal", ${
  it("equal int32 lanes produce all-ones mask", _{
    auto a = Argon<int32_t>::FromScalar(5);
    auto b = Argon<int32_t>::FromScalar(5);
    auto mask = (a == b).to_array();
    for (auto v : mask)
      expect(v).to_equal(uint32_t{0xFFFFFFFFu});
  });

  it("unequal int32 lanes produce zero mask", _{
    auto a = Argon<int32_t>::FromScalar(5);
    auto b = Argon<int32_t>::FromScalar(6);
    auto mask = (a == b).to_array();
    for (auto v : mask)
      expect(v).to_equal(uint32_t{0u});
  });
});

auto describe_not_equal = describe("NotEqual", ${
  it("unequal uint16 lanes produce all-ones mask", _{
    auto a = Argon<uint16_t>::FromScalar(1u);
    auto b = Argon<uint16_t>::FromScalar(2u);
    auto mask = (a != b).to_array();
    for (auto v : mask)
      expect(v).to_equal(uint16_t{0xFFFFu});
  });
});

// ── Ordered comparisons ────────────────────────────────────────────────────

auto describe_less_than = describe("LessThan", ${
  it("int32: 1 < 2 is all-ones, 2 < 1 is zero", _{
    auto a = Argon<int32_t>::FromScalar(1);
    auto b = Argon<int32_t>::FromScalar(2);
    auto lt = (a < b).to_array();
    auto gt = (b < a).to_array();
    for (auto v : lt) expect(v).to_equal(uint32_t{0xFFFFFFFFu});
    for (auto v : gt) expect(v).to_equal(uint32_t{0u});
  });

  it("float: -1.f < 0.f is all-ones", _{
    auto a = Argon<float>::FromScalar(-1.0f);
    auto b = Argon<float>::FromScalar(0.0f);
    auto mask = (a < b).to_array();
    for (auto v : mask)
      expect(v).to_equal(uint32_t{0xFFFFFFFFu});
  });
});

auto describe_greater_than = describe("GreaterThan", ${
  it("uint32: 10 > 5 is all-ones", _{
    auto a = Argon<uint32_t>::FromScalar(10u);
    auto b = Argon<uint32_t>::FromScalar(5u);
    auto mask = (a > b).to_array();
    for (auto v : mask)
      expect(v).to_equal(uint32_t{0xFFFFFFFFu});
  });
});

auto describe_less_than_or_equal = describe("LessThanOrEqual", ${
  it("int32: a <= a is all-ones", _{
    auto a = Argon<int32_t>::FromScalar(7);
    auto mask = a.LessThanOrEqual(a).to_array();
    for (auto v : mask)
      expect(v).to_equal(uint32_t{0xFFFFFFFFu});
  });
});

auto describe_greater_than_or_equal = describe("GreaterThanOrEqual", ${
  it("int32: a >= a is all-ones", _{
    auto a = Argon<int32_t>::FromScalar(7);
    auto mask = a.GreaterThanOrEqual(a).to_array();
    for (auto v : mask)
      expect(v).to_equal(uint32_t{0xFFFFFFFFu});
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
    auto mask = a.GreaterThan(b).template As<uint32_t>();
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
