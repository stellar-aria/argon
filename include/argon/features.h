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

#ifndef ARGON_USE_COMPILER_EXTENSIONS
#if !defined(_MSC_VER) || defined(__clang__)
#define ARGON_USE_COMPILER_EXTENSIONS 1
#else
#define ARGON_USE_COMPILER_EXTENSIONS 0
#endif
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
