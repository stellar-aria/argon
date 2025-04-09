#pragma once

#ifdef __ARM_NEON
#pragma message("NEON detected")

#if (__ARM_ARCH >= 8)  // ARMv8
#pragma message("ARMv8 detected")

#ifdef __ARM_64BIT_STATE  // A64
#include "arm_simd/neon/a64.hpp"
#else  // A32
#include "arm_simd/neon/a32.hpp"
#endif

#else  // __ARM_ARCH < 8
#pragma message("ARMv7 detected")

// ARMv7
#ifdef __ARM_FEATURE_FMA
#include "arm_simd/neon/vfpv4.hpp"
#else  // !__ARM_FEATURE_FMA = VFPv3
#include "arm_simd/neon/vfpv3.hpp"
#endif

#endif

#elifdef __ARM_FEATURE_MVE

#pragma message("MVE detected")

#if (__ARM_FEATURE_MVE & 2)
#include "arm_simd/helium/float.hpp"
#else
#include "arm_simd/helium/int.hpp"
#endif

#else

#pragma message("Using SIMDe fallback")
#include "arm_simd/neon/vfpv3.hpp"
#endif
