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
#define NEON_ONLY_SPECS , describe_wide_lanes
#else
#define NEON_ONLY_SPECS
#endif
#if !defined(ARGON_PLATFORM_MVE) && !defined(__aarch64__)
#define AARCH32_SPECS , describe_one_lane_broadcast
#else
#define AARCH32_SPECS
#endif

CPPSPEC_MAIN(
  describe_from_four
  NEON_ONLY_SPECS
  AARCH32_SPECS
);
