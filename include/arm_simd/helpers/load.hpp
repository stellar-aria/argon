#pragma once
#include <utility>
#include "argon/utility.hpp"
#include "arm_simd.hpp"
#include "concepts.hpp"
#include "scalar.hpp"
#include "vec128.hpp"

#ifdef __ARM_NEON
#include <arm_neon.h
#define simd neon
#elifdef __ARM_FEATURE_MVE
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
#ifndef ARGON_PLATFORM_MVE
template <typename T>
nce T load1_lane(T vec, const int i, Scalar_t<T> const* ptr) {
  constexpr size_t lanes = sizeof(T) / sizeof(Scalar_t<T>);
  constexpr bool is_quadword = is_quadword_v<T>;
  if constexpr (is_quadword) {
    if constexpr (lanes == 2) {
      switch (i) {
        case 0:
          return neon::load1_lane_quad<0>(ptr, vec);
        case 1:
          return neon::load1_lane_quad<1>(ptr, vec);
        default:
          std::unreachable();
      }
    } else if constexpr (lanes == 4) {
      switch (i) {
        case 0:
          return neon::load1_lane_quad<0>(ptr, vec);
        case 1:
          return neon::load1_lane_quad<1>(ptr, vec);
        case 2:
          return neon::load1_lane_quad<2>(ptr, vec);
        case 3:
          return neon::load1_lane_quad<3>(ptr, vec);
        default:
          std::unreachable();
      }
    } else if constexpr (lanes == 8) {
      switch (i) {
        case 0:
          return neon::load1_lane_quad<0>(ptr, vec);
        case 1:
          return neon::load1_lane_quad<1>(ptr, vec);
        case 2:
          return neon::load1_lane_quad<2>(ptr, vec);
        case 3:
          return neon::load1_lane_quad<3>(ptr, vec);
        case 4:
          return neon::load1_lane_quad<4>(ptr, vec);
        case 5:
          return neon::load1_lane_quad<5>(ptr, vec);
        case 6:
          return neon::load1_lane_quad<6>(ptr, vec);
        case 7:
          return neon::load1_lane_quad<7>(ptr, vec);
        default:
          std::unreachable();
      }
    } else if constexpr (lanes == 16) {
      switch (i) {
        case 0:
          return neon::load1_lane_quad<0>(ptr, vec);
        case 1:
          return neon::load1_lane_quad<1>(ptr, vec);
        case 2:
          return neon::load1_lane_quad<2>(ptr, vec);
        case 3:
          return neon::load1_lane_quad<3>(ptr, vec);
        case 4:
          return neon::load1_lane_quad<4>(ptr, vec);
        case 5:
          return neon::load1_lane_quad<5>(ptr, vec);
        case 6:
          return neon::load1_lane_quad<6>(ptr, vec);
        case 7:
          return neon::load1_lane_quad<7>(ptr, vec);
        case 8:
          return neon::load1_lane_quad<8>(ptr, vec);
        case 9:
          return neon::load1_lane_quad<9>(ptr, vec);
        case 10:
          return neon::load1_lane_quad<10>(ptr, vec);
        case 11:
          return neon::load1_lane_quad<11>(ptr, vec);
        case 12:
          return neon::load1_lane_quad<12>(ptr, vec);
        case 13:
          return neon::load1_lane_quad<13>(ptr, vec);
        case 14:
          return neon::load1_lane_quad<14>(ptr, vec);
        case 15:
          return neon::load1_lane_quad<15>(ptr, vec);
        default:
          std::unreachable();
      }
    } else {
      std::unreachable();
    }
  } else {
    if constexpr (lanes == 2) {
      switch (i) {
        case 0:
          return neon::load1_lane<0>(ptr, vec);
        case 1:
          return neon::load1_lane<1>(ptr, vec);
        default:
          std::unreachable();
      }
    } else if constexpr (lanes == 4) {
      switch (i) {
        case 0:
          return neon::load1_lane<0>(ptr, vec);
        case 1:
          return neon::load1_lane<1>(ptr, vec);
        case 2:
          return neon::load1_lane<2>(ptr, vec);
        case 3:
          return neon::load1_lane<3>(ptr, vec);
        default:
          std::unreachable();
      }
    } else if constexpr (lanes == 8) {
      switch (i) {
        case 0:
          return neon::load1_lane<0>(ptr, vec);
        case 1:
          return neon::load1_lane<1>(ptr, vec);
        case 2:
          return neon::load1_lane<2>(ptr, vec);
        case 3:
          return neon::load1_lane<3>(ptr, vec);
        case 4:
          return neon::load1_lane<4>(ptr, vec);
        case 5:
          return neon::load1_lane<5>(ptr, vec);
        case 6:
          return neon::load1_lane<6>(ptr, vec);
        case 7:
          return neon::load1_lane<7>(ptr, vec);
        default:
          std::unreachable();
      }
    } else {
      std::unreachable();
    }
  }
}
#endif

}  // namespace simd
#undef neon
#undef nce
