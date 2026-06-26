#include "argon.hpp"
#include "cppspec.hpp"
#include "helpers/type_matrix.hpp"
#include <numeric>

// clang-format off

// ── Load / StoreTo round-trip ──────────────────────────────────────────────

auto describe_load_store_int32 = describe("Load/Store int32", ${
  it("round-trips int32 data through a vector", _{
    std::array<int32_t, 4> data = {11, 22, 33, 44};
    auto v = Argon<int32_t>::Load(data.data());
    std::array<int32_t, 4> out{};
    v.StoreTo(out.data());
    expect(out).to_equal(data);
  });
});

auto describe_load_store_uint8 = describe("Load/Store uint8", ${
  it("round-trips uint8 data through a vector", _{
    std::array<uint8_t, 16> data;
    std::iota(data.begin(), data.end(), uint8_t{0});
    auto v = Argon<uint8_t>::Load(data.data());
    std::array<uint8_t, 16> out{};
    v.StoreTo(out.data());
    expect(out).to_equal(data);
  });
});

auto describe_load_store_float = describe("Load/Store float", ${
  it("round-trips float data through a vector", _{
    std::array<float, 4> data = {1.1f, 2.2f, 3.3f, 4.4f};
    auto v = Argon<float>::Load(data.data());
    std::array<float, 4> out{};
    v.StoreTo(out.data());
    expect(out).to_equal(data);
  });
});

// ── LoadCopy ───────────────────────────────────────────────────────────────

auto describe_load_copy = describe("LoadCopy", ${
  it("duplicates a scalar int32 across all lanes", _{
    int32_t val = 42;
    auto v = Argon<int32_t>::LoadCopy(&val);
    for (auto x : v.to_array())
      expect(x).to_equal(42);
  });

  it("duplicates a scalar float across all lanes", _{
    float val = 3.14f;
    auto v = Argon<float>::LoadCopy(&val);
    for (auto x : v.to_array())
      expect(x).to_equal(3.14f);
  });
});

// ── FromScalar / Iota ──────────────────────────────────────────────────────

auto describe_from_scalar = describe("FromScalar", ${
  it("fills all int32 lanes with the given scalar", _{
    auto v = Argon<int32_t>::FromScalar(7);
    for (auto x : v.to_array())
      expect(x).to_equal(7);
  });
});

auto describe_iota = describe("Iota", ${
  it("fills int32 lanes with 0,1,2,3", _{
    auto v = Argon<int32_t>::Iota(0);
    auto arr = v.to_array();
    for (size_t i = 0; i < Argon<int32_t>::lanes; ++i)
      expect(arr[i]).to_equal((int32_t)i);
  });

  it("fills uint8 lanes with 0..15", _{
    auto v = Argon<uint8_t>::Iota(0);
    auto arr = v.to_array();
    for (size_t i = 0; i < Argon<uint8_t>::lanes; ++i)
      expect((int)arr[i]).to_equal((int)i);
  });
});

// ── StoreLaneTo ────────────────────────────────────────────────────────────

auto describe_store_lane = describe("StoreLaneTo", ${
  it("stores lane 2 of int32 vector to a scalar", _{
    std::array<int32_t, 4> data = {10, 20, 30, 40};
    auto v = Argon<int32_t>::Load(data.data());
    int32_t out = 0;
    v.template StoreLaneTo<2>(&out);
    expect(out).to_equal(30);
  });
});

// ── GetHigh / GetLow / Combine (Argon 128-bit) ─────────────────────────────

#ifndef ARGON_PLATFORM_MVE
auto describe_get_high_low = describe("GetHigh/GetLow/Combine", ${
  it("GetHigh returns the upper half of an int32 vector", _{
    std::array<int32_t, 4> data = {1, 2, 3, 4};
    auto v = Argon<int32_t>::Load(data.data());
    auto hi = v.GetHigh().to_array();
    expect(hi).to_equal(std::array<int32_t, 2>{3, 4});
  });

  it("GetLow returns the lower half of an int32 vector", _{
    std::array<int32_t, 4> data = {1, 2, 3, 4};
    auto v = Argon<int32_t>::Load(data.data());
    auto lo = v.GetLow().to_array();
    expect(lo).to_equal(std::array<int32_t, 2>{1, 2});
  });

  it("Combine(low, high) reconstructs the original 128-bit vector", _{
    std::array<int32_t, 4> data = {5, 6, 7, 8};
    auto v   = Argon<int32_t>::Load(data.data());
    auto lo  = v.GetLow();
    auto hi  = v.GetHigh();
    auto rec = Argon<int32_t>::Combine(lo, hi);
    expect(rec.to_array()).to_equal(data);
  });
});
#endif

// Preprocessor directives inside a macro invocation are UB (and break MSVC's
// preprocessor), so fold the conditional spec into a macro expanded in-place.
#ifndef ARGON_PLATFORM_MVE
#define MAYBE_GET_HIGH_LOW , describe_get_high_low
#else
#define MAYBE_GET_HIGH_LOW
#endif

CPPSPEC_MAIN(
  describe_load_store_int32,
  describe_load_store_uint8,
  describe_load_store_float,
  describe_load_copy,
  describe_from_scalar,
  describe_iota,
  describe_store_lane
  MAYBE_GET_HIGH_LOW
);
