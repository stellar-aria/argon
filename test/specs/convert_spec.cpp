#include "argon.hpp"
#include "cppspec.hpp"
#include "helpers/type_matrix.hpp"

// clang-format off

// ── ConvertTo: int → float ─────────────────────────────────────────────────

auto describe_convert_int_to_float = describe("ConvertTo int32→float", ${
  it("converts int32 vector to float32 lane-wise", _{
    std::array<int32_t, 4> data = {1, 2, 3, 4};
    auto v = Argon<int32_t>::Load(data.data());
    auto result = v.template ConvertTo<float>().to_array();
    expect(result).to_equal(std::array<float, 4>{1.0f, 2.0f, 3.0f, 4.0f});
  });
});

// ── ConvertTo: float → int ─────────────────────────────────────────────────

auto describe_convert_float_to_int = describe("ConvertTo float32→int32", ${
  it("converts float32 vector to int32 (truncating)", _{
    std::array<float, 4> data = {1.7f, 2.3f, 3.9f, 4.1f};
    auto v = Argon<float>::Load(data.data());
    auto result = v.template ConvertTo<int32_t>().to_array();
    // NEON vcvtq_s32_f32 truncates toward zero
    expect(result[0]).to_equal(1);
    expect(result[1]).to_equal(2);
    expect(result[2]).to_equal(3);
    expect(result[3]).to_equal(4);
  });
});

// ── As: bitcast reinterpretation ───────────────────────────────────────────

auto describe_as_bitcast = describe("As bitcast", ${
  it("reinterprets int32 bits as uint32 without changing register contents", _{
    std::array<int32_t, 4> data = {-1, -1, -1, -1};
    auto v = Argon<int32_t>::Load(data.data());
    auto result = v.template As<uint32_t>().to_array();
    for (auto x : result)
      expect(x).to_equal(uint32_t{0xFFFFFFFFu});
  });

  it("reinterprets uint32 bits back to int32", _{
    std::array<uint32_t, 4> data = {0x3F800000u, 0x3F800000u, 0x3F800000u, 0x3F800000u};
    // 0x3F800000 is the IEEE 754 representation of 1.0f
    auto v = Argon<uint32_t>::Load(data.data());
    auto as_float = v.template As<float>().to_array();
    for (auto x : as_float)
      expect(x).to_equal(1.0f);
  });
});

// ── Narrow / Widen chain ───────────────────────────────────────────────────

auto describe_saturate_narrow = describe("SaturateNarrow int32→int16", ${
  it("saturate-narrows int32 vector into int16 (values stay in range)", _{
    // Values in [-32768, 32767] should be preserved
    std::array<int32_t, 4> data = {10, -10, 200, -200};
    auto v = Argon<int32_t>::Load(data.data());
    auto narrow = v.SaturateNarrow().to_array();
    expect(narrow[0]).to_equal(int16_t{10});
    expect(narrow[1]).to_equal(int16_t{-10});
    expect(narrow[2]).to_equal(int16_t{200});
    expect(narrow[3]).to_equal(int16_t{-200});
  });

  it("saturate-narrows int32 to int16 — clamps overflow to INT16_MAX", _{
    std::array<int32_t, 4> data = {0x00020000, 0x00020000, -0x00020000, -0x00020000};
    auto v = Argon<int32_t>::Load(data.data());
    auto narrow = v.SaturateNarrow().to_array();
    expect(narrow[0]).to_equal(std::numeric_limits<int16_t>::max());
    expect(narrow[1]).to_equal(std::numeric_limits<int16_t>::max());
    expect(narrow[2]).to_equal(std::numeric_limits<int16_t>::min());
    expect(narrow[3]).to_equal(std::numeric_limits<int16_t>::min());
  });
});

auto describe_shift_right_narrow = describe("ShiftRightNarrow int32→int16", ${
  it("shifts right by 8 and narrows int32 to int16", _{
    std::array<int32_t, 4> data = {256, 512, 1024, 2048};
    auto v = Argon<int32_t>::Load(data.data());
    auto result = v.template ShiftRightNarrow<8>().to_array();
    expect(result[0]).to_equal(int16_t{1});
    expect(result[1]).to_equal(int16_t{2});
    expect(result[2]).to_equal(int16_t{4});
    expect(result[3]).to_equal(int16_t{8});
  });
});

CPPSPEC_MAIN(
  describe_convert_int_to_float,
  describe_convert_float_to_int,
  describe_as_bitcast,
  describe_saturate_narrow,
  describe_shift_right_narrow
);
