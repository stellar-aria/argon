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
  describe_reduce_max_int32,
  describe_reduce_max_float,
  describe_reduce_min_int32,
  describe_reduce_min_float
);
