#pragma once
#include "concepts.hpp"
#include "nonvec.hpp"

#ifdef __ARM_NEON
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#define simd helium
#endif
#endif

#ifdef __clang__
#define nce [[gnu::always_inline]] constexpr
#else
#define nce [[gnu::always_inline]] inline
#endif

namespace simd {
#if ARGON_HAS_DWORD
template <is_vector_type T, is_doubleword U>
  requires std::is_same_v<NonVec_t<T>, NonVec_t<U>>
nce T multiply_add_lane(T a, T b, U vec, const int lane) {
  constexpr int lanes = sizeof(U) / sizeof(NonVec_t<U>);
  if constexpr (lanes == 2) {
    switch (lane) {
      case 0:
        return multiply_add_lane<0>(a, b, vec);
      case 1:
        return multiply_add_lane<1>(a, b, vec);
      default:
        __builtin_unreachable();
    }
  } else if constexpr (lanes == 4) {
    switch (lane) {
      case 0:
        return multiply_add_lane<0>(a, b, vec);
      case 1:
        return multiply_add_lane<1>(a, b, vec);
      case 2:
        return multiply_add_lane<2>(a, b, vec);
      case 3:
        return multiply_add_lane<3>(a, b, vec);
      default:
        __builtin_unreachable();
    }
  } else if constexpr (lanes == 8) {
    switch (lane) {
      case 0:
        return multiply_add_lane<0>(a, b, vec);
      case 1:
        return multiply_add_lane<1>(a, b, vec);
      case 2:
        return multiply_add_lane<2>(a, b, vec);
      case 3:
        return multiply_add_lane<3>(a, b, vec);
      case 4:
        return multiply_add_lane<4>(a, b, vec);
      case 5:
        return multiply_add_lane<5>(a, b, vec);
      case 6:
        return multiply_add_lane<6>(a, b, vec);
      case 7:
        return multiply_add_lane<7>(a, b, vec);
      default:
        __builtin_unreachable();
    }
  }
  return T();
}
#endif

// ARM64 supports quadword vector argument
#ifdef __aarch64__
template <is_vector_type T, is_vector_type U>
  requires std::is_same_v<NonVec_t<T>, NonVec_t<U>>
nce T multiply_add_lane(T a, T b, U vec, const int lane) {
  constexpr int lanes = sizeof(U) / sizeof(NonVec_t<U>);
  if constexpr (lanes == 2) {
    switch (lane) {
      case 0:
        return multiply_add_lane<0>(a, b, vec);
      case 1:
        return multiply_add_lane<1>(a, b, vec);
      default:
        __builtin_unreachable();
    }
  } else if constexpr (lanes == 4) {
    switch (lane) {
      case 0:
        return multiply_add_lane<0>(a, b, vec);
      case 1:
        return multiply_add_lane<1>(a, b, vec);
      case 2:
        return multiply_add_lane<2>(a, b, vec);
      case 3:
        return multiply_add_lane<3>(a, b, vec);
      default:
        __builtin_unreachable();
    }
  } else if constexpr (lanes == 8) {
    switch (lane) {
      case 0:
        return multiply_add_lane<0>(a, b, vec);
      case 1:
        return multiply_add_lane<1>(a, b, vec);
      case 2:
        return multiply_add_lane<2>(a, b, vec);
      case 3:
        return multiply_add_lane<3>(a, b, vec);
      case 4:
        return multiply_add_lane<4>(a, b, vec);
      case 5:
        return multiply_add_lane<5>(a, b, vec);
      case 6:
        return multiply_add_lane<6>(a, b, vec);
      case 7:
        return multiply_add_lane<7>(a, b, vec);
      default:
        __builtin_unreachable();
    }
  } else if constexpr (lanes == 16) {
    switch (lane) {
      case 0:
        return multiply_add_lane<0>(a, b, vec);
      case 1:
        return multiply_add_lane<1>(a, b, vec);
      case 2:
        return multiply_add_lane<2>(a, b, vec);
      case 3:
        return multiply_add_lane<3>(a, b, vec);
      case 4:
        return multiply_add_lane<4>(a, b, vec);
      case 5:
        return multiply_add_lane<5>(a, b, vec);
      case 6:
        return multiply_add_lane<6>(a, b, vec);
      case 7:
        return multiply_add_lane<7>(a, b, vec);
      case 8:
        return multiply_add_lane<8>(a, b, vec);
      case 9:
        return multiply_add_lane<9>(a, b, vec);
      case 10:
        return multiply_add_lane<10>(a, b, vec);
      case 11:
        return multiply_add_lane<11>(a, b, vec);
      case 12:
        return multiply_add_lane<12>(a, b, vec);
      case 13:
        return multiply_add_lane<13>(a, b, vec);
      case 14:
        return multiply_add_lane<14>(a, b, vec);
      case 15:
        return multiply_add_lane<15>(a, b, vec);
      default:
        __builtin_unreachable();
    }
  }
}
#endif
}  // namespace simd
#undef simd
#undef nce
