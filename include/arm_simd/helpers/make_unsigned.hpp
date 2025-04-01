#pragma once
#include "argon/features.h"

#ifdef __ARM_NEON
#include <arm_neon.h>
#define simd neon
#elifdef __ARM_FEATURE_MVE
#include <arm_mve.h>
#define simd helium
#else
#define SIMDE_ENABLE_NATIVE_ALIASES
#include <arm/neon.h>
#define simd neon
#endif

namespace simd {
// clang-format off
template <typename T> struct make_unsigned;
template <> struct make_unsigned<int8x16_t> { using type = uint8x16_t; };
template <> struct make_unsigned<uint8x16_t> { using type = uint8x16_t; };
template <> struct make_unsigned<int16x8_t> { using type = uint16x8_t; };
template <> struct make_unsigned<uint16x8_t> { using type = uint16x8_t; };
template <> struct make_unsigned<int32x4_t> { using type = uint32x4_t; };
template <> struct make_unsigned<uint32x4_t> { using type = uint32x4_t; };
template <> struct make_unsigned<int64x2_t> { using type = uint64x2_t; };
template <> struct make_unsigned<uint64x2_t> { using type = uint64x2_t; };

#if ARGON_HAS_DWORD
template <> struct make_unsigned<int8x8_t> { using type = uint8x8_t; };
template <> struct make_unsigned<uint8x8_t> { using type = uint8x8_t; };
template <> struct make_unsigned<int16x4_t> { using type = uint16x4_t; };
template <> struct make_unsigned<uint16x4_t> { using type = uint16x4_t; };
template <> struct make_unsigned<int32x2_t> { using type = uint32x2_t; };
template <> struct make_unsigned<uint32x2_t> { using type = uint32x2_t; };
template <> struct make_unsigned<int64x1_t> { using type = uint64x1_t; };
template <> struct make_unsigned<uint64x1_t> { using type = uint64x1_t; };
#endif

template <typename T> using make_unsigned_t = typename make_unsigned<T>::type;
// clang-format on
}  // namespace simd
#undef simd
