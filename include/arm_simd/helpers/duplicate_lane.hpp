#pragma once
#include <utility>
#include "argon/features.h"
#include "arm_simd.hpp"
#include "concepts.hpp"
#include "scalar.hpp"
#include "vec64.hpp"

#ifdef __ARM_FEATURE_MVE
#define simd helium
#else
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
#if ARGON_HAS_DWORD
template <typename VectorType>
nce VectorType duplicate_lane(Vec64_t<Scalar_t<VectorType>> vec, const int i) {
  constexpr int lanes = sizeof(VectorType) / sizeof(Scalar_t<VectorType>);
  constexpr bool is_quadword = is_quadword_v<VectorType>;
  if constexpr (is_quadword) {
    if constexpr (lanes == 2) {
      switch (i) {
        case 0:
          return simd::duplicate_lane_quad<0>(vec);
        case 1:
          return simd::duplicate_lane_quad<1>(vec);
        default:
          std::unreachable();
      }
    } else if constexpr (lanes == 4) {
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
          std::unreachable();
      }
    } else if constexpr (lanes == 8) {
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
          std::unreachable();
      }
    } else {
      std::unreachable();
    }

  } else {
    if constexpr (lanes == 2) {
      switch (i) {
        case 0:
          return simd::duplicate_lane<0>(vec);
        case 1:
          return simd::duplicate_lane<1>(vec);
        default:
          std::unreachable();
      }
    } else if constexpr (lanes == 4) {
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
          std::unreachable();
      }
    } else if constexpr (lanes == 8) {
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
          std::unreachable();
      }
    } else {
      std::unreachable();
    }
  }
}
#endif
}  // namespace simd
#undef simd
#undef nce
