#pragma once
#include <cstddef>
#include <type_traits>
#include "arm_simd.hpp"

namespace argon::impl {
// clang-format off
template <typename T> struct Result;
template <> struct Result<int8x16_t> { using type = uint8x16_t; };
template <> struct Result<uint8x16_t> { using type = uint8x16_t; };
template <> struct Result<int16x8_t> { using type = uint16x8_t; };
template <> struct Result<uint16x8_t> { using type = uint16x8_t; };
template <> struct Result<int32x4_t> { using type = uint32x4_t; };
template <> struct Result<uint32x4_t> { using type = uint32x4_t; };
template <> struct Result<int64x2_t> { using type = uint64x2_t; };
template <> struct Result<uint64x2_t> { using type = uint64x2_t; };
#if ARGON_HAS_SINGLE_FLOAT
template <> struct Result<float32x4_t> { using type = uint32x4_t; };
#endif

#if ARGON_HAS_DWORD
template <> struct Result<int8x8_t> { using type = uint8x8_t; };
template <> struct Result<uint8x8_t> { using type = uint8x8_t; };
template <> struct Result<int16x4_t> { using type = uint16x4_t; };
template <> struct Result<uint16x4_t> { using type = uint16x4_t; };
template <> struct Result<int32x2_t> { using type = uint32x2_t; };
template <> struct Result<uint32x2_t> { using type = uint32x2_t; };
template <> struct Result<int64x1_t> { using type = uint64x1_t; };
template <> struct Result<uint64x1_t> { using type = uint64x1_t; };

#if ARGON_HAS_SINGLE_FLOAT
template <> struct Result<float32x2_t> { using type = uint32x2_t; };
#endif
#endif

template <typename T>
using Result_t = Result<T>::type;
// clang-format on
}  // namespace argon::impl
