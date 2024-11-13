#pragma once

#if (__ARM_ARCH >= 8)  // ARMv8
#ifdef __ARM_64BIT_STATE  // A64
#include "arm_simd/neon/a64.hpp"
#else                     // A32
#include "arm_simd/neon/a32.hpp"
#endif

#else // __ARM_ARCH < 8

#ifdef __ARM_NEON

// ARMv7
#ifdef __ARM_FEATURE_FMA
#include "arm_simd/neon/vfpv4.hpp"
#else // !__ARM_FEATURE_FMA = VFPv3
#include "arm_simd/neon/vfpv3.hpp"
#endif

#endif
#ifdef __ARM_FEATURE_MVE

#if (__ARM_FEATURE_MVE & 2)
#include "arm_simd/helium/float.hpp"
#else
#include "arm_simd/helium/int.hpp"
#endif

#endif // __ARM_FEATURE_MVE

#endif  // __ARM_ARCH

#if !defined(__ARM_NEON) && !defined(__ARM_FEATURE_MVE)
// mock

#endif
