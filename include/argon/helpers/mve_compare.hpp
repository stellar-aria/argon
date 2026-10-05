#pragma once
#include <type_traits>
#include "argon/features.h"

#ifdef ARGON_PLATFORM_MVE
#include <arm_mve.h>
#include "arm_simd.hpp"
#include "bool.hpp"

/// @file mve_compare.hpp
/// @brief Lane comparisons for MVE, which produce an mve_pred16_t rather than a mask vector.

namespace argon::helpers {

/// @brief The comparisons MVE provides natively; less-than forms are expressed by swapping the operands.
enum class MveComparison { Equal, GreaterThan, GreaterThanOrEqual };

/// @brief Compare the lanes of two vectors, returning MVE's per-byte predicate.
/// @details The mve:: layer names these differently for signed (greater_than), unsigned (higher) and floating-point
/// (compare_greater_than) vectors; this picks the right one.
/// @tparam op The comparison to perform.
/// @param a The left-hand operand.
/// @param b The right-hand operand.
/// @return A predicate with every byte of each lane set where the comparison holds.
/// @param active Optionally, compare only these lanes (vcmpq_m): the result is inactive wherever `active` is.
template <MveComparison op, typename VectorType, typename... PredicateType>
[[gnu::always_inline]] inline mve_pred16_t mve_compare(VectorType a, VectorType b, PredicateType... active) {
  using scalar_type = mve::Scalar_t<VectorType>;
  if constexpr (op == MveComparison::Equal) {
    if constexpr (!std::is_integral_v<scalar_type>) {
      return mve::compare_equal(a, b, active...);
    } else {
      return mve::equal(a, b, active...);
    }
  } else if constexpr (op == MveComparison::GreaterThan) {
    if constexpr (!std::is_integral_v<scalar_type>) {
      return mve::compare_greater_than(a, b, active...);
    } else if constexpr (std::is_signed_v<scalar_type>) {
      return mve::greater_than(a, b, active...);
    } else {
      return mve::higher(a, b, active...);
    }
  } else {
    if constexpr (!std::is_integral_v<scalar_type>) {
      return mve::compare_greater_than_or_equal(a, b, active...);
    } else if constexpr (std::is_signed_v<scalar_type>) {
      return mve::greater_than_or_equal(a, b, active...);
    } else {
      return mve::higher_or_same(a, b, active...);
    }
  }
}

/// @brief Expand an MVE predicate into a NEON-style mask vector (all ones where active, all zeros otherwise).
/// @tparam VectorType The vector type the predicate was produced from.
/// @param p The predicate.
/// @return The mask vector, of type Bool_t<VectorType>.
template <typename VectorType>
[[gnu::always_inline]] inline Bool_t<VectorType> mve_mask(mve_pred16_t p) {
  using mask_type = Bool_t<VectorType>;
  using mask_scalar = mve::Scalar_t<mask_type>;
  return mve::predicate_select(mve::duplicate(static_cast<mask_scalar>(~mask_scalar{0})),
                               mve::duplicate(mask_scalar{0}), p);
}

}  // namespace argon::helpers
#endif
