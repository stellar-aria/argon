#pragma once

#ifdef __ARM_NEON
#include <arm_neon.h>
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#include <arm_mve.h>
#define simd helium
#endif
#endif

namespace simd {

}  // namespace simd
#undef simd
