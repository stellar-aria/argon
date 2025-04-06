#pragma once
#include "argon/features.h"
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
// clang-format off

template <typename T>
nce auto get_lane(T vec, const int i);

template <>
nce auto get_lane(uint8x16_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    case 4:
      return simd::get_lane<4>(vec);
    case 5:
      return simd::get_lane<5>(vec);
    case 6:
      return simd::get_lane<6>(vec);
    case 7:
      return simd::get_lane<7>(vec);
    case 8:
      return simd::get_lane<8>(vec);
    case 9:
      return simd::get_lane<9>(vec);
    case 10:
      return simd::get_lane<10>(vec);
    case 11:
      return simd::get_lane<11>(vec);
    case 12:
      return simd::get_lane<12>(vec);
    case 13:
      return simd::get_lane<13>(vec);
    case 14:
      return simd::get_lane<14>(vec);
    case 15:
      return simd::get_lane<15>(vec);
    default:
      std::unreachable();
  }
}

template <>
nce auto get_lane(int8x16_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    case 4:
      return simd::get_lane<4>(vec);
    case 5:
      return simd::get_lane<5>(vec);
    case 6:
      return simd::get_lane<6>(vec);
    case 7:
      return simd::get_lane<7>(vec);
    case 8:
      return simd::get_lane<8>(vec);
    case 9:
      return simd::get_lane<9>(vec);
    case 10:
      return simd::get_lane<10>(vec);
    case 11:
      return simd::get_lane<11>(vec);
    case 12:
      return simd::get_lane<12>(vec);
    case 13:
      return simd::get_lane<13>(vec);
    case 14:
      return simd::get_lane<14>(vec);
    case 15:
      return simd::get_lane<15>(vec);
    default:
      std::unreachable();
  }
}

template <>
nce auto get_lane(uint16x8_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    case 4:
      return simd::get_lane<4>(vec);
    case 5:
      return simd::get_lane<5>(vec);
    case 6:
      return simd::get_lane<6>(vec);
    case 7:
      return simd::get_lane<7>(vec);
    default:
      std::unreachable();
  }
}

template <>
nce auto get_lane(int16x8_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    case 4:
      return simd::get_lane<4>(vec);
    case 5:
      return simd::get_lane<5>(vec);
    case 6:
      return simd::get_lane<6>(vec);
    case 7:
      return simd::get_lane<7>(vec);
    default:
      std::unreachable();
  }
}

template <>
nce auto get_lane(uint32x4_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    default:
      std::unreachable();
  }
}

template <>
nce auto get_lane(int32x4_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    default:
      std::unreachable();
  }
}

template <>
nce auto get_lane(uint64x2_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    default:
      std::unreachable();
  }
}

template <>
nce auto get_lane(int64x2_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    default:
      std::unreachable();
  }
}

#if ARGON_HAS_SINGLE_FLOAT
template <>
nce auto get_lane(float32x4_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    default:
      std::unreachable();
  }
}
#endif

#if ARGON_HAS_HALF_FLOAT
template <>
nce auto get_lane(float16x8_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    case 4:
      return simd::get_lane<4>(vec);
    case 5:
      return simd::get_lane<5>(vec);
    case 6:
      return simd::get_lane<6>(vec);
    case 7:
      return simd::get_lane<7>(vec);
    default:
      std::unreachable();
  }
}
#endif

#if ARGON_HAS_DOUBLE_FLOAT
template <>
nce auto get_lane(float64x2_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    default:
      std::unreachable();
 }
}
#endif

#if ARGON_HAS_DWORD
template <>
nce auto get_lane(uint8x8_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    case 4:
      return simd::get_lane<4>(vec);
    case 5:
      return simd::get_lane<5>(vec);
    case 6:
      return simd::get_lane<6>(vec);
    case 7:
      return simd::get_lane<7>(vec);
    default:
      std::unreachable();
  }
}

template <>
nce auto get_lane(int8x8_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    case 4:
      return simd::get_lane<4>(vec);
    case 5:
      return simd::get_lane<5>(vec);
    case 6:
      return simd::get_lane<6>(vec);
    case 7:
      return simd::get_lane<7>(vec);
    default:
      std::unreachable();
  }
}

template <>
nce auto get_lane(uint16x4_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    default:
      std::unreachable();
  }
}

template <>
nce auto get_lane(int16x4_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    default:
      std::unreachable();
  }
}

template <>
nce auto get_lane(uint32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    default:
      std::unreachable();
  }
}

template <>
nce auto get_lane(int32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    default:
      std::unreachable();
  }
}

template <>
nce auto get_lane(uint64x1_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    default:
      std::unreachable();
  }
}

template <>
nce auto get_lane(int64x1_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    default:
      std::unreachable();
  }
}


#if ARGON_HAS_SINGLE_FLOAT
template <>
nce auto get_lane(float32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    default:
      std::unreachable();
  }
}
#endif

#if ARGON_HAS_HALF_FLOAT
template <>
nce auto get_lane(float16x4_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    default:
      std::unreachable();
  }
}
#endif

#if ARGON_HAS_DOUBLE_FLOAT
template <>
nce auto get_lane(float64x1_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    default:
      std::unreachable();
  }
}
#endif
#endif

// clang-format on
}  // namespace simd
#undef simd
