#include "argon.hpp"
#include "cppspec.hpp"

// clang-format off

// ── ReduceAdd ──────────────────────────────────────────────────────────────

auto describe_reduce_add_int32 = describe("ReduceAdd int32", ${
  it("sums all lanes of an int32 vector", _{
    std::array<int32_t, 4> data = {1, 2, 3, 4};
    auto v = Argon<int32_t>::Load(data.data());
    expect(v.ReduceAdd()).to_equal(10);
  });

  it("sums all lanes of an int32 vector (iota, larger)", _{
    // 1+2+...+4 = 10
    std::array<int32_t, 4> data;
    std::iota(data.begin(), data.end(), 1);
    auto v = Argon<int32_t>::Load(data.data());
    expect(v.ReduceAdd()).to_equal(10);
  });
});

auto describe_reduce_add_float = describe("ReduceAdd float", ${
  it("sums all lanes of a float vector", _{
    std::array<float, 4> data = {1.0f, 2.0f, 3.0f, 4.0f};
    auto v = Argon<float>::Load(data.data());
    expect(v.ReduceAdd()).to_equal(10.0f);
  });
});

// ── ReduceMax ──────────────────────────────────────────────────────────────

auto describe_reduce_max_int32 = describe("ReduceMax int32", ${
  it("returns the maximum lane of an int32 vector", _{
    std::array<int32_t, 4> data = {3, 7, 1, 5};
    auto v = Argon<int32_t>::Load(data.data());
    expect(v.ReduceMax()).to_equal(7);
  });

  it("returns the maximum lane with negative values", _{
    std::array<int32_t, 4> data = {-3, -7, -1, -5};
    auto v = Argon<int32_t>::Load(data.data());
    expect(v.ReduceMax()).to_equal(-1);
  });
});

auto describe_reduce_max_float = describe("ReduceMax float", ${
  it("returns the maximum lane of a float vector", _{
    std::array<float, 4> data = {3.0f, 7.0f, 1.0f, 5.0f};
    auto v = Argon<float>::Load(data.data());
    expect(v.ReduceMax()).to_equal(7.0f);
  });
});

// On the host (non-AArch64) path, ReduceAdd/ReduceMax fold via Reduce(), whose
// fold depth depends on the lane count: 8-lane types add a Reverse32bit step and
// 16-lane types add a Reverse16bit step on top of the 4-lane Reverse64bit fold.
// These cover those wider-lane fold arms.

auto describe_reduce_add_wide = describe("ReduceAdd wide lanes", ${
  it("sums all 8 lanes of a uint16 vector (Reverse32bit fold arm)", _{
    std::array<uint16_t, 8> data;
    std::iota(data.begin(), data.end(), uint16_t{1});  // 1..8 -> 36
    auto v = Argon<uint16_t>::Load(data.data());
    expect(v.ReduceAdd()).to_equal(uint16_t{36});
  });

  it("sums all 16 lanes of a uint8 vector (Reverse16bit fold arm)", _{
    std::array<uint8_t, 16> data;
    std::iota(data.begin(), data.end(), uint8_t{1});  // 1..16 -> 136, fits uint8
    auto v = Argon<uint8_t>::Load(data.data());
    expect((int)v.ReduceAdd()).to_equal(136);
  });
});

auto describe_reduce_max_wide = describe("ReduceMax wide lanes", ${
  it("returns the max of all 8 lanes of an int16 vector", _{
    std::array<int16_t, 8> data = {3, 7, 1, 5, 2, 8, 4, 6};
    auto v = Argon<int16_t>::Load(data.data());
    expect(v.ReduceMax()).to_equal(int16_t{8});
  });

  it("returns the max of all 16 lanes of an int8 vector", _{
    std::array<int8_t, 16> data = {3, 7, 1, 5, 2, 8, 4, 6, 9, 0, 11, 10, 13, 12, 15, 14};
    auto v = Argon<int8_t>::Load(data.data());
    expect((int)v.ReduceMax()).to_equal(15);
  });
});

// ── ReduceMin ──────────────────────────────────────────────────────────────

auto describe_reduce_min_int32 = describe("ReduceMin int32", ${
  it("returns the minimum lane of an int32 vector", _{
    std::array<int32_t, 4> data = {3, 7, 1, 5};
    auto v = Argon<int32_t>::Load(data.data());
    expect(v.ReduceMin()).to_equal(1);
  });
});

auto describe_reduce_min_float = describe("ReduceMin float", ${
  it("returns the minimum lane of a float vector", _{
    std::array<float, 4> data = {3.0f, 7.0f, 1.0f, 5.0f};
    auto v = Argon<float>::Load(data.data());
    expect(v.ReduceMin()).to_equal(1.0f);
  });
});

CPPSPEC_MAIN(
  describe_reduce_add_int32,
  describe_reduce_add_float,
  describe_reduce_add_wide,
  describe_reduce_max_int32,
  describe_reduce_max_float,
  describe_reduce_max_wide,
  describe_reduce_min_int32,
  describe_reduce_min_float
);
