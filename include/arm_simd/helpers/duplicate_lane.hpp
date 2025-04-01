#pragma once
#include "argon/features.h"
#include "nonvec.hpp"
#include "vec64.hpp"
#include "arm_simd.hpp"

#ifdef __ARM_NEON
#define simd neon
#elifdef __ARM_FEATURE_MVE
#define simd helium
#else
#define simd neon
#endif


#ifdef __clang__
#define nce [[gnu::always_inline]] constexpr
#else
#define nce [[gnu::always_inline]] inline
#endif


namespace simd {
#if ARGON_HAS_DWORD
template <typename T>
nce T duplicate_lane(typename Vec64<NonVec_t<T>>::type vec, const int i);

template <>
nce uint8x8_t duplicate_lane(uint8x8_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane<0>(vec);
    case 1:
      return simd::duplicate_lane<1>(vec);
    case 2:
      return simd::duplicate_lane<2>(vec);
    case 3:
      return simd::duplicate_lane<3>(vec);
    case 4:
      return simd::duplicate_lane<4>(vec);
    case 5:
      return simd::duplicate_lane<5>(vec);
    case 6:
      return simd::duplicate_lane<6>(vec);
    case 7:
      return simd::duplicate_lane<7>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint8x16_t duplicate_lane(uint8x8_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane_quad<0>(vec);
    case 1:
      return simd::duplicate_lane_quad<1>(vec);
    case 2:
      return simd::duplicate_lane_quad<2>(vec);
    case 3:
      return simd::duplicate_lane_quad<3>(vec);
    case 4:
      return simd::duplicate_lane_quad<4>(vec);
    case 5:
      return simd::duplicate_lane_quad<5>(vec);
    case 6:
      return simd::duplicate_lane_quad<6>(vec);
    case 7:
      return simd::duplicate_lane_quad<7>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int8x8_t duplicate_lane(int8x8_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane<0>(vec);
    case 1:
      return simd::duplicate_lane<1>(vec);
    case 2:
      return simd::duplicate_lane<2>(vec);
    case 3:
      return simd::duplicate_lane<3>(vec);
    case 4:
      return simd::duplicate_lane<4>(vec);
    case 5:
      return simd::duplicate_lane<5>(vec);
    case 6:
      return simd::duplicate_lane<6>(vec);
    case 7:
      return simd::duplicate_lane<7>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int8x16_t duplicate_lane(int8x8_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane_quad<0>(vec);
    case 1:
      return simd::duplicate_lane_quad<1>(vec);
    case 2:
      return simd::duplicate_lane_quad<2>(vec);
    case 3:
      return simd::duplicate_lane_quad<3>(vec);
    case 4:
      return simd::duplicate_lane_quad<4>(vec);
    case 5:
      return simd::duplicate_lane_quad<5>(vec);
    case 6:
      return simd::duplicate_lane_quad<6>(vec);
    case 7:
      return simd::duplicate_lane_quad<7>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint16x4_t duplicate_lane(uint16x4_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane<0>(vec);
    case 1:
      return simd::duplicate_lane<1>(vec);
    case 2:
      return simd::duplicate_lane<2>(vec);
    case 3:
      return simd::duplicate_lane<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint16x8_t duplicate_lane(uint16x4_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane_quad<0>(vec);
    case 1:
      return simd::duplicate_lane_quad<1>(vec);
    case 2:
      return simd::duplicate_lane_quad<2>(vec);
    case 3:
      return simd::duplicate_lane_quad<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int16x4_t duplicate_lane(int16x4_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane<0>(vec);
    case 1:
      return simd::duplicate_lane<1>(vec);
    case 2:
      return simd::duplicate_lane<2>(vec);
    case 3:
      return simd::duplicate_lane<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int16x8_t duplicate_lane(int16x4_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane_quad<0>(vec);
    case 1:
      return simd::duplicate_lane_quad<1>(vec);
    case 2:
      return simd::duplicate_lane_quad<2>(vec);
    case 3:
      return simd::duplicate_lane_quad<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint32x2_t duplicate_lane(uint32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane<0>(vec);
    case 1:
      return simd::duplicate_lane<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint32x4_t duplicate_lane(uint32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane_quad<0>(vec);
    case 1:
      return simd::duplicate_lane_quad<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int32x2_t duplicate_lane(int32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane<0>(vec);
    case 1:
      return simd::duplicate_lane<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int32x4_t duplicate_lane(int32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane_quad<0>(vec);
    case 1:
      return simd::duplicate_lane_quad<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint64x2_t duplicate_lane(uint64x1_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane_quad<0>(vec);
    default:
      __builtin_unreachable();
  }
}

#if ARGON_HAS_SINGLE_FLOAT
template <>
nce float32x2_t duplicate_lane(float32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane<0>(vec);
    case 1:
      return simd::duplicate_lane<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce float32x4_t duplicate_lane(float32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane_quad<0>(vec);
    case 1:
      return simd::duplicate_lane_quad<1>(vec);
    default:
      __builtin_unreachable();
  }
}
#endif
#endif
}
#undef simd
#undef nce
