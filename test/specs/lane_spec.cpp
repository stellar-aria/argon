#include "argon.hpp"
#include "cppspec.hpp"
#include "helpers/type_matrix.hpp"

// clang-format off

// ── GetLane / SetLane ──────────────────────────────────────────────────────

auto describe_get_lane = describe("GetLane", ${
  it("retrieves each lane of an int32 vector by compile-time index", _{
    std::array<int32_t, 4> data = {10, 20, 30, 40};
    auto v = Argon<int32_t>::Load(data.data());
    expect((int32_t)v.template GetLane<0>()).to_equal(10);
    expect((int32_t)v.template GetLane<1>()).to_equal(20);
    expect((int32_t)v.template GetLane<2>()).to_equal(30);
    expect((int32_t)v.template GetLane<3>()).to_equal(40);
  });

  it("retrieves each lane of a uint8 vector by runtime index", _{
    std::array<uint8_t, 16> data;
    std::iota(data.begin(), data.end(), uint8_t{0});
    auto v = Argon<uint8_t>::Load(data.data());
    for (int i = 0; i < 16; ++i)
      expect((int)(uint8_t)v.GetLane(i)).to_equal(i);
  });
});

auto describe_set_lane = describe("SetLane", ${
  it("sets a specific int32 lane without affecting others", _{
    auto v = Argon<int32_t>::FromScalar(0);
    auto modified = v.template GetLane<2>().Set(99);
    auto arr = modified.to_array();
    expect(arr[0]).to_equal(0);
    expect(arr[1]).to_equal(0);
    expect(arr[2]).to_equal(99);
    expect(arr[3]).to_equal(0);
  });
});

// ── Lane::Load — regression for in-place mutation ──────────────────────────
// The lane accessors (both compile-time GetLane<N>() and runtime operator[])
// MUTATE the vector they are bound to, so callers may discard the returned
// vector — exactly as `operator=` does. A regression here (Load returning the
// updated vector but not writing it back to vec_) silently produced zeroed
// wavetable reads on the SIMDe backend — `readValue[i].Load(addr)` in a
// per-lane gather left the vector at 0 — while passing on native NEON, which
// silenced the DelugeFirmware oscillators. These pin the mutation contract.
auto describe_lane_load = describe("Lane::Load", ${
  it("compile-time GetLane<N>().Load() mutates the vector in place (return discarded)", _{
    std::array<int32_t, 4> data = {10, 20, 30, 40};
    int32_t src = 222;
    auto v = Argon<int32_t>::Load(data.data());
    v.template GetLane<1>().Load(&src);
    expect(v.to_array()).to_equal(std::array<int32_t, 4>{10, 222, 30, 40});
  });

  it("GetLane<N>().Load() also returns the updated vector", _{
    std::array<int32_t, 4> data = {10, 20, 30, 40};
    int32_t src = 222;
    auto v = Argon<int32_t>::Load(data.data());
    auto r = v.template GetLane<1>().Load(&src);
    expect(r.to_array()).to_equal(std::array<int32_t, 4>{10, 222, 30, 40});
  });

  it("runtime operator[].Load() loads every lane in place (wavetable-gather pattern)", _{
    std::array<int32_t, 4> data = {0, 0, 0, 0};
    std::array<int32_t, 4> src = {111, 222, 333, 444};
    auto v = Argon<int32_t>::Load(data.data());
    for (int i = 0; i < 4; ++i)
      v[i].Load(&src[i]);
    expect(v.to_array()).to_equal(std::array<int32_t, 4>{111, 222, 333, 444});
  });

  it("loads into a uint32 quadword (oscillator readValue type)", _{
    std::array<uint32_t, 4> data = {0, 0, 0, 0};
    std::array<uint32_t, 4> src = {0xAAAA0001u, 0xBBBB0002u, 0xCCCC0003u, 0xDDDD0004u};
    auto v = Argon<uint32_t>::Load(data.data());
    for (int i = 0; i < 4; ++i)
      v[i].Load(&src[i]);
    expect(v.to_array()).to_equal(src);
  });

  it("loads into a uint16 half-vector (oscillator strength type)", _{
    std::array<uint16_t, 4> data = {0, 0, 0, 0};
    std::array<uint16_t, 4> src = {11, 22, 33, 44};
    auto v = ArgonHalf<uint16_t>::Load(data.data());
    for (int i = 0; i < 4; ++i)
      v[i].Load(&src[i]);
    expect(v.to_array()).to_equal(src);
  });
});

// ── Lane mutation — operator= / Set write in place ─────────────────────────
auto describe_lane_mutation = describe("Lane mutation", ${
  it("operator[] = scalar mutates the vector in place (return discarded)", _{
    auto v = Argon<int32_t>::FromScalar(0);
    v[2] = 99;
    expect(v.to_array()).to_equal(std::array<int32_t, 4>{0, 0, 99, 0});
  });

  it("compile-time GetLane<N>() = scalar mutates the vector in place", _{
    auto v = Argon<int32_t>::FromScalar(0);
    v.template GetLane<3>() = 7;
    expect(v.to_array()).to_equal(std::array<int32_t, 4>{0, 0, 0, 7});
  });

  it("half-vector lane assignment mutates in place", _{
    auto v = ArgonHalf<uint16_t>::FromScalar(0);
    for (uint16_t i = 0; i < 4; ++i)
      v[i] = static_cast<uint16_t>(i * 10 + 1);
    expect(v.to_array()).to_equal(std::array<uint16_t, 4>{1, 11, 21, 31});
  });
});

// ── DuplicateLane ──────────────────────────────────────────────────────────

auto describe_duplicate_lane = describe("DuplicateLane", ${
  it("broadcasts lane 2 of int32 across all lanes", _{
    std::array<int32_t, 4> data = {1, 2, 7, 4};
    auto v = Argon<int32_t>::Load(data.data());
    auto dup = Argon<int32_t>::FromLane(v.template GetLane<2>());
    auto arr = dup.to_array();
    for (auto x : arr)
      expect(x).to_equal(7);
  });

  it("broadcasts lane 0 of float across all lanes", _{
    std::array<float, 4> data = {3.14f, 1.0f, 2.0f, 5.0f};
    auto v = Argon<float>::Load(data.data());
    auto dup = Argon<float>::FromLane(v.template GetLane<0>());
    auto arr = dup.to_array();
    for (auto x : arr)
      expect(x).to_equal(3.14f);
  });
});

// ── Extract ────────────────────────────────────────────────────────────────

auto describe_extract = describe("Extract", ${
  it("extracts int32 with offset 1: result is a[1..3] ++ b[0]", _{
    std::array<int32_t, 4> a_arr = {1, 2, 3, 4};
    std::array<int32_t, 4> b_arr = {10, 20, 30, 40};
    auto a = Argon<int32_t>::Load(a_arr.data());
    auto b = Argon<int32_t>::Load(b_arr.data());
    // vextq_s32(a, b, 1) = {a[1], a[2], a[3], b[0]} = {2, 3, 4, 10}
    auto result = a.template Extract<1>(b).to_array();
    expect(result).to_equal(std::array<int32_t, 4>{2, 3, 4, 10});
  });
});

// ── Reverse ────────────────────────────────────────────────────────────────

auto describe_reverse = describe("Reverse64bit", ${
  it("reverses int32 elements within each 64-bit word", _{
    std::array<int32_t, 4> data = {1, 2, 3, 4};
    auto v = Argon<int32_t>::Load(data.data());
    // Reverse64bit: reverses within each 64-bit chunk
    // [1,2] → [2,1], [3,4] → [4,3]
    auto result = v.Reverse64bit().to_array();
    expect(result).to_equal(std::array<int32_t, 4>{2, 1, 4, 3});
  });
});

// ── Zip / Unzip ────────────────────────────────────────────────────────────

auto describe_zip = describe("ZipWith", ${
  it("zips two int16 vectors into low and high interleaved parts", _{
    std::array<int16_t, 8> a_arr = {1, 2, 3, 4, 5, 6, 7, 8};
    std::array<int16_t, 8> b_arr = {10, 20, 30, 40, 50, 60, 70, 80};
    auto a = Argon<int16_t>::Load(a_arr.data());
    auto b = Argon<int16_t>::Load(b_arr.data());
    auto [lo, hi] = a.ZipWith(b);
    // lo: {1,10, 2,20, 3,30, 4,40}  hi: {5,50, 6,60, 7,70, 8,80}
    auto lo_arr = lo.to_array();
    auto hi_arr = hi.to_array();
    expect(lo_arr[0]).to_equal(int16_t{1});
    expect(lo_arr[1]).to_equal(int16_t{10});
    expect(hi_arr[0]).to_equal(int16_t{5});
    expect(hi_arr[1]).to_equal(int16_t{50});
  });
});

auto describe_unzip = describe("UnzipWith", ${
  it("UnzipWith is the inverse of ZipWith for int16", _{
    std::array<int16_t, 8> a_arr = {1, 2, 3, 4, 5, 6, 7, 8};
    std::array<int16_t, 8> b_arr = {10, 20, 30, 40, 50, 60, 70, 80};
    auto a = Argon<int16_t>::Load(a_arr.data());
    auto b = Argon<int16_t>::Load(b_arr.data());
    auto [lo, hi] = a.ZipWith(b);
    auto [ra, rb] = lo.UnzipWith(hi);
    expect(ra.to_array()).to_equal(a_arr);
    expect(rb.to_array()).to_equal(b_arr);
  });
});

// ── Transpose ──────────────────────────────────────────────────────────────

auto describe_transpose = describe("TransposeWith", ${
  it("transposes two 2x2 int32 matrices packed in vectors", _{
    std::array<int32_t, 4> a_arr = {1, 2, 3, 4};
    std::array<int32_t, 4> b_arr = {5, 6, 7, 8};
    auto a = Argon<int32_t>::Load(a_arr.data());
    auto b = Argon<int32_t>::Load(b_arr.data());
    auto [t0, t1] = a.TransposeWith(b);
    // vtrnq_s32: t0 = {a[0],b[0], a[2],b[2]} = {1,5,3,7}
    //            t1 = {a[1],b[1], a[3],b[3]} = {2,6,4,8}
    expect(t0.to_array()).to_equal(std::array<int32_t, 4>{1, 5, 3, 7});
    expect(t1.to_array()).to_equal(std::array<int32_t, 4>{2, 6, 4, 8});
  });
});

CPPSPEC_MAIN(
  describe_get_lane,
  describe_set_lane,
  describe_lane_load,
  describe_lane_mutation,
  describe_duplicate_lane,
  describe_extract,
  describe_reverse,
  describe_zip,
  describe_unzip,
  describe_transpose
);

