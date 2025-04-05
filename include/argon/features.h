#pragma once
#include <stdbool.h>

namespace argon {
enum class platform {
  NEON,
  MVE,
  MOCK,
};
}

#ifdef __ARM_NEON
namespace argon {
constexpr platform target = platform::NEON;
}
#define ARGON_HAS_DWORD true
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

#if (__ARM_NEON_FP & 2)
#define ARGON_HAS_HALF_FLOAT true
#else
#define ARGON_HAS_HALF_FLOAT false
#endif

#if (__ARM_NEON_FP & 4)
#define ARGON_HAS_SINGLE_FLOAT true
#else
#define ARGON_HAS_SINGLE_FLOAT false
#endif

#if (__ARM_NEON_FP & 8)
#define ARGON_HAS_DOUBLE_FLOAT true
#else
#define ARGON_HAS_DOUBLE_FLOAT false
#endif

#endif

#elifdef __ARM_FEATURE_MVE
namespace argon {
constexpr platform target = platform::MVE;
}
#define ARGON_HAS_DWORD false

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
constexpr platform target = platform::MOCK;
}
#define ARGON_HAS_DWORD true
#define ARGON_HAS_FLOAT true
#define ARGON_HAS_HALF_FLOAT false
#define ARGON_HAS_SINGLE_FLOAT true
#define ARGON_HAS_DOUBLE_FLOAT false
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
