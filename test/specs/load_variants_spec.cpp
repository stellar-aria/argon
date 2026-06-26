#include "argon.hpp"
#include "cppspec.hpp"
#include "helpers/type_matrix.hpp"
#include <array>
#include <numeric>

// clang-format off

// Coverage for load variants beyond Load / LoadCopy / gather-offset-index
// already exercised in load_store_spec.cpp and gather_spec.cpp.

// ── LoadScalar (alias of LoadCopy: broadcast one scalar) ────────────────────

auto describe_load_scalar = describe("LoadScalar", ${
  it("broadcasts a single scalar across all lanes", _{
    int32_t src = 42;
    auto v = Argon<int32_t>::LoadScalar(&src).to_array();
    for (auto x : v)
      expect(x).to_equal(42);
  });
});

// ── LoadToLane<n> (load one scalar into a single lane) ──────────────────────

auto describe_load_to_lane = describe("LoadToLane", ${
  it("loads a scalar into a specific lane, leaving the rest untouched", _{
    int32_t src = 99;
    auto v = Argon<int32_t>::FromScalar(0).template LoadToLane<2>(&src).to_array();
    expect(v).to_equal(std::array<int32_t, 4>{0, 0, 99, 0});
  });
});

// ── LoadMulti<n> (load n consecutive vectors) ───────────────────────────────

auto describe_load_multi = describe("LoadMulti", ${
  it("loads two consecutive int32 vectors", _{
    std::array<int32_t, 8> data;
    std::iota(data.begin(), data.end(), 0);
    auto multi = Argon<int32_t>::LoadMulti<2>(data.data());
    expect(multi[0].to_array()).to_equal(std::array<int32_t, 4>{0, 1, 2, 3});
    expect(multi[1].to_array()).to_equal(std::array<int32_t, 4>{4, 5, 6, 7});
  });
});

// ── LoadInterleaved<stride> (de-interleave) ─────────────────────────────────

auto describe_load_interleaved = describe("LoadInterleaved", ${
  it("de-interleaves a stride-2 stream into two vectors", _{
    std::array<int32_t, 8> data = {0, 1, 2, 3, 4, 5, 6, 7};
    auto multi = Argon<int32_t>::LoadInterleaved<2>(data.data());
    expect(multi[0].to_array()).to_equal(std::array<int32_t, 4>{0, 2, 4, 6});
    expect(multi[1].to_array()).to_equal(std::array<int32_t, 4>{1, 3, 5, 7});
  });
});

// ── LoadCopyInterleaved<stride> (de-interleave + duplicate) ─────────────────

auto describe_load_copy_interleaved = describe("LoadCopyInterleaved", ${
  it("duplicates the first stride elements across each vector", _{
    std::array<int32_t, 8> data = {10, 20, 0, 0, 0, 0, 0, 0};
    auto multi = Argon<int32_t>::LoadCopyInterleaved<2>(data.data());
    for (auto x : multi[0].to_array())
      expect(x).to_equal(10);
    for (auto x : multi[1].to_array())
      expect(x).to_equal(20);
  });
});

// ── LoadGatherOffsetBytes (gather by *byte* offset from a base) ──────────────

auto describe_load_gather_offset_bytes = describe("LoadGatherOffsetBytes", ${
  it("gathers int32 lanes from base + byte offsets", _{
    std::array<int32_t, 10> data;
    std::iota(data.begin(), data.end(), 0);
    // byte offsets {0, 8, 4, 12} -> element indices {0, 2, 1, 3}
    auto offsets = Argon<uint32_t>{0u, 8u, 4u, 12u};
    auto v = Argon<int32_t>::LoadGatherOffsetBytes(data.data(), offsets).to_array();
    expect(v).to_equal(std::array<int32_t, 4>{0, 2, 1, 3});
  });
});

CPPSPEC_MAIN(
  describe_load_scalar,
  describe_load_to_lane,
  describe_load_multi,
  describe_load_interleaved,
  describe_load_copy_interleaved,
  describe_load_gather_offset_bytes
);
