#include "argon.hpp"
#include "cppspec.hpp"
#include "helpers/type_matrix.hpp"
#include <array>

// clang-format off

// Coverage for the NEON table-lookup family (entirely untested).
// These operate on ArgonHalf (doubleword) registers acting as 8-byte tables.

// ── TableLookup ─────────────────────────────────────────────────────────────
// result[i] = (idx[i] < lanes) ? table[idx[i]] : 0

auto describe_table_lookup = describe("TableLookup", ${
  it("looks up in-range indices and zeroes out-of-range ones", _{
    std::array<uint8_t, 8> table_arr = {10, 20, 30, 40, 50, 60, 70, 80};
    std::array<uint8_t, 8> idx_arr   = {0, 2, 4, 7, 8, 100, 1, 3};
    auto table = ArgonHalf<uint8_t>::Load(table_arr.data());
    auto idx   = ArgonHalf<uint8_t>::Load(idx_arr.data());
    auto result = table.TableLookup(idx).to_array();
    expect(result).to_equal(std::array<uint8_t, 8>{10, 30, 50, 80, 0, 0, 20, 40});
  });
});

// ── TableExtension ──────────────────────────────────────────────────────────
// result[i] = (idx[i] < lanes) ? ext[idx[i]] : previous[i]
// The receiver is the "previous" result; out-of-range indices pass through.

auto describe_table_extension = describe("TableExtension", ${
  it("overwrites in-range lookups and keeps prior values for out-of-range", _{
    std::array<uint8_t, 8> prev_arr = {1, 2, 3, 4, 5, 6, 7, 8};
    std::array<uint8_t, 8> ext_arr  = {10, 20, 30, 40, 50, 60, 70, 80};
    std::array<uint8_t, 8> idx_arr  = {0, 2, 8, 100, 4, 9, 1, 3};
    auto prev = ArgonHalf<uint8_t>::Load(prev_arr.data());
    auto ext  = ArgonHalf<uint8_t>::Load(ext_arr.data());
    auto idx  = ArgonHalf<uint8_t>::Load(idx_arr.data());
    auto result = prev.TableExtension(ext, idx).to_array();
    // idx:    0    2    8(oob) 100(oob) 4    9(oob) 1    3
    // result: e[0] e[2] p[2]   p[3]     e[4] p[5]   e[1] e[3]
    expect(result).to_equal(std::array<uint8_t, 8>{10, 30, 3, 4, 50, 6, 20, 40});
  });
});

CPPSPEC_MAIN(
  describe_table_lookup,
  describe_table_extension
);
