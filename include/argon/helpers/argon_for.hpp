#pragma once
#include <type_traits>
#include "argon/features.h"
#include "arm_simd/helpers/concepts.hpp"
#include "arm_simd/helpers/scalar.hpp"

#ifdef __ARM_FEATURE_MVE
#define simd helium
#else
#define simd neon
#endif

template <typename T>
class ArgonHalf;
template <typename T>
class Argon;

namespace argon::helpers {

/// @brief Helper template to get the Argon type for a given vector type.
/// @tparam T The vector type to get the Argon type for.
/// @details This template is specialized for either quadword or doubleword types.
template <typename T>
struct ArgonFor;

/// @cond EXCLUDE
template <simd::is_quadword T>
struct ArgonFor<T> {
  using type = Argon<simd::Scalar_t<T>>;
};

#if ARGON_HAS_DWORD
template <simd::is_doubleword T>
struct ArgonFor<T> {
  using type = ArgonHalf<simd::Scalar_t<T>>;
};
#endif
/// @endcond

/// @brief Helper alias to get the Argon type for a given vector type.
/// @tparam T The vector type to get the Argon type for.
template <typename T>
using ArgonFor_t = typename ArgonFor<std::remove_cv_t<T>>::type;
}  // namespace argon::helpers
#undef simd
