#include "argon.hpp"
#include "cppspec.hpp"
#include "helpers/type_matrix.hpp"
#include <array>

// clang-format off

// Coverage for the pairwise-reduction family (entirely untested).
// For two vectors a={a0,a1,...}, b={b0,b1,...}, the pairwise ops reduce
// *adjacent* lanes: result = {f(a0,a1), f(a2,a3), ..., f(b0,b1), f(b2,b3), ...}.
//
// NOTE: pairwise add/max/min map to NEON vpadd/vpmax/vpmin, which are
// doubleword-only before AArch64, so these are exercised on ArgonHalf
// (doubleword) which is portable across A32 and A64.

// ── PairwiseAdd ─────────────────────────────────────────────────────────────

auto describe_pairwise_add = describe("PairwiseAdd", ${
  it("adds adjacent lanes of a then b (int16 doubleword)", _{
    std::array<int16_t, 4> a_arr = {1, 2, 3, 4};
    std::array<int16_t, 4> b_arr = {10, 20, 30, 40};
    auto a = ArgonHalf<int16_t>::Load(a_arr.data());
    auto b = ArgonHalf<int16_t>::Load(b_arr.data());
    auto result = a.PairwiseAdd(b).to_array();
    expect(result).to_equal(std::array<int16_t, 4>{3, 7, 30, 70});
  });

  it("adds adjacent lanes (float doubleword)", _{
    std::array<float, 2> a_arr = {1.f, 2.f};
    std::array<float, 2> b_arr = {10.f, 20.f};
    auto a = ArgonHalf<float>::Load(a_arr.data());
    auto b = ArgonHalf<float>::Load(b_arr.data());
    auto result = a.PairwiseAdd(b).to_array();
    expect(result).to_equal(std::array<float, 2>{3.f, 30.f});
  });
});

// ── PairwiseMax ─────────────────────────────────────────────────────────────

auto describe_pairwise_max = describe("PairwiseMax", ${
  it("takes the max of adjacent lanes (int16 doubleword)", _{
    std::array<int16_t, 4> a_arr = {1, 5, 2, 8};
    std::array<int16_t, 4> b_arr = {9, 3, 7, 4};
    auto a = ArgonHalf<int16_t>::Load(a_arr.data());
    auto b = ArgonHalf<int16_t>::Load(b_arr.data());
    auto result = a.PairwiseMax(b).to_array();
    expect(result).to_equal(std::array<int16_t, 4>{5, 8, 9, 7});
  });
});

// ── PairwiseMin ─────────────────────────────────────────────────────────────

auto describe_pairwise_min = describe("PairwiseMin", ${
  it("takes the min of adjacent lanes (int16 doubleword)", _{
    std::array<int16_t, 4> a_arr = {1, 5, 2, 8};
    std::array<int16_t, 4> b_arr = {9, 3, 7, 4};
    auto a = ArgonHalf<int16_t>::Load(a_arr.data());
    auto b = ArgonHalf<int16_t>::Load(b_arr.data());
    auto result = a.PairwiseMin(b).to_array();
    expect(result).to_equal(std::array<int16_t, 4>{1, 2, 3, 4});
  });
});

// ── PairwiseAddLong (widening pairwise add into a doubleword) ────────────────

auto describe_pairwise_add_long = describe("PairwiseAddLong", ${
  it("pairwise-adds adjacent lanes and widens int16 -> int32", _{
    std::array<int16_t, 4> data = {1, 2, 3, 4};
    auto a = ArgonHalf<int16_t>::Load(data.data());
    auto result = a.PairwiseAddLong().to_array();  // {1+2, 3+4}
    expect(result).to_equal(std::array<int32_t, 2>{3, 7});
  });

  it("accumulates a pairwise-added next-smaller vector into this (VPADAL)", _{
    std::array<int16_t, 4> b_arr = {1, 2, 3, 4};
    auto acc = ArgonHalf<int32_t>::FromScalar(100);  // {100, 100}
    auto b   = ArgonHalf<int16_t>::Load(b_arr.data());
    auto result = acc.PairwiseAddLong(b).to_array();  // {100 + (1+2), 100 + (3+4)}
    expect(result).to_equal(std::array<int32_t, 2>{103, 107});
  });
});

CPPSPEC_MAIN(
  describe_pairwise_add,
  describe_pairwise_max,
  describe_pairwise_min,
  describe_pairwise_add_long
);
