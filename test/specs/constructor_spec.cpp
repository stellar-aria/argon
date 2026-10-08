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

CPPSPEC_MAIN(describe_from_four);
