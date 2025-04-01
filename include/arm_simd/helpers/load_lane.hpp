#pragma once
#include "nonvec.hpp"
#include "../../arm_simd.hpp"

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

#ifdef __clang__
#define nce [[gnu::always_inline]] constexpr
#else
#define nce [[gnu::always_inline]] inline
#endif

namespace simd {

template <typename T>
nce T load1_lane(T vec, const int i, typename NonVec<T>::type const *ptr);

template <>
nce uint8x16_t load1_lane(uint8x16_t vec, const int i, uint8_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane_quad<0>(ptr, vec);
    case 1:
      return simd::load1_lane_quad<1>(ptr, vec);
    case 2:
      return simd::load1_lane_quad<2>(ptr, vec);
    case 3:
      return simd::load1_lane_quad<3>(ptr, vec);
    case 4:
      return simd::load1_lane_quad<4>(ptr, vec);
    case 5:
      return simd::load1_lane_quad<5>(ptr, vec);
    case 6:
      return simd::load1_lane_quad<6>(ptr, vec);
    case 7:
      return simd::load1_lane_quad<7>(ptr, vec);
    case 8:
      return simd::load1_lane_quad<8>(ptr, vec);
    case 9:
      return simd::load1_lane_quad<9>(ptr, vec);
    case 10:
      return simd::load1_lane_quad<10>(ptr, vec);
    case 11:
      return simd::load1_lane_quad<11>(ptr, vec);
    case 12:
      return simd::load1_lane_quad<12>(ptr, vec);
    case 13:
      return simd::load1_lane_quad<13>(ptr, vec);
    case 14:
      return simd::load1_lane_quad<14>(ptr, vec);
    case 15:
      return simd::load1_lane_quad<15>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int8x16_t load1_lane(int8x16_t vec, const int i, int8_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane_quad<0>(ptr, vec);
    case 1:
      return simd::load1_lane_quad<1>(ptr, vec);
    case 2:
      return simd::load1_lane_quad<2>(ptr, vec);
    case 3:
      return simd::load1_lane_quad<3>(ptr, vec);
    case 4:
      return simd::load1_lane_quad<4>(ptr, vec);
    case 5:
      return simd::load1_lane_quad<5>(ptr, vec);
    case 6:
      return simd::load1_lane_quad<6>(ptr, vec);
    case 7:
      return simd::load1_lane_quad<7>(ptr, vec);
    case 8:
      return simd::load1_lane_quad<8>(ptr, vec);
    case 9:
      return simd::load1_lane_quad<9>(ptr, vec);
    case 10:
      return simd::load1_lane_quad<10>(ptr, vec);
    case 11:
      return simd::load1_lane_quad<11>(ptr, vec);
    case 12:
      return simd::load1_lane_quad<12>(ptr, vec);
    case 13:
      return simd::load1_lane_quad<13>(ptr, vec);
    case 14:
      return simd::load1_lane_quad<14>(ptr, vec);
    case 15:
      return simd::load1_lane_quad<15>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint16x8_t load1_lane(uint16x8_t vec, const int i, uint16_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane_quad<0>(ptr, vec);
    case 1:
      return simd::load1_lane_quad<1>(ptr, vec);
    case 2:
      return simd::load1_lane_quad<2>(ptr, vec);
    case 3:
      return simd::load1_lane_quad<3>(ptr, vec);
    case 4:
      return simd::load1_lane_quad<4>(ptr, vec);
    case 5:
      return simd::load1_lane_quad<5>(ptr, vec);
    case 6:
      return simd::load1_lane_quad<6>(ptr, vec);
    case 7:
      return simd::load1_lane_quad<7>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int16x8_t load1_lane(int16x8_t vec, const int i, int16_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane_quad<0>(ptr, vec);
    case 1:
      return simd::load1_lane_quad<1>(ptr, vec);
    case 2:
      return simd::load1_lane_quad<2>(ptr, vec);
    case 3:
      return simd::load1_lane_quad<3>(ptr, vec);
    case 4:
      return simd::load1_lane_quad<4>(ptr, vec);
    case 5:
      return simd::load1_lane_quad<5>(ptr, vec);
    case 6:
      return simd::load1_lane_quad<6>(ptr, vec);
    case 7:
      return simd::load1_lane_quad<7>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint32x4_t load1_lane(uint32x4_t vec, const int i, uint32_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane_quad<0>(ptr, vec);
    case 1:
      return simd::load1_lane_quad<1>(ptr, vec);
    case 2:
      return simd::load1_lane_quad<2>(ptr, vec);
    case 3:
      return simd::load1_lane_quad<3>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int32x4_t load1_lane(int32x4_t vec, const int i, int32_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane_quad<0>(ptr, vec);
    case 1:
      return simd::load1_lane_quad<1>(ptr, vec);
    case 2:
      return simd::load1_lane_quad<2>(ptr, vec);
    case 3:
      return simd::load1_lane_quad<3>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce float32x4_t load1_lane(float32x4_t vec, const int i, float const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane_quad<0>(ptr, vec);
    case 1:
      return simd::load1_lane_quad<1>(ptr, vec);
    case 2:
      return simd::load1_lane_quad<2>(ptr, vec);
    case 3:
      return simd::load1_lane_quad<3>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint64x2_t load1_lane(uint64x2_t vec, const int i, uint64_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane_quad<0>(ptr, vec);
    case 1:
      return simd::load1_lane_quad<1>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int64x2_t load1_lane(int64x2_t vec, const int i, int64_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane_quad<0>(ptr, vec);
    case 1:
      return simd::load1_lane_quad<1>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}
#if ARGON_HAS_DWORD

template <>
nce uint8x8_t load1_lane(uint8x8_t vec, const int i, uint8_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane<0>(ptr, vec);
    case 1:
      return simd::load1_lane<1>(ptr, vec);
    case 2:
      return simd::load1_lane<2>(ptr, vec);
    case 3:
      return simd::load1_lane<3>(ptr, vec);
    case 4:
      return simd::load1_lane<4>(ptr, vec);
    case 5:
      return simd::load1_lane<5>(ptr, vec);
    case 6:
      return simd::load1_lane<6>(ptr, vec);
    case 7:
      return simd::load1_lane<7>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int8x8_t load1_lane(int8x8_t vec, const int i, int8_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane<0>(ptr, vec);
    case 1:
      return simd::load1_lane<1>(ptr, vec);
    case 2:
      return simd::load1_lane<2>(ptr, vec);
    case 3:
      return simd::load1_lane<3>(ptr, vec);
    case 4:
      return simd::load1_lane<4>(ptr, vec);
    case 5:
      return simd::load1_lane<5>(ptr, vec);
    case 6:
      return simd::load1_lane<6>(ptr, vec);
    case 7:
      return simd::load1_lane<7>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint16x4_t load1_lane(uint16x4_t vec, const int i, uint16_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane<0>(ptr, vec);
    case 1:
      return simd::load1_lane<1>(ptr, vec);
    case 2:
      return simd::load1_lane<2>(ptr, vec);
    case 3:
      return simd::load1_lane<3>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int16x4_t load1_lane(int16x4_t vec, const int i, int16_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane<0>(ptr, vec);
    case 1:
      return simd::load1_lane<1>(ptr, vec);
    case 2:
      return simd::load1_lane<2>(ptr, vec);
    case 3:
      return simd::load1_lane<3>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint32x2_t load1_lane(uint32x2_t vec, const int i, uint32_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane<0>(ptr, vec);
    case 1:
      return simd::load1_lane<1>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int32x2_t load1_lane(int32x2_t vec, const int i, int32_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane<0>(ptr, vec);
    case 1:
      return simd::load1_lane<1>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce float32x2_t load1_lane(float32x2_t vec, const int i, float32_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane<0>(ptr, vec);
    case 1:
      return simd::load1_lane<1>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint64x1_t load1_lane(uint64x1_t vec, const int i, uint64_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane<0>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int64x1_t load1_lane(int64x1_t vec, const int i, int64_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane<0>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}
#endif

}  // namespace simd
#undef simd
#undef nce
