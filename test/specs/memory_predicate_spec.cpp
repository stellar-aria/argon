#include "argon.hpp"
#include "cppspec.hpp"
#include <array>
#include <numeric>

// clang-format off

using P32 = argon::Predicate<Argon<int32_t>::vector_type>;
using P8  = argon::Predicate<Argon<uint8_t>::vector_type>;

// An index far past any buffer: if an inactive lane were read or written, the spec would fault.
constexpr uint32_t kWild = 0x0FFFFFFFu;

// ── Contiguous ─────────────────────────────────────────────────────────────

auto describe_load_store = describe("Predicated Load / StoreTo", ${
  it("loads the active lanes and zeroes the rest", _{
    std::array<int32_t, 4> data = {1, 2, 3, 99};
    auto v = Argon<int32_t>::Load(data.data(), P32::FirstN(3));
    expect(v.to_array()).to_equal(std::array<int32_t, 4>{1, 2, 3, 0});
  });

  it("loads a uint8 tail", _{
    std::array<uint8_t, 16> data{};
    std::iota(data.begin(), data.end(), uint8_t{1});
    auto v = Argon<uint8_t>::Load(data.data(), P8::FirstN(10));
    std::array<uint8_t, 16> expected{};
    std::iota(expected.begin(), expected.begin() + 10, uint8_t{1});
    expect(v.to_array()).to_equal(expected);
  });

  it("stores only the active lanes", _{
    std::array<float, 4> out = {-1.0f, -1.0f, -1.0f, -1.0f};
    auto active = Argon<int32_t>{1, 0, 1, 0} == Argon<int32_t>{1};
    Argon<float>{1.5f, 2.5f, 3.5f, 4.5f}.StoreTo(out.data(), active);
    expect(out).to_equal(std::array<float, 4>{1.5f, -1.0f, 3.5f, -1.0f});
  });

  it("stores a uint8 tail without touching the bytes after it", _{
    std::array<uint8_t, 16> out{};
    out.fill(0xEE);
    Argon<uint8_t>{7}.StoreTo(out.data(), P8::FirstN(5));
    std::array<uint8_t, 16> expected{};
    expected.fill(0xEE);
    for (size_t i = 0; i < 5; ++i) expected[i] = 7;
    expect(out).to_equal(expected);
  });
});

// ── Gather ─────────────────────────────────────────────────────────────────

alignas(16) static std::array<uint16_t, 40001> big_table = [] {
  std::array<uint16_t, 40001> t{};
  for (size_t i = 0; i < t.size(); ++i) t[i] = static_cast<uint16_t>(i * 3);
  return t;
}();

auto describe_gather = describe("Predicated gather", ${
  it("gathers the active lanes by index and never reads the inactive ones", _{
    std::array<int32_t, 8> data = {0, 10, 20, 30, 40, 50, 60, 70};
    auto active = P32::FirstN(2);
    auto v = Argon<int32_t>::LoadGatherOffsetIndex(data.data(), Argon<uint32_t>{7u, 2u, kWild, kWild}, active);
    expect(v.to_array()).to_equal(std::array<int32_t, 4>{70, 20, 0, 0});
  });

  it("gathers the active lanes by byte offset", _{
    std::array<int32_t, 8> data = {0, 10, 20, 30, 40, 50, 60, 70};
    auto active = Argon<int32_t>{0, 1, 0, 1} == Argon<int32_t>{1};
    auto v = Argon<int32_t>::LoadGatherOffsetBytes(data.data(), Argon<uint32_t>{kWild, 4u, kWild, 28u}, active);
    expect(v.to_array()).to_equal(std::array<int32_t, 4>{0, 10, 0, 70});
  });

  it("scales uint16 indices without overflowing 16 bits", _{
    // index * sizeof(uint16_t) exceeds 0xFFFF for these lanes
    auto idx = Argon<uint16_t>{40000, 1, 32768, 2, 39999, 3, 33000, 4};
    auto v = Argon<uint16_t>::LoadGatherOffsetIndex(big_table.data(), idx);
    std::array<uint16_t, 8> expected{};
    auto idx_arr = idx.to_array();
    for (size_t i = 0; i < 8; ++i) expected[i] = big_table[idx_arr[i]];
    expect(v.to_array()).to_equal(expected);
  });
});

// ── Scatter ────────────────────────────────────────────────────────────────

auto describe_scatter = describe("Scatter", ${
  it("scatters every lane by index", _{
    std::array<int32_t, 8> out{};
    Argon<int32_t>{1, 2, 3, 4}.StoreScatterOffsetIndex(out.data(), Argon<uint32_t>{6u, 0u, 3u, 5u});
    expect(out).to_equal(std::array<int32_t, 8>{2, 0, 0, 3, 0, 4, 1, 0});
  });

  it("scatters every lane by byte offset", _{
    std::array<uint16_t, 8> out{};
    Argon<uint16_t>{1, 2, 3, 4, 5, 6, 7, 8}.StoreScatterOffsetBytes(out.data(),
        Argon<uint16_t>{14, 12, 10, 8, 6, 4, 2, 0});
    expect(out).to_equal(std::array<uint16_t, 8>{8, 7, 6, 5, 4, 3, 2, 1});
  });

  it("scatters only the active lanes and never writes the inactive ones", _{
    std::array<float, 4> out = {-1.0f, -1.0f, -1.0f, -1.0f};
    auto active = P32::FirstN(2);
    Argon<float>{1.0f, 2.0f, 3.0f, 4.0f}.StoreScatterOffsetIndex(out.data(), Argon<uint32_t>{3u, 1u, kWild, kWild},
                                                                 active);
    expect(out).to_equal(std::array<float, 4>{-1.0f, 2.0f, -1.0f, 1.0f});
  });

  it("scatters uint8 lanes", _{
    std::array<uint8_t, 32> out{};
    std::array<uint8_t, 16> idx{};
    for (size_t i = 0; i < 16; ++i) idx[i] = static_cast<uint8_t>(31 - 2 * i);
    Argon<uint8_t>::Iota(1).StoreScatterOffsetIndex(out.data(), Argon<uint8_t>::Load(idx.data()));
    std::array<uint8_t, 32> expected{};
    for (size_t i = 0; i < 16; ++i) expected[31 - 2 * i] = static_cast<uint8_t>(i + 1);
    expect(out).to_equal(expected);
  });
});

// ── Reduction ──────────────────────────────────────────────────────────────

auto describe_reduce = describe("Predicated ReduceAdd", ${
  it("sums the active int32 lanes", _{
    auto v = Argon<int32_t>{1, 20, 300, 4000};
    expect(v.ReduceAdd(P32::FirstN(3))).to_equal(321);
    expect(v.ReduceAdd(P32::False())).to_equal(0);
    expect(v.ReduceAdd(P32::True())).to_equal(v.ReduceAdd());
  });

  it("sums the active float lanes", _{
    auto v = Argon<float>{0.5f, 1.5f, 2.5f, 3.5f};
    expect(v.ReduceAdd(v > Argon<float>{1.0f})).to_equal(7.5f);
  });

  it("sums the active uint8 lanes", _{
    expect(Argon<uint8_t>::Iota(1).ReduceAdd(P8::FirstN(10))).to_equal(uint8_t{55});
  });

  it("wraps int8 sums in the lane type, as on NEON", _{
    expect(Argon<int8_t>{10}.ReduceAdd()).to_equal(static_cast<int8_t>(160));
  });
});

CPPSPEC_MAIN(
  describe_load_store,
  describe_gather,
  describe_scatter,
  describe_reduce
);
