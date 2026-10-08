// Every Argon operation and constructor here must inline when the translation unit is compiled with
// -fno-inline-functions (checked by check_inline.sh): no call may target an Argon symbol. Firmware builds use that
// flag, under which a function without [[gnu::always_inline]] is emitted out of line and called from the loop.
// The loops are the shapes of an audio engine's inner loops: Q31 fixed-point gain, mixing, oscillators.
#include <cstddef>
#include <cstdint>
#include <utility>
#include "argon.hpp"
#include "argon/vectorize/for_each.hpp"

#ifdef ARGON_PLATFORM_MVE
#define simd mve
#else
#define simd neon
#endif

using I32 = Argon<int32_t>;

extern "C" {

// ── construction ──

// From a scalar, broadcast to every lane.
void inline_from_scalar(int32_t* out, int32_t value, ptrdiff_t vectors) {
  for (ptrdiff_t i = 0; i < vectors; ++i) {
    (I32{value} + I32{static_cast<int32_t>(i)}).StoreTo(out + i * I32::lanes);
  }
}

// From the underlying vector type, as an intrinsic returns it.
void inline_from_vector(int32_t* out, const int32_t* in, ptrdiff_t vectors) {
  for (ptrdiff_t i = 0; i < vectors; ++i) {
    simd::Vec128_t<int32_t> raw = I32::Load(in + i * I32::lanes);
    I32 v{raw};
    I32 w = raw;
    (v + w).StoreTo(out + i * I32::lanes);
  }
}

// From a load, and default-constructed, copied, moved and assigned on the way.
void inline_from_load(int32_t* out, const int32_t* in, ptrdiff_t vectors) {
  I32 acc{0};
  I32 last;
  for (ptrdiff_t i = 0; i < vectors; ++i) {
    I32 v = I32::Load(in + i * I32::lanes);
    I32 copy{v};
    acc = acc + copy;
    I32 moved{std::move(v)};
    last = moved;
  }
  (acc + last).StoreTo(out);
}

// From one value per lane.
void inline_from_lanes(int32_t* out, int32_t a, int32_t b, ptrdiff_t vectors) {
  for (ptrdiff_t i = 0; i < vectors; ++i) {
    (I32::Load(out + i * I32::lanes) + I32{a, b, a, b}).StoreTo(out + i * I32::lanes);
  }
}

// ── fixed-point arithmetic ──

// A VCA: Q31 gain with rounding, then a saturating headroom shift.
void inline_vca(int32_t* buffer, int32_t gain, ptrdiff_t vectors) {
  for (ptrdiff_t i = 0; i < vectors; ++i) {
    I32 v = I32::Load(buffer + i * I32::lanes);
    v.MultiplyRoundFixedQMax(gain).ShiftLeftSaturate<2>().StoreTo(buffer + i * I32::lanes);
  }
}

// A mixer: sum a source at a Q31 gain into the destination, saturating.
void inline_mix(int32_t* dest, const int32_t* source, int32_t gain, ptrdiff_t vectors) {
  for (ptrdiff_t i = 0; i < vectors; ++i) {
    I32 d = I32::Load(dest + i * I32::lanes);
    I32 s = I32::Load(source + i * I32::lanes).MultiplyFixedQMax(I32{gain});
    d.AddSaturate(s).StoreTo(dest + i * I32::lanes);
  }
}

// A pulse oscillator: a phase accumulator compared against a width, shifted down to the output level.
void inline_pulse(int32_t* out,
                  uint32_t phase,
                  uint32_t increment,
                  uint32_t width,
                  int32_t amplitude,
                  ptrdiff_t vectors) {
  using U32 = Argon<uint32_t>;
  U32 phases = U32{phase} + U32{0u, increment, increment * 2, increment * 3};
  const U32 step{increment * 4};
  for (ptrdiff_t i = 0; i < vectors; ++i) {
    I32 square = argon::ternary(phases < U32{width}, I32{INT32_MAX}, I32{INT32_MIN});
    I32 shaped = (square >> 1) + (phases.As<int32_t>().ShiftRight<2>() << 1);
    shaped.MultiplyRoundFixedQMax(amplitude).StoreTo(out + i * I32::lanes);
    phases = phases + step;
  }
}

// ── vectorize::for_each ──

void inline_for_each_gain(int32_t* buffer, int32_t gain, ptrdiff_t n) {
  argon::vectorize::for_each<int32_t>(n, [&](auto s) {
    s.Store(buffer, s.Load(buffer).MultiplyRoundFixedQMax(I32{gain}).template ShiftLeftSaturate<1>());
  });
}

void inline_for_each_mix(int32_t* dest, const int32_t* source, int32_t gain, ptrdiff_t n) {
  argon::vectorize::for_each<int32_t>(
      n, [&](auto s) { s.Store(dest, s.Load(dest).AddSaturate(s.Load(source).MultiplyFixedQMax(gain))); });
}

}  // extern "C"
