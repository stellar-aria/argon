#pragma once
#include "argon/features.h"

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
// clang-format off
template <typename T> struct make_signed;
template <> struct make_signed<uint8x16_t> { using type = int8x16_t; };
template <> struct make_signed<int8x16_t> { using type = int8x16_t; };
template <> struct make_signed<uint16x8_t> { using type = int16x8_t; };
template <> struct make_signed<int16x8_t> { using type = int16x8_t; };
template <> struct make_signed<uint32x4_t> { using type = int32x4_t; };
template <> struct make_signed<int32x4_t> { using type = int32x4_t; };
template <> struct make_signed<uint64x2_t> { using type = int64x2_t; };
template <> struct make_signed<int64x2_t> { using type = int64x2_t; };

#if ARGON_HAS_DWORD
template <> struct make_signed<uint8x8_t> { using type = int8x8_t; };
template <> struct make_signed<int8x8_t> { using type = int8x8_t; };
template <> struct make_signed<uint16x4_t> { using type = int16x4_t; };
template <> struct make_signed<int16x4_t> { using type = int16x4_t; };
template <> struct make_signed<uint32x2_t> { using type = int32x2_t; };
template <> struct make_signed<int32x2_t> { using type = int32x2_t; };
template <> struct make_signed<uint64x1_t> { using type = int64x1_t; };
template <> struct make_signed<int64x1_t> { using type = int64x1_t; };
#endif

template <typename T> using make_signed_t = typename make_signed<T>::type;
// clang-format on
}  // namespace simd
#undef simd
