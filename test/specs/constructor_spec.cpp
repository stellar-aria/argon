#include <algorithm>
#include "argon.hpp"
#include "cppspec.hpp"
#include "helpers/type_matrix.hpp"

// Constructors whose forms differ by lane width or target: the four-value array, a runtime Lane, and lane access
// on 64-bit lanes.

namespace {
/// Fill the stack the next call's frame will use with a non-zero pattern, so a read past the end of a local
/// array sees the pattern instead of zeroes that happened to be there.
[[gnu::noinline]] void dirty_stack() {
  volatile uint8_t junk[1024];
  for (auto& byte : junk)
    byte = 0xA5;
}

/// Argon<S>(std::array<S, 4>), out of line on a dirtied stack: the array is a local of this frame.
template <typename S>
[[gnu::noinline]] std::array<S, Argon<S>::lanes> from_four(std::array<S, 4> values) {
  return Argon<S>{values}.to_array();
}

/// Lanes widened for printing: an 8-bit lane would print as a character.
template <typename S>
using Shown = std::conditional_t<std::is_integral_v<S>, int, S>;

/// The lanes Argon<S>(std::array<S, 4>{1, 2, 3, 4}) should hold: the four values, then zeroes.
template <typename S>
std::array<Shown<S>, Argon<S>::lanes> four_then_zeroes() {
  std::array<Shown<S>, Argon<S>::lanes> expected{};
  for (size_t i = 0; i < 4 && i < expected.size(); ++i)
    expected[i] = static_cast<Shown<S>>(i + 1);
  return expected;
}

/// The lanes Argon<S>(std::array<S, 4>{1, 2, 3, 4}) holds, built on a dirtied stack.
template <typename S>
std::array<Shown<S>, Argon<S>::lanes> construct_from_four() {
  dirty_stack();
  const auto lanes = from_four<S>({1, 2, 3, 4});
  std::array<Shown<S>, Argon<S>::lanes> shown{};
  for (size_t i = 0; i < lanes.size(); ++i)
    shown[i] = lanes[i];
  return shown;
}

/// A lane index the optimiser can't see, so the runtime-Lane constructors take their runtime path.
volatile int opaque_zero = 0;

/// For each lane i of a vector holding 1, 2, 3, ..., the value V{v[i]} (a runtime Lane) broadcasts, or -1 if its
/// lanes differ.
template <typename V>
auto broadcasts_of_runtime_lanes() {
  using S = typename V::scalar_type;
  std::array<S, V::lanes> values{};
  for (size_t i = 0; i < V::lanes; ++i)
    values[i] = static_cast<S>(i + 1);
  auto v = V::Load(values.data());
  std::array<Shown<S>, V::lanes> broadcasts{};
  for (int i = 0; i < static_cast<int>(V::lanes); ++i) {
    const auto lanes = V{v[i + opaque_zero]}.to_array();
    const bool same = std::all_of(lanes.begin(), lanes.end(), [&](S x) { return x == lanes[0]; });
    broadcasts[i] = same ? static_cast<Shown<S>>(lanes[0]) : Shown<S>(-1);
  }
  return broadcasts;
}

/// 1, 2, 3, ...: what broadcasts_of_runtime_lanes<V>() returns when every lane broadcasts.
template <typename V>
auto each_lane_value() {
  std::array<Shown<typename V::scalar_type>, V::lanes> expected{};
  for (size_t i = 0; i < V::lanes; ++i)
    expected[i] = static_cast<Shown<typename V::scalar_type>>(i + 1);
  return expected;
}
}  // namespace

// clang-format off

// ── Argon(std::array<S, 4>) ────────────────────────────────────────────────

auto describe_from_four = describe("Argon(std::array<S, 4>)", ${
  it("fills all four int32 lanes", _{
    expect(construct_from_four<int32_t>()).to_equal(four_then_zeroes<int32_t>());
  });

  it("fills all four float lanes", _{
    expect(construct_from_four<float>()).to_equal(four_then_zeroes<float>());
  });

  it("fills lanes 0-3 of an int16 vector and zeroes the rest", _{
    expect(construct_from_four<int16_t>()).to_equal(four_then_zeroes<int16_t>());
  });

  it("fills lanes 0-3 of a uint16 vector and zeroes the rest", _{
    expect(construct_from_four<uint16_t>()).to_equal(four_then_zeroes<uint16_t>());
  });

  it("fills lanes 0-3 of an int8 vector and zeroes the rest", _{
    expect(construct_from_four<int8_t>()).to_equal(four_then_zeroes<int8_t>());
  });

  it("fills lanes 0-3 of a uint8 vector and zeroes the rest", _{
    expect(construct_from_four<uint8_t>()).to_equal(four_then_zeroes<uint8_t>());
  });
});

// ── Construction from a runtime Lane ───────────────────────────────────────
// On AArch32 (and SIMDe) a runtime Lane hands the constructor the 64-bit half that holds the lane and the lane's
// index within it.
// AArch64 has no runtime-lane broadcast for a quadword: its Lane hands over the whole quadword, which
// simd::duplicate_lane doesn't take.
#ifndef __aarch64__
auto describe_runtime_lane = describe("Argon(Lane<V>) with a runtime index", ${
  it("broadcasts each lane of an int8 vector", _{
    expect(broadcasts_of_runtime_lanes<Argon<int8_t>>()).to_equal(each_lane_value<Argon<int8_t>>());
  });
  it("broadcasts each lane of a uint8 vector", _{
    expect(broadcasts_of_runtime_lanes<Argon<uint8_t>>()).to_equal(each_lane_value<Argon<uint8_t>>());
  });
  it("broadcasts each lane of an int16 vector", _{
    expect(broadcasts_of_runtime_lanes<Argon<int16_t>>()).to_equal(each_lane_value<Argon<int16_t>>());
  });
  it("broadcasts each lane of a uint16 vector", _{
    expect(broadcasts_of_runtime_lanes<Argon<uint16_t>>()).to_equal(each_lane_value<Argon<uint16_t>>());
  });
  it("broadcasts each lane of an int32 vector", _{
    expect(broadcasts_of_runtime_lanes<Argon<int32_t>>()).to_equal(each_lane_value<Argon<int32_t>>());
  });
  it("broadcasts each lane of a uint32 vector", _{
    expect(broadcasts_of_runtime_lanes<Argon<uint32_t>>()).to_equal(each_lane_value<Argon<uint32_t>>());
  });
  it("broadcasts each lane of a float vector", _{
    expect(broadcasts_of_runtime_lanes<Argon<float>>()).to_equal(each_lane_value<Argon<float>>());
  });
  it("broadcasts each lane of an int64 vector", _{
    expect(broadcasts_of_runtime_lanes<Argon<int64_t>>()).to_equal(each_lane_value<Argon<int64_t>>());
  });
  it("broadcasts each lane of a uint64 vector", _{
    expect(broadcasts_of_runtime_lanes<Argon<uint64_t>>()).to_equal(each_lane_value<Argon<uint64_t>>());
  });
});
#endif

#ifndef ARGON_PLATFORM_MVE  // MVE has no 64-bit vectors
auto describe_runtime_lane_half = describe("ArgonHalf(Lane<V>) with a runtime index", ${
  it("broadcasts each lane of an int8 half-vector", _{
    expect(broadcasts_of_runtime_lanes<ArgonHalf<int8_t>>()).to_equal(each_lane_value<ArgonHalf<int8_t>>());
  });
  it("broadcasts each lane of a uint8 half-vector", _{
    expect(broadcasts_of_runtime_lanes<ArgonHalf<uint8_t>>()).to_equal(each_lane_value<ArgonHalf<uint8_t>>());
  });
  it("broadcasts each lane of an int16 half-vector", _{
    expect(broadcasts_of_runtime_lanes<ArgonHalf<int16_t>>()).to_equal(each_lane_value<ArgonHalf<int16_t>>());
  });
  it("broadcasts each lane of a uint16 half-vector", _{
    expect(broadcasts_of_runtime_lanes<ArgonHalf<uint16_t>>()).to_equal(each_lane_value<ArgonHalf<uint16_t>>());
  });
  it("broadcasts each lane of an int32 half-vector", _{
    expect(broadcasts_of_runtime_lanes<ArgonHalf<int32_t>>()).to_equal(each_lane_value<ArgonHalf<int32_t>>());
  });
  it("broadcasts each lane of a uint32 half-vector", _{
    expect(broadcasts_of_runtime_lanes<ArgonHalf<uint32_t>>()).to_equal(each_lane_value<ArgonHalf<uint32_t>>());
  });
  it("broadcasts each lane of a float half-vector", _{
    expect(broadcasts_of_runtime_lanes<ArgonHalf<float>>()).to_equal(each_lane_value<ArgonHalf<float>>());
  });
  it("broadcasts the lane of an int64 half-vector", _{
    expect(broadcasts_of_runtime_lanes<ArgonHalf<int64_t>>()).to_equal(each_lane_value<ArgonHalf<int64_t>>());
  });
  it("broadcasts the lane of a uint64 half-vector", _{
    expect(broadcasts_of_runtime_lanes<ArgonHalf<uint64_t>>()).to_equal(each_lane_value<ArgonHalf<uint64_t>>());
  });
});
#endif

// ── 64-bit lanes ───────────────────────────────────────────────────────────
// A lane of a 64-bit-lane quadword lives in a one-lane ArgonHalf. On GCC AArch32, whose int64x1_t is a plain
// long long, that class failed to compile, and with it every lane broadcast and half of a 64-bit-lane vector.
#ifndef ARGON_PLATFORM_MVE  // MVE has no 64-bit vectors
auto describe_wide_lanes = describe("64-bit lanes", ${
  it("broadcasts compile-time lane 1 of an int64 vector", _{
    Argon<int64_t> v{int64_t{5}, int64_t{-7}};
    expect(Argon<int64_t>{v.template GetLane<1>()}.to_array()).to_equal(std::array<int64_t, 2>{-7, -7});
  });

  it("broadcasts compile-time lane 0 of a uint64 vector", _{
    Argon<uint64_t> v{uint64_t{11}, uint64_t{13}};
    expect(Argon<uint64_t>{v.template GetLane<0>()}.to_array()).to_equal(std::array<uint64_t, 2>{11, 11});
  });

  it("splits an int64 vector into its halves", _{
    Argon<int64_t> v{int64_t{5}, int64_t{-7}};
    expect(v.GetLow().to_array()).to_equal(std::array<int64_t, 1>{5});
    expect(v.GetHigh().to_array()).to_equal(std::array<int64_t, 1>{-7});
  });

  it("builds a uint64 half-vector from a scalar", _{
    ArgonHalf<uint64_t> h{uint64_t{0x123456789abcdef0}};
    expect(h.to_array()).to_equal(std::array<uint64_t, 1>{0x123456789abcdef0});
  });
});
#endif

// AArch64 declares two duplicate_lane<0>(uint64x1_t), returning the vector and the scalar, so this form is
// ambiguous there.
#if !defined(ARGON_PLATFORM_MVE) && !defined(__aarch64__)
auto describe_one_lane_broadcast = describe("64-bit half-vector lanes", ${
  it("builds a uint64 half-vector from its own lane", _{
    ArgonHalf<uint64_t> h{uint64_t{0x123456789abcdef0}};
    expect(ArgonHalf<uint64_t>{h.template GetLane<0>()}.to_array()).to_equal(std::array<uint64_t, 1>{0x123456789abcdef0});
  });
});
#endif

// Preprocessor directives inside a macro invocation are UB, so splice the NEON-only specs in via a macro.
#ifndef ARGON_PLATFORM_MVE
#define NEON_ONLY_SPECS , describe_runtime_lane_half, describe_wide_lanes
#else
#define NEON_ONLY_SPECS
#endif
#if !defined(ARGON_PLATFORM_MVE) && !defined(__aarch64__)
#define AARCH32_SPECS , describe_one_lane_broadcast
#else
#define AARCH32_SPECS
#endif
#ifndef __aarch64__
#define RUNTIME_LANE_SPECS , describe_runtime_lane
#else
#define RUNTIME_LANE_SPECS
#endif

CPPSPEC_MAIN(
  describe_from_four
  RUNTIME_LANE_SPECS
  NEON_ONLY_SPECS
  AARCH32_SPECS
);
