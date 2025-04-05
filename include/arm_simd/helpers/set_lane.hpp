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

#ifdef ARGON_PLATFORM_SIMDE
#define nce
#elifdef __clang__
#define nce [[gnu::always_inline]] constexpr
#else
#define nce [[gnu::always_inline]] inline
#endif

namespace simd {

template <typename T>
nce T set_lane(T vec, const int i, typename NonVec<T>::type a);

template <>
nce uint8x16_t set_lane(uint8x16_t vec, const int i, uint8_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    case 2:
      return simd::set_lane<2>(a, vec);
    case 3:
      return simd::set_lane<3>(a, vec);
    case 4:
      return simd::set_lane<4>(a, vec);
    case 5:
      return simd::set_lane<5>(a, vec);
    case 6:
      return simd::set_lane<6>(a, vec);
    case 7:
      return simd::set_lane<7>(a, vec);
    case 8:
      return simd::set_lane<8>(a, vec);
    case 9:
      return simd::set_lane<9>(a, vec);
    case 10:
      return simd::set_lane<10>(a, vec);
    case 11:
      return simd::set_lane<11>(a, vec);
    case 12:
      return simd::set_lane<12>(a, vec);
    case 13:
      return simd::set_lane<13>(a, vec);
    case 14:
      return simd::set_lane<14>(a, vec);
    case 15:
      return simd::set_lane<15>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int8x16_t set_lane(int8x16_t vec, const int i, int8_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    case 2:
      return simd::set_lane<2>(a, vec);
    case 3:
      return simd::set_lane<3>(a, vec);
    case 4:
      return simd::set_lane<4>(a, vec);
    case 5:
      return simd::set_lane<5>(a, vec);
    case 6:
      return simd::set_lane<6>(a, vec);
    case 7:
      return simd::set_lane<7>(a, vec);
    case 8:
      return simd::set_lane<8>(a, vec);
    case 9:
      return simd::set_lane<9>(a, vec);
    case 10:
      return simd::set_lane<10>(a, vec);
    case 11:
      return simd::set_lane<11>(a, vec);
    case 12:
      return simd::set_lane<12>(a, vec);
    case 13:
      return simd::set_lane<13>(a, vec);
    case 14:
      return simd::set_lane<14>(a, vec);
    case 15:
      return simd::set_lane<15>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint16x8_t set_lane(uint16x8_t vec, const int i, uint16_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    case 2:
      return simd::set_lane<2>(a, vec);
    case 3:
      return simd::set_lane<3>(a, vec);
    case 4:
      return simd::set_lane<4>(a, vec);
    case 5:
      return simd::set_lane<5>(a, vec);
    case 6:
      return simd::set_lane<6>(a, vec);
    case 7:
      return simd::set_lane<7>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int16x8_t set_lane(int16x8_t vec, const int i, int16_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    case 2:
      return simd::set_lane<2>(a, vec);
    case 3:
      return simd::set_lane<3>(a, vec);
    case 4:
      return simd::set_lane<4>(a, vec);
    case 5:
      return simd::set_lane<5>(a, vec);
    case 6:
      return simd::set_lane<6>(a, vec);
    case 7:
      return simd::set_lane<7>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint32x4_t set_lane(uint32x4_t vec, const int i, uint32_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    case 2:
      return simd::set_lane<2>(a, vec);
    case 3:
      return simd::set_lane<3>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int32x4_t set_lane(int32x4_t vec, const int i, int32_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    case 2:
      return simd::set_lane<2>(a, vec);
    case 3:
      return simd::set_lane<3>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce float32x4_t set_lane(float32x4_t vec, const int i, float a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    case 2:
      return simd::set_lane<2>(a, vec);
    case 3:
      return simd::set_lane<3>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint64x2_t set_lane(uint64x2_t vec, const int i, uint64_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int64x2_t set_lane(int64x2_t vec, const int i, int64_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    default:
      __builtin_unreachable();
  }
}
#if ARGON_HAS_DWORD

template <>
nce uint8x8_t set_lane(uint8x8_t vec, const int i, uint8_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    case 2:
      return simd::set_lane<2>(a, vec);
    case 3:
      return simd::set_lane<3>(a, vec);
    case 4:
      return simd::set_lane<4>(a, vec);
    case 5:
      return simd::set_lane<5>(a, vec);
    case 6:
      return simd::set_lane<6>(a, vec);
    case 7:
      return simd::set_lane<7>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int8x8_t set_lane(int8x8_t vec, const int i, int8_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    case 2:
      return simd::set_lane<2>(a, vec);
    case 3:
      return simd::set_lane<3>(a, vec);
    case 4:
      return simd::set_lane<4>(a, vec);
    case 5:
      return simd::set_lane<5>(a, vec);
    case 6:
      return simd::set_lane<6>(a, vec);
    case 7:
      return simd::set_lane<7>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint16x4_t set_lane(uint16x4_t vec, const int i, uint16_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    case 2:
      return simd::set_lane<2>(a, vec);
    case 3:
      return simd::set_lane<3>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int16x4_t set_lane(int16x4_t vec, const int i, int16_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    case 2:
      return simd::set_lane<2>(a, vec);
    case 3:
      return simd::set_lane<3>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint32x2_t set_lane(uint32x2_t vec, const int i, uint32_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int32x2_t set_lane(int32x2_t vec, const int i, int32_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce float32x2_t set_lane(float32x2_t vec, const int i, float32_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint64x1_t set_lane(uint64x1_t vec, const int i, uint64_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int64x1_t set_lane(int64x1_t vec, const int i, int64_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    default:
      __builtin_unreachable();
  }
}
#endif

}  // namespace simd
#undef simd
#undef nce
