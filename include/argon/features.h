#pragma once
#include <stdbool.h>

#ifdef __ARM_NEON
#define ARGON_HAS_DWORD true
#define ARGON_HAS_FLOAT true
#define ARGON_HAS_NEON true

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

#else
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

#endif
