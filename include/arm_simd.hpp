#pragma once

#ifdef __ARM_NEON
#include <arm_neon.h>
#include "arm_simd/neon/vfpv3.hpp"

#ifdef __ARM_FEATURE_FMA
#include "arm_simd/neon/vfpv4.hpp"
#endif

#if (__ARM_ARCH > 7)  // ARMv8
// Always include A32
#include "arm_simd/neon/a32.hpp"

#ifdef __ARM_64BIT_STATE  // A64
#include "arm_simd/neon/a64.hpp"
#endif  // 64BIT_STATE
#endif  // __ARM_ARCH > 7

#else
#ifdef __ARM_FEATURE_MVE
#include <arm_mve.h>
#include "arm_simd/helium/int.hpp"
#include "arm_simd/helium/neon_int.hpp"

#if (__ARM_FEATURE_MVE & 2)
#include "arm_simd/helium/float.hpp"
#include "arm_simd/helium/neon_float.hpp"
#endif
#endif
#endif
