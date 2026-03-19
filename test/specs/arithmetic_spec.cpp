#include "argon.hpp"
#include "cppspec.hpp"
#include "helpers/type_matrix.hpp"
#include <numeric>
#include <limits>

// clang-format off

// ── helpers ────────────────────────────────────────────────────────────────

template <typename T>
static auto make_vec(T start = T{1}) {
  constexpr size_t N = Argon<T>::lanes;
  auto arr = argon::test::iota_array<T, N>(start);
  return Argon<T>::Load(arr.data());
}

// ── Add ────────────────────────────────────────────────────────────────────

auto describe_add_int8 = describe("Add int8", ${
  it("adds two int8 vectors lane-wise", _{
    auto a = make_vec<int8_t>(1);
    auto b = make_vec<int8_t>(10);
    auto result = a.Add(b);
    auto arr = result.to_array();
    for (size_t i = 0; i < Argon<int8_t>::lanes; ++i)
      expect((int)arr[i]).to_equal((int)(int8_t(1 + i) + int8_t(10 + i)));
  });
});

auto describe_add_int16 = describe("Add int16", ${
  it("adds two int16 vectors lane-wise", _{
    auto a = make_vec<int16_t>(1);
    auto b = make_vec<int16_t>(100);
    auto result = a.Add(b);
    auto arr = result.to_array();
    for (size_t i = 0; i < Argon<int16_t>::lanes; ++i)
      expect(arr[i]).to_equal(int16_t(int16_t(1 + i) + int16_t(100 + i)));
  });
});

auto describe_add_int32 = describe("Add int32", ${
  it("adds two int32 vectors lane-wise", _{
    auto a = make_vec<int32_t>(1);
    auto b = make_vec<int32_t>(1000);
    auto result = a + b;
    auto arr = result.to_array();
    for (size_t i = 0; i < Argon<int32_t>::lanes; ++i)
      expect(arr[i]).to_equal(int32_t(1 + i) + int32_t(1000 + i));
  });
});

auto describe_add_uint32 = describe("Add uint32", ${
  it("adds two uint32 vectors lane-wise", _{
    auto a = make_vec<uint32_t>(1u);
    auto b = make_vec<uint32_t>(1000u);
    auto result = a + b;
    auto arr = result.to_array();
    for (size_t i = 0; i < Argon<uint32_t>::lanes; ++i)
      expect(arr[i]).to_equal(uint32_t(1 + i) + uint32_t(1000 + i));
  });
});

auto describe_add_float = describe("Add float", ${
  it("adds two float vectors lane-wise", _{
    auto a = make_vec<float>(1.0f);
    auto b = make_vec<float>(10.0f);
    auto result = a + b;
    auto arr = result.to_array();
    for (size_t i = 0; i < Argon<float>::lanes; ++i)
      expect(arr[i]).to_equal(float(1 + i) + float(10 + i));
  });
});

// ── Subtract ───────────────────────────────────────────────────────────────

auto describe_subtract = describe("Subtract", ${
  it("subtracts int32 vectors lane-wise", _{
    auto a = make_vec<int32_t>(10);
    auto b = make_vec<int32_t>(1);
    auto result = a - b;
    auto arr = result.to_array();
    for (size_t i = 0; i < Argon<int32_t>::lanes; ++i)
      expect(arr[i]).to_equal(int32_t(10 + i) - int32_t(1 + i));
  });

  it("subtracts float vectors lane-wise", _{
    auto a = make_vec<float>(10.0f);
    auto b = make_vec<float>(1.0f);
    auto result = a - b;
    auto arr = result.to_array();
    for (size_t i = 0; i < Argon<float>::lanes; ++i)
      expect(arr[i]).to_equal(float(10 + i) - float(1 + i));
  });
});

// ── Multiply ───────────────────────────────────────────────────────────────

auto describe_multiply = describe("Multiply", ${
  it("multiplies int16 vectors lane-wise", _{
    auto a = make_vec<int16_t>(1);
    auto b = make_vec<int16_t>(2);
    auto result = a * b;
    auto arr = result.to_array();
    for (size_t i = 0; i < Argon<int16_t>::lanes; ++i)
      expect(arr[i]).to_equal(int16_t(int16_t(1 + i) * int16_t(2 + i)));
  });

  it("multiplies uint32 vectors by a scalar", _{
    constexpr uint32_t factor = 3u;
    auto a = make_vec<uint32_t>(1u);
    auto result = a.Multiply(factor);
    auto arr = result.to_array();
    for (size_t i = 0; i < Argon<uint32_t>::lanes; ++i)
      expect(arr[i]).to_equal(uint32_t(1 + i) * factor);
  });

  it("multiplies float vectors lane-wise", _{
    auto a = make_vec<float>(1.0f);
    auto b = make_vec<float>(2.0f);
    auto result = a * b;
    auto arr = result.to_array();
    for (size_t i = 0; i < Argon<float>::lanes; ++i)
      expect(arr[i]).to_equal(float(1 + i) * float(2 + i));
  });
});

// ── MultiplyAdd ────────────────────────────────────────────────────────────

auto describe_multiply_add = describe("MultiplyAdd", ${
  it("fused multiply-add on int32: a + (b * c)", _{
    auto a = Argon<int32_t>::FromScalar(100);
    auto b = make_vec<int32_t>(1);
    auto c = make_vec<int32_t>(2);
    auto result = a.MultiplyAdd(b, c);
    auto arr = result.to_array();
    for (size_t i = 0; i < Argon<int32_t>::lanes; ++i)
      expect(arr[i]).to_equal(100 + int32_t(1 + i) * int32_t(2 + i));
  });

  it("fused multiply-add on float: a + (b * c)", _{
    auto a = Argon<float>::FromScalar(0.0f);
    auto b = make_vec<float>(1.0f);
    auto c = make_vec<float>(2.0f);
    auto result = a.MultiplyAdd(b, c);
    auto arr = result.to_array();
    for (size_t i = 0; i < Argon<float>::lanes; ++i)
      expect(arr[i]).to_equal(float(1 + i) * float(2 + i));
  });
});

// ── Negate ─────────────────────────────────────────────────────────────────

auto describe_negate = describe("Negate", ${
  it("negates int32 vector", _{
    auto a = make_vec<int32_t>(1);
    auto result = a.Negate();
    auto arr = result.to_array();
    for (size_t i = 0; i < Argon<int32_t>::lanes; ++i)
      expect(arr[i]).to_equal(-int32_t(1 + i));
  });

  it("negates float vector", _{
    auto a = make_vec<float>(1.0f);
    auto result = -a;
    auto arr = result.to_array();
    for (size_t i = 0; i < Argon<float>::lanes; ++i)
      expect(arr[i]).to_equal(-float(1 + i));
  });
});

// ── Absolute ───────────────────────────────────────────────────────────────

auto describe_absolute = describe("Absolute", ${
  it("absolute value of int32 vector", _{
    std::array<int32_t, 4> data = {-3, -1, 2, -4};
    auto a = Argon<int32_t>::Load(data.data());
    auto result = a.Absolute();
    auto arr = result.to_array();
    expect(arr).to_equal(std::array<int32_t, 4>{3, 1, 2, 4});
  });

  it("absolute value of float vector", _{
    std::array<float, 4> data = {-3.0f, -1.0f, 2.0f, -4.0f};
    auto a = Argon<float>::Load(data.data());
    auto result = a.Absolute();
    auto arr = result.to_array();
    expect(arr).to_equal(std::array<float, 4>{3.0f, 1.0f, 2.0f, 4.0f});
  });
});

// ── Saturating ops ─────────────────────────────────────────────────────────

auto describe_saturating = describe("Saturating", ${
  it("AddSaturate clamps int8 at max", _{
    std::array<int8_t, 16> a_arr, b_arr;
    a_arr.fill(std::numeric_limits<int8_t>::max());
    b_arr.fill(1);
    auto a = Argon<int8_t>::Load(a_arr.data());
    auto b = Argon<int8_t>::Load(b_arr.data());
    auto result = a.AddSaturate(b);
    auto arr = result.to_array();
    for (auto v : arr)
      expect((int)v).to_equal((int)std::numeric_limits<int8_t>::max());
  });

  it("SubtractSaturate clamps uint16 at zero", _{
    std::array<uint16_t, 8> a_arr, b_arr;
    a_arr.fill(0u);
    b_arr.fill(1u);
    auto a = Argon<uint16_t>::Load(a_arr.data());
    auto b = Argon<uint16_t>::Load(b_arr.data());
    auto result = a.SubtractSaturate(b);
    auto arr = result.to_array();
    for (auto v : arr)
      expect(v).to_equal(uint16_t{0});
  });
});

// ── Halving ops ────────────────────────────────────────────────────────────

auto describe_halving = describe("Halving", ${
  it("AddHalve produces (a + b) / 2 for int32", _{
    std::array<int32_t, 4> a_arr = {2, 4, 6, 8};
    std::array<int32_t, 4> b_arr = {4, 8, 12, 16};
    auto a = Argon<int32_t>::Load(a_arr.data());
    auto b = Argon<int32_t>::Load(b_arr.data());
    auto result = a.AddHalve(b);
    auto arr = result.to_array();
    expect(arr).to_equal(std::array<int32_t, 4>{3, 6, 9, 12});
  });

  it("SubtractHalve produces (a - b) / 2 for int32", _{
    std::array<int32_t, 4> a_arr = {10, 20, 30, 40};
    std::array<int32_t, 4> b_arr = {2, 4, 6, 8};
    auto a = Argon<int32_t>::Load(a_arr.data());
    auto b = Argon<int32_t>::Load(b_arr.data());
    auto result = a.SubtractHalve(b);
    auto arr = result.to_array();
    expect(arr).to_equal(std::array<int32_t, 4>{4, 8, 12, 16});
  });
});

CPPSPEC_MAIN(
  describe_add_int8,
  describe_add_int16,
  describe_add_int32,
  describe_add_uint32,
  describe_add_float,
  describe_subtract,
  describe_multiply,
  describe_multiply_add,
  describe_negate,
  describe_absolute,
  describe_saturating,
  describe_halving
);
