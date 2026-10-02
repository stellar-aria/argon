#pragma once
#include <array>
#include <cstdint>
#include "argon/features.h"

#ifndef __ARM_FEATURE_MVE
#ifdef __ARM_NEON
#include <arm_neon.h>
#else
#define SIMDE_ENABLE_NATIVE_ALIASES
#include <arm/neon.h>
#endif

/// Workarounds that keep Argon's float operations on NEON with the NEON instructions' semantics.
///
/// - GCC on AArch32 scalarises generic vector-extension float arithmetic, comparisons and `?:` to VFP unless
///   -ffast-math is on (AArch32 NEON flushes denormals, so it is not IEEE), and its arm_neon.h implements
///   vc{lt,gt,le,ge}{q}_f32 as such generic comparisons. Argon uses the NEON builtins behind the arithmetic
///   intrinsics there (see `ARGON_GCC_AARCH32_FLOAT`), and the inline vcgt/vcge below for comparisons.
/// - clang on AArch32 lowers vcvt{q}_{s,u}32_f32 to IR fptosi/fptoui, which are poison for NaN and
///   out-of-range inputs and get constant-folded to wrong values (AArch64 uses llvm.fpto{s,u}i.sat). The
///   conversions below emit vcvt directly there, keeping its truncate/saturate/NaN→0 semantics.
/// - SIMDe (x86) converts float values between 2^31 and 2^32 to uint32 as 2^31; the conversions below convert
///   per lane there.
namespace argon::helpers {

#if defined(__arm__) && !defined(__aarch64__) && defined(__clang__)
#define ARGON_CLANG_AARCH32_CONVERT true
#else
#define ARGON_CLANG_AARCH32_CONVERT false
#endif

[[gnu::always_inline]] inline uint32_t saturate_to_uint32(float x) {
  if (!(x > 0.0f)) return 0;  // also NaN
  if (x >= 4294967296.0f) return UINT32_MAX;
  return static_cast<uint32_t>(x);
}

[[gnu::always_inline]] inline int32x4_t convert_to_int32(float32x4_t a) {
#if ARGON_CLANG_AARCH32_CONVERT
  int32x4_t r;
  asm("vcvt.s32.f32 %q0, %q1" : "=w"(r) : "w"(a));
  return r;
#else
  return vcvtq_s32_f32(a);
#endif
}

[[gnu::always_inline]] inline int32x2_t convert_to_int32(float32x2_t a) {
#if ARGON_CLANG_AARCH32_CONVERT
  int32x2_t r;
  asm("vcvt.s32.f32 %P0, %P1" : "=w"(r) : "w"(a));
  return r;
#else
  return vcvt_s32_f32(a);
#endif
}

[[gnu::always_inline]] inline uint32x4_t convert_to_uint32(float32x4_t a) {
#if ARGON_CLANG_AARCH32_CONVERT
  uint32x4_t r;
  asm("vcvt.u32.f32 %q0, %q1" : "=w"(r) : "w"(a));
  return r;
#elif ARGON_PLATFORM_SIMDE
  std::array<float, 4> in;
  vst1q_f32(in.data(), a);
  const std::array<uint32_t, 4> out{saturate_to_uint32(in[0]), saturate_to_uint32(in[1]), saturate_to_uint32(in[2]),
                                    saturate_to_uint32(in[3])};
  return vld1q_u32(out.data());
#else
  return vcvtq_u32_f32(a);
#endif
}

[[gnu::always_inline]] inline uint32x2_t convert_to_uint32(float32x2_t a) {
#if ARGON_CLANG_AARCH32_CONVERT
  uint32x2_t r;
  asm("vcvt.u32.f32 %P0, %P1" : "=w"(r) : "w"(a));
  return r;
#elif ARGON_PLATFORM_SIMDE
  std::array<float, 2> in;
  vst1_f32(in.data(), a);
  const std::array<uint32_t, 2> out{saturate_to_uint32(in[0]), saturate_to_uint32(in[1])};
  return vld1_u32(out.data());
#else
  return vcvt_u32_f32(a);
#endif
}

#undef ARGON_CLANG_AARCH32_CONVERT

#if ARGON_GCC_AARCH32_FLOAT
[[gnu::always_inline]] inline uint32x4_t greater_than(float32x4_t a, float32x4_t b) {
  uint32x4_t r;
  asm("vcgt.f32 %q0, %q1, %q2" : "=w"(r) : "w"(a), "w"(b));
  return r;
}
[[gnu::always_inline]] inline uint32x2_t greater_than(float32x2_t a, float32x2_t b) {
  uint32x2_t r;
  asm("vcgt.f32 %P0, %P1, %P2" : "=w"(r) : "w"(a), "w"(b));
  return r;
}
[[gnu::always_inline]] inline uint32x4_t greater_than_or_equal(float32x4_t a, float32x4_t b) {
  uint32x4_t r;
  asm("vcge.f32 %q0, %q1, %q2" : "=w"(r) : "w"(a), "w"(b));
  return r;
}
[[gnu::always_inline]] inline uint32x2_t greater_than_or_equal(float32x2_t a, float32x2_t b) {
  uint32x2_t r;
  asm("vcge.f32 %P0, %P1, %P2" : "=w"(r) : "w"(a), "w"(b));
  return r;
}
#endif

}  // namespace argon::helpers
#endif
