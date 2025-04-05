#pragma once
#include "concepts.hpp"
#include "nonvec.hpp"

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

#define make_lane_helper_dword_1arg(lane_func)             \
  template <is_vector_type T, is_doubleword U>             \
    requires std::is_same_v<NonVec_t<T>, NonVec_t<U>>      \
  nce T lane_func(T a, U vec, const int lane) {          \
    constexpr int lanes = sizeof(U) / sizeof(NonVec_t<U>); \
    if constexpr (lanes == 2) {                            \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, vec);                   \
        case 1:                                            \
          return lane_func<1>(a, vec);                   \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    } else if constexpr (lanes == 4) {                     \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, vec);                   \
        case 1:                                            \
          return lane_func<1>(a, vec);                   \
        case 2:                                            \
          return lane_func<2>(a, vec);                   \
        case 3:                                            \
          return lane_func<3>(a, vec);                   \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    } else if constexpr (lanes == 8) {                     \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, vec);                   \
        case 1:                                            \
          return lane_func<1>(a, vec);                   \
        case 2:                                            \
          return lane_func<2>(a, vec);                   \
        case 3:                                            \
          return lane_func<3>(a, vec);                   \
        case 4:                                            \
          return lane_func<4>(a, vec);                   \
        case 5:                                            \
          return lane_func<5>(a, vec);                   \
        case 6:                                            \
          return lane_func<6>(a, vec);                   \
        case 7:                                            \
          return lane_func<7>(a, vec);                   \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    }                                                      \
  }

#define make_lane_helper_dword_2arg(lane_func)             \
  template <is_vector_type T, is_doubleword U>             \
    requires std::is_same_v<NonVec_t<T>, NonVec_t<U>>      \
  nce T lane_func(T a, T b, U vec, const int lane) {     \
    constexpr int lanes = sizeof(U) / sizeof(NonVec_t<U>); \
    if constexpr (lanes == 2) {                            \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, b, vec);                \
        case 1:                                            \
          return lane_func<1>(a, b, vec);                \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    } else if constexpr (lanes == 4) {                     \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, b, vec);                \
        case 1:                                            \
          return lane_func<1>(a, b, vec);                \
        case 2:                                            \
          return lane_func<2>(a, b, vec);                \
        case 3:                                            \
          return lane_func<3>(a, b, vec);                \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    } else if constexpr (lanes == 8) {                     \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, b, vec);                \
        case 1:                                            \
          return lane_func<1>(a, b, vec);                \
        case 2:                                            \
          return lane_func<2>(a, b, vec);                \
        case 3:                                            \
          return lane_func<3>(a, b, vec);                \
        case 4:                                            \
          return lane_func<4>(a, b, vec);                \
        case 5:                                            \
          return lane_func<5>(a, b, vec);                \
        case 6:                                            \
          return lane_func<6>(a, b, vec);                \
        case 7:                                            \
          return lane_func<7>(a, b, vec);                \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    }                                                      \
  }

#define make_lane_helper_qword_1arg(lane_func)             \
  template <is_vector_type T, is_vector_type U>            \
    requires std::is_same_v<NonVec_t<T>, NonVec_t<U>>      \
  nce T lane_func(T a, U vec, const int lane) {          \
    constexpr int lanes = sizeof(U) / sizeof(NonVec_t<U>); \
    if constexpr (lanes == 2) {                            \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, vec);                   \
        case 1:                                            \
          return lane_func<1>(a, vec);                   \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    } else if constexpr (lanes == 4) {                     \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, vec);                   \
        case 1:                                            \
          return lane_func<1>(a, vec);                   \
        case 2:                                            \
          return lane_func<2>(a, vec);                   \
        case 3:                                            \
          return lane_func<3>(a, vec);                   \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    } else if constexpr (lanes == 8) {                     \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, vec);                   \
        case 1:                                            \
          return lane_func<1>(a, vec);                   \
        case 2:                                            \
          return lane_func<2>(a, vec);                   \
        case 3:                                            \
          return lane_func<3>(a, vec);                   \
        case 4:                                            \
          return lane_func<4>(a, vec);                   \
        case 5:                                            \
          return lane_func<5>(a, vec);                   \
        case 6:                                            \
          return lane_func<6>(a, vec);                   \
        case 7:                                            \
          return lane_func<7>(a, vec);                   \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    } else if constexpr (lanes == 16) {                    \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, vec);                   \
        case 1:                                            \
          return lane_func<1>(a, vec);                   \
        case 2:                                            \
          return lane_func<2>(a, vec);                   \
        case 3:                                            \
          return lane_func<3>(a, vec);                   \
        case 4:                                            \
          return lane_func<4>(a, vec);                   \
        case 5:                                            \
          return lane_func<5>(a, vec);                   \
        case 6:                                            \
          return lane_func<6>(a, vec);                   \
        case 7:                                            \
          return lane_func<7>(a, vec);                   \
        case 8:                                            \
          return lane_func<8>(a, vec);                   \
        case 9:                                            \
          return lane_func<9>(a, vec);                   \
        case 10:                                           \
          return lane_func<10>(a, vec);                  \
        case 11:                                           \
          return lane_func<11>(a, vec);                  \
        case 12:                                           \
          return lane_func<12>(a, vec);                  \
        case 13:                                           \
          return lane_func<13>(a, vec);                  \
        case 14:                                           \
          return lane_func<14>(a, vec);                  \
        case 15:                                           \
          return lane_func<15>(a, vec);                  \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    }                                                      \
  }

#define make_lane_helper_qword_2arg(lane_func)             \
  template <is_vector_type T, is_vector_type U>            \
    requires std::is_same_v<NonVec_t<T>, NonVec_t<U>>      \
  nce T lane_func(T a, T b, U vec, const int lane) {     \
    constexpr int lanes = sizeof(U) / sizeof(NonVec_t<U>); \
    if constexpr (lanes == 2) {                            \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, b, vec);                \
        case 1:                                            \
          return lane_func<1>(a, b, vec);                \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    } else if constexpr (lanes == 4) {                     \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, b, vec);                \
        case 1:                                            \
          return lane_func<1>(a, b, vec);                \
        case 2:                                            \
          return lane_func<2>(a, b, vec);                \
        case 3:                                            \
          return lane_func<3>(a, b, vec);                \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    } else if constexpr (lanes == 8) {                     \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, b, vec);                \
        case 1:                                            \
          return lane_func<1>(a, b, vec);                \
        case 2:                                            \
          return lane_func<2>(a, b, vec);                \
        case 3:                                            \
          return lane_func<3>(a, b, vec);                \
        case 4:                                            \
          return lane_func<4>(a, b, vec);                \
        case 5:                                            \
          return lane_func<5>(a, b, vec);                \
        case 6:                                            \
          return lane_func<6>(a, b, vec);                \
        case 7:                                            \
          return lane_func<7>(a, b, vec);                \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    } else if constexpr (lanes == 16) {                    \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, b, vec);                \
        case 1:                                            \
          return lane_func<1>(a, b, vec);                \
        case 2:                                            \
          return lane_func<2>(a, b, vec);                \
        case 3:                                            \
          return lane_func<3>(a, b, vec);                \
        case 4:                                            \
          return lane_func<4>(a, b, vec);                \
        case 5:                                            \
          return lane_func<5>(a, b, vec);                \
        case 6:                                            \
          return lane_func<6>(a, b, vec);                \
        case 7:                                            \
          return lane_func<7>(a, b, vec);                \
        case 8:                                            \
          return lane_func<8>(a, b, vec);                \
        case 9:                                            \
          return lane_func<9>(a, b, vec);                \
        case 10:                                           \
          return lane_func<10>(a, b, vec);               \
        case 11:                                           \
          return lane_func<11>(a, b, vec);               \
        case 12:                                           \
          return lane_func<12>(a, b, vec);               \
        case 13:                                           \
          return lane_func<13>(a, b, vec);               \
        case 14:                                           \
          return lane_func<14>(a, b, vec);               \
        case 15:                                           \
          return lane_func<15>(a, b, vec);               \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    }                                                      \
  }

namespace simd {
#if ARGON_HAS_DWORD
make_lane_helper_dword_1arg(multiply_lane);
make_lane_helper_dword_1arg(multiply_long_lane);
make_lane_helper_dword_1arg(multiply_double_saturate_long_lane);
make_lane_helper_dword_1arg(multiply_double_saturate_high_lane);
make_lane_helper_dword_1arg(multiply_double_round_saturate_high_lane);
make_lane_helper_dword_2arg(multiply_add_lane);
make_lane_helper_dword_2arg(multiply_subtract_lane);
make_lane_helper_dword_2arg(multiply_add_long_lane);
make_lane_helper_dword_2arg(multiply_subtract_long_lane);
make_lane_helper_dword_2arg(multiply_double_add_saturate_long_lane);
make_lane_helper_dword_2arg(multiply_double_subtract_saturate_long_lane);
#endif

#ifdef __aarch64__
make_lane_helper_qword_1arg(multiply_lane);
make_lane_helper_qword_1arg(multiply_long_lane);
make_lane_helper_qword_1arg(multiply_double_saturate_long_lane);
make_lane_helper_qword_1arg(multiply_double_saturate_high_lane);
make_lane_helper_qword_1arg(multiply_double_round_saturate_high_lane);
make_lane_helper_qword_2arg(multiply_add_lane);
make_lane_helper_qword_2arg(multiply_subtract_lane);
make_lane_helper_qword_2arg(multiply_add_long_lane);
make_lane_helper_qword_2arg(multiply_subtract_long_lane);
make_lane_helper_qword_2arg(multiply_double_add_saturate_long_lane);
make_lane_helper_qword_2arg(multiply_double_subtract_saturate_long_lane);

#endif
}  // namespace simd
#undef simd
#undef nce
#undef make_lane_helper_dword_1arg
#undef make_lane_helper_qword_1arg
#undef make_lane_helper_dword_2arg
#undef make_lane_helper_qword_2arg
