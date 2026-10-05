#pragma once
#include <stdbool.h>

/// @file features.h
/// @brief Header file for SIMD features and platform detection.

namespace argon {
enum class Platform {
  NEON,
  MVE,
  SIMDe,
};
}

#ifdef __ARM_NEON
namespace argon {
constexpr Platform platform = Platform::NEON;
}
#define ARGON_PLATFORM_NEON true
#define ARGON_HAS_FLOAT true

#if (__ARM_ARCH >= 8)

#if (__arm__)  // A32

#define ARGON_HAS_HALF_FLOAT true
#define ARGON_HAS_SINGLE_FLOAT true
#define ARGON_HAS_DOUBLE_FLOAT false

#elif (__aarch64__)  // A64

#define ARGON_HAS_HALF_FLOAT true
#define ARGON_HAS_SINGLE_FLOAT true
#define ARGON_HAS_DOUBLE_FLOAT true

#endif

#else

#define ARGON_HAS_HALF_FLOAT (__ARM_NEON_FP & 2)
#define ARGON_HAS_SINGLE_FLOAT (__ARM_NEON_FP & 4)
#define ARGON_HAS_DOUBLE_FLOAT (__ARM_NEON_FP & 8)

#endif

#elifdef __ARM_FEATURE_MVE
namespace argon {
constexpr Platform platform = Platform::MVE;
}
#define ARGON_PLATFORM_MVE true

#if (__ARM_FEATURE_MVE & 2)
#define ARGON_HAS_FLOAT true
#define ARGON_HAS_HALF_FLOAT true
#define ARGON_HAS_SINGLE_FLOAT true
#else
#define ARGON_HAS_FLOAT false
#define ARGON_HAS_HALF_FLOAT false
#define ARGON_HAS_SINGLE_FLOAT false
#endif

#else
namespace argon {
constexpr Platform platform = Platform::SIMDe;
}
#define ARGON_PLATFORM_SIMDE true
#define ARGON_HAS_FLOAT true
#define ARGON_HAS_HALF_FLOAT false
#define ARGON_HAS_SINGLE_FLOAT true
#define ARGON_HAS_DOUBLE_FLOAT false
#endif

/// True where vmaxnm/vminnm exist (simd::max_strict / min_strict): Helium with floating point, and Armv8 NEON.
#if (defined(__ARM_FEATURE_MVE) && (__ARM_FEATURE_MVE & 2)) || (defined(__ARM_NEON) && __ARM_ARCH >= 8)
#define ARGON_HAS_MAXNM true
#else
#define ARGON_HAS_MAXNM false
#endif

/// True where NEON has half-precision vector arithmetic (FEAT_FP16), so the f16 forms of vmaxnm/vminnm exist.
#if defined(__ARM_NEON) && defined(__ARM_FEATURE_FP16_VECTOR_ARITHMETIC)
#define ARGON_NEON_FP16_VECTOR true
#else
#define ARGON_NEON_FP16_VECTOR false
#endif

#ifndef ARGON_USE_COMPILER_EXTENSIONS
#if !defined(_MSC_VER) || defined(__clang__)
#define ARGON_USE_COMPILER_EXTENSIONS 1
#else
#define ARGON_USE_COMPILER_EXTENSIONS 0
#endif
#endif

/// True where GCC compiles AArch32 NEON code without -ffast-math: it then scalarises generic vector-extension
/// float arithmetic, comparisons and ?: to VFP (NEON flushes denormals, so it isn't IEEE), so Argon routes float
/// operations through NEON builtins and inline vcgt/vcge instead (argon/helpers/float_fixups.hpp).
#if defined(__arm__) && !defined(__aarch64__) && defined(__ARM_NEON) && defined(__GNUC__) && !defined(__clang__) && \
    !defined(__FAST_MATH__)
#define ARGON_GCC_AARCH32_FLOAT true
#else
#define ARGON_GCC_AARCH32_FLOAT false
#endif

/// Set to 1 when the AES and PMULL crypto intrinsics are available.
/// Requires __ARM_FEATURE_CRYPTO (ARMv8 Cryptographic Extension).
#ifdef __ARM_FEATURE_CRYPTO
#define ARGON_HAS_CRYPTO true
#else
#define ARGON_HAS_CRYPTO false
#endif

/*
#define XSTR(x) STR(x)
#define STR(x) #x
#pragma message "DWORD: " XSTR(ARGON_HAS_DWORD)
#pragma message "SINGLE_FLOAT: " XSTR(ARGON_HAS_SINGLE_FLOAT)
#pragma message "HALF_FLOAT: " XSTR(ARGON_HAS_HALF_FLOAT)
#pragma message "DOUBLE_FLOAT: " XSTR(ARGON_HAS_DOUBLE_FLOAT)
#pragma message "__ARM_NEON: " XSTR(__ARM_NEON)
#pragma message "__ARM_NEON_FP: " XSTR(__ARM_NEON_FP)
#pragma message "__ARM_FP: " XSTR(__ARM_FP)
*/
