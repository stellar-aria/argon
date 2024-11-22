#pragma once
#include <cstddef>
#include "arm_simd.hpp"
#include "argon/features.h"

namespace argon::impl {
template <typename T, size_t size> struct MultiVec;
template <> struct MultiVec<int8x16_t, 2> { using type = int8x16x2_t; };
template <> struct MultiVec<uint8x16_t, 2> { using type = uint8x16x2_t; };
template <> struct MultiVec<int16x8_t, 2> { using type = int16x8x2_t; };
template <> struct MultiVec<uint16x8_t, 2> { using type = uint16x8x2_t; };
template <> struct MultiVec<int32x4_t, 2> { using type = int32x4x2_t; };
template <> struct MultiVec<uint32x4_t, 2> { using type = uint32x4x2_t; };
template <> struct MultiVec<int64x2_t, 2> { using type = int64x2x2_t; };
template <> struct MultiVec<uint64x2_t, 2> { using type = uint64x2x2_t; };

template <> struct MultiVec<float32x2_t, 2> { using type = float32x2x2_t; };
template <> struct MultiVec<float32x4_t, 2> { using type = float32x4x2_t; };

template <> struct MultiVec<poly8x8_t, 2> { using type = poly8x8x2_t; };
template <> struct MultiVec<poly16x4_t, 2> { using type = poly16x4x2_t; };


template <> struct MultiVec<int8x16_t, 3> { using type = int8x16x3_t; };
template <> struct MultiVec<uint8x16_t, 3> { using type = uint8x16x3_t; };
template <> struct MultiVec<int16x8_t, 3> { using type = int16x8x3_t; };
template <> struct MultiVec<uint16x8_t, 3> { using type = uint16x8x3_t; };
template <> struct MultiVec<int32x4_t, 3> { using type = int32x4x3_t; };
template <> struct MultiVec<uint32x4_t, 3> { using type = uint32x4x3_t; };
template <> struct MultiVec<int64x2_t, 3> { using type = int64x2x3_t; };
template <> struct MultiVec<uint64x2_t, 3> { using type = uint64x2x3_t; };

template <> struct MultiVec<float32x2_t, 3> { using type = float32x2x3_t; };
template <> struct MultiVec<float32x4_t, 3> { using type = float32x4x3_t; };

template <> struct MultiVec<poly8x8_t, 3> { using type = poly8x8x3_t; };
template <> struct MultiVec<poly16x4_t, 3> { using type = poly16x4x3_t; };

template <> struct MultiVec<int8x16_t, 4> { using type = int8x16x4_t; };
template <> struct MultiVec<uint8x16_t, 4> { using type = uint8x16x4_t; };
template <> struct MultiVec<int16x8_t, 4> { using type = int16x8x4_t; };
template <> struct MultiVec<uint16x8_t, 4> { using type = uint16x8x4_t; };
template <> struct MultiVec<int32x4_t, 4> { using type = int32x4x4_t; };
template <> struct MultiVec<uint32x4_t, 4> { using type = uint32x4x4_t; };
template <> struct MultiVec<int64x2_t, 4> { using type = int64x2x4_t; };
template <> struct MultiVec<uint64x2_t, 4> { using type = uint64x2x4_t; };

template <> struct MultiVec<float32x2_t, 4> { using type = float32x2x4_t; };
template <> struct MultiVec<float32x4_t, 4> { using type = float32x4x4_t; };

template <> struct MultiVec<poly8x8_t, 4> { using type = poly8x8x4_t; };
template <> struct MultiVec<poly16x4_t, 4> { using type = poly16x4x4_t; };

#if ARGON_HAS_DWORD
template <> struct MultiVec<int8x8_t, 2> { using type = int8x8x2_t; };
template <> struct MultiVec<uint8x8_t, 2> { using type = uint8x8x2_t; };
template <> struct MultiVec<int16x4_t, 2> { using type = int16x4x2_t; };
template <> struct MultiVec<uint16x4_t, 2> { using type = uint16x4x2_t; };
template <> struct MultiVec<int32x2_t, 2> { using type = int32x2x2_t; };
template <> struct MultiVec<uint32x2_t, 2> { using type = uint32x2x2_t; };
template <> struct MultiVec<int64x1_t, 2> { using type = int64x1x2_t; };
template <> struct MultiVec<uint64x1_t, 2> { using type = uint64x1x2_t; };

template <> struct MultiVec<int8x8_t, 3> { using type = int8x8x3_t; };
template <> struct MultiVec<uint8x8_t, 3> { using type = uint8x8x3_t; };
template <> struct MultiVec<int16x4_t, 3> { using type = int16x4x3_t; };
template <> struct MultiVec<uint16x4_t, 3> { using type = uint16x4x3_t; };
template <> struct MultiVec<int32x2_t, 3> { using type = int32x2x3_t; };
template <> struct MultiVec<uint32x2_t, 3> { using type = uint32x2x3_t; };
template <> struct MultiVec<int64x1_t, 3> { using type = int64x1x3_t; };
template <> struct MultiVec<uint64x1_t, 3> { using type = uint64x1x3_t; };

template <> struct MultiVec<int8x8_t, 4> { using type = int8x8x4_t; };
template <> struct MultiVec<uint8x8_t, 4> { using type = uint8x8x4_t; };
template <> struct MultiVec<int16x4_t, 4> { using type = int16x4x4_t; };
template <> struct MultiVec<uint16x4_t, 4> { using type = uint16x4x4_t; };
template <> struct MultiVec<int32x2_t, 4> { using type = int32x2x4_t; };
template <> struct MultiVec<uint32x2_t, 4> { using type = uint32x2x4_t; };
template <> struct MultiVec<int64x1_t, 4> { using type = int64x1x4_t; };
template <> struct MultiVec<uint64x1_t, 4> { using type = uint64x1x4_t; };
#endif

template <typename T, size_t size>
using MultiVec_t = MultiVec<T, size>::type;
}
