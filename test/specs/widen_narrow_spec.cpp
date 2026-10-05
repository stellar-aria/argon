#include "argon.hpp"
#include "cppspec.hpp"
#include <array>
#include <cstdint>
#include <limits>

// clang-format off

template <typename N>
std::array<N, 16> narrow_sample() {
  std::array<N, 16> out{};
  const N values[] = {std::numeric_limits<N>::min(), std::numeric_limits<N>::max(), N(0), N(1), N(-1), N(42), N(-42), N(7)};
  for (size_t i = 0; i < 16; ++i) out[i] = values[(i * 3) % 8];
  return out;
}

template <typename N, typename W>
void check_load_store(auto& self) {
  constexpr size_t lanes = Argon<W>::lanes;
  auto src = narrow_sample<N>();
  std::array<W, lanes> expected{};
  for (size_t i = 0; i < lanes; ++i) expected[i] = static_cast<W>(src[i]);
  expect(Argon<W>::LoadWiden(src.data()).to_array()).to_equal(expected);

  // predicated: inactive lanes are zero
  auto active = Argon<W>::argon_bool_type::FirstN(lanes / 2 + 1);
  auto partial = expected;
  for (size_t i = lanes / 2 + 1; i < lanes; ++i) partial[i] = 0;
  expect(Argon<W>::LoadWiden(src.data(), active).to_array()).to_equal(partial);

  // store keeps the low bits; predicated store leaves the rest of the buffer alone
  std::array<W, lanes> wide{};
  for (size_t i = 0; i < lanes; ++i) wide[i] = static_cast<W>(static_cast<W>(i * 1000003u) ^ static_cast<W>(0x5A5A5A5Au));
  auto v = Argon<W>::Load(wide.data());
  std::array<N, 16> out{}, out_expected{};
  out.fill(N(99)); out_expected.fill(N(99));
  v.StoreNarrow(out.data());
  for (size_t i = 0; i < lanes; ++i) out_expected[i] = static_cast<N>(wide[i]);
  expect(out).to_equal(out_expected);
  out.fill(N(99)); out_expected.fill(N(99));
  v.StoreNarrow(out.data(), active);
  for (size_t i = 0; i < lanes / 2 + 1; ++i) out_expected[i] = static_cast<N>(wide[i]);
  expect(out).to_equal(out_expected);
}

template <typename N, typename W>
void check_gather_scatter(auto& self) {
  constexpr size_t lanes = Argon<W>::lanes;
  using O = typename Argon<W>::offset_type::scalar_type;
  std::array<N, 64> table{};
  for (size_t i = 0; i < table.size(); ++i) table[i] = static_cast<N>(i * 37 - 500);
  std::array<O, lanes> idx{};
  for (size_t i = 0; i < lanes; ++i) idx[i] = static_cast<O>((i * 13 + 5) % 64);
  auto offsets = Argon<O>::Load(idx.data());
  std::array<W, lanes> expected{};
  for (size_t i = 0; i < lanes; ++i) expected[i] = static_cast<W>(table[idx[i]]);
  expect(Argon<W>::LoadGatherOffsetIndexWiden(table.data(), offsets).to_array()).to_equal(expected);
  std::array<O, lanes> bytes{};
  for (size_t i = 0; i < lanes; ++i) bytes[i] = static_cast<O>(idx[i] * sizeof(N));
  expect(Argon<W>::LoadGatherOffsetBytesWiden(table.data(), Argon<O>::Load(bytes.data())).to_array()).to_equal(expected);

  std::array<N, 64> out{}, out_expected{};
  auto v = Argon<W>::LoadWiden(narrow_sample<N>().data());
  v.StoreScatterOffsetIndexNarrow(out.data(), offsets);
  const auto values = v.to_array();
  for (size_t i = 0; i < lanes; ++i) out_expected[idx[i]] = static_cast<N>(values[i]);
  expect(out).to_equal(out_expected);

  // predicated gather: inactive lanes are zero
  auto active = Argon<W>::argon_bool_type::FirstN(1);
  auto first = Argon<W>::LoadGatherOffsetIndexWiden(table.data(), offsets, active).to_array();
  expect(first[0]).to_equal(expected[0]);
  expect(first[lanes - 1]).to_equal(W(0));
}

auto describe_load_store = describe("LoadWiden / StoreNarrow", ${
  it("int8 into int16 lanes", _{ check_load_store<int8_t, int16_t>(self); });
  it("uint8 into uint16 lanes", _{ check_load_store<uint8_t, uint16_t>(self); });
  it("int8 into int32 lanes", _{ check_load_store<int8_t, int32_t>(self); });
  it("uint8 into uint32 lanes", _{ check_load_store<uint8_t, uint32_t>(self); });
  it("int16 into int32 lanes", _{ check_load_store<int16_t, int32_t>(self); });
  it("uint16 into uint32 lanes", _{ check_load_store<uint16_t, uint32_t>(self); });
  it("uint8 into int32 lanes extends by the source's signedness", _{ check_load_store<uint8_t, int32_t>(self); });
  it("int16 into uint32 lanes extends by the source's signedness", _{ check_load_store<int16_t, uint32_t>(self); });
});

auto describe_gather_scatter = describe("Widening gathers / narrowing scatters", ${
  it("int8 / int16 lanes", _{ check_gather_scatter<int8_t, int16_t>(self); });
  it("uint8 / uint32 lanes", _{ check_gather_scatter<uint8_t, uint32_t>(self); });
  it("int16 / int32 lanes", _{ check_gather_scatter<int16_t, int32_t>(self); });
  it("uint16 / uint32 lanes", _{ check_gather_scatter<uint16_t, uint32_t>(self); });
});

CPPSPEC_MAIN(
  describe_load_store,
  describe_gather_scatter
);
