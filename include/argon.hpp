#pragma once
#include <array>
#include <concepts>
#include <cstddef>
#include <ranges>
#include <span>
#include <type_traits>
#include "argon/argon_full.hpp"
#include "argon/argon_half.hpp"
#include "argon/helpers/argon_for.hpp"
#include "argon/store.hpp"
#include "argon/vector.hpp"
#include "arm_simd/helpers/multivector.hpp"
#include "arm_simd/helpers/scalar.hpp"

#ifdef __ARM_FEATURE_MVE
#define simd mve
#else
#define simd neon
#endif

#ifdef ARGON_PLATFORM_SIMDE
#define ace [[gnu::always_inline]] inline
#elifdef __clang__
#define ace [[gnu::always_inline]] constexpr
#else
#define ace [[gnu::always_inline]] inline
#endif

namespace argon {

/// @brief Reinterpret a vector of one type to another
/// @tparam T The type to reinterpret to
/// @tparam V The type to reinterpret from
/// @param in The vector to reinterpret
/// @return The reinterpreted vector
template <typename T, typename V>
ace auto reinterpret(Vector<V> in) {
  if constexpr (simd::is_quadword_v<V>) {
    return Argon<T>{simd::reinterpret<typename Argon<T>::vector_type>(in.vec())};
  } else if constexpr (simd::is_doubleword_v<V>) {
    return ArgonHalf<T>{simd::reinterpret<typename ArgonHalf<T>::vector_type>(in.vec())};
  }
}

/// @brief Reinterpret a vector of one type to another
/// @tparam argon_type The type to reinterpret to
/// @tparam V The type to reinterpret from
/// @param in The vector to reinterpret
/// @return The reinterpreted vector
template <typename argon_type, simd::is_vector_type V>
ace argon_type reinterpret(V in) {
  static_assert(!std::is_same_v<typename argon_type::vector_type, V>);
  return argon_type{simd::reinterpret<typename argon_type::vector_type>(in)};
}

/// @brief Reinterpret a vector of one type to another
/// @tparam argon_type The type to reinterpret to
/// @tparam V The type to reinterpret from
/// @param in The vector to reinterpret
/// @return The reinterpreted vector
template <typename ScalarType, typename ArgonType>
ace ScalarType bit_cast(ArgonType in) {
  return in.template As<ScalarType>();
}

/// @brief Load data to a set of vector lanes from a pointer with interleaving
/// @tparam lane The lane to load to
/// @tparam stride The stride
/// @tparam argon_type The type to load
/// @param multi The multi-vector to load to
/// @param ptr The pointer to load from
/// @return The altered array of vectors
template <size_t lane, size_t stride, typename argon_type>
ace static std::array<argon_type, stride> load_to_lane_interleaved(
    simd::MultiVector_t<typename argon_type::vector_type, stride> multi,
    typename argon_type::scalar_type const* ptr) {
  return argon_type::LoadToLaneInterleaved(multi, ptr);
}

/// @brief Load data to a set of vector lanes from a pointer with interleaving

template <size_t lane, size_t stride, typename argon_type>
ace static std::array<argon_type, stride> load_to_lane_interleaved(std::array<argon_type, stride> multi,
                                                                   typename argon_type::scalar_type const* ptr) {
  return argon_type::LoadToLaneInterleaved(multi, ptr);
}

/// @brief Zip two vectors together into a pair of output vectors
/// @tparam argon_type The type of the vectors to zip
/// @param a The first vector
/// @param b The second vector
/// @return The zipped multi-vector
/// @details Given two vectors:  {a0, a1, a2, a3}, {b0, b1, b2, b3}
///          The result will be: {a0, b0, a1, b1}, {a2, b2, a3, b3}
template <typename argon_type>
ace std::array<argon_type, 2> zip(argon_type a, argon_type b) {
  return a.ZipWith(b);
}

/// @brief Unzip vectors into a pair of output vectors
/// @tparam argon_type The type of the vectors to unzip
/// @param a The first vector
/// @param b The second vector
/// @return The unzipped multi-vector
/// @details Given two vectors:  {a0, b0, a1, b1}, {a2, b2, a3, b3}
///          The result will be: {a0, a1, a2, a3}, {b0, b1, b2, b3}
template <typename argon_type>
ace std::array<argon_type, 2> unzip(argon_type a, argon_type b) {
  return a.UnzipWith(b);
}

/// @brief Treats the lanes of its inputs as elements of a 2x2 matrix and transposes the matrices
/// @tparam argon_type The type of the vectors to transpose
/// @param a The first vector
/// @param b The second vector
/// @return The transposed multi-vector
/// @details Given two vectors:  {a0, a1, a2, a3}, {b0, b1, b2, b3}
///          The result will be: {b1, a1, b3, a3}, {b0, a0, b2, a2}
/// @see https://developer.arm.com/documentation/dui0489/i/neon-and-vfp-programming/vtrn
template <typename argon_type>
ace std::array<argon_type, 2> transpose(argon_type a, argon_type b) {
  return a.TransposeWith(b);
}

#ifndef ARGON_PLATFORM_MVE
/// @brief Combine two double-word vectors into a single quad-word vector
/// @tparam T The type of the vectors to combine
/// @param low The low half of the vector
/// @param high The high half of the vector
/// @return The combined vector
template <typename T>
ace Argon<T> combine(ArgonHalf<T> low, ArgonHalf<T> high) {
  return simd::combine(low, high);
}
#endif

/// @brief Load a quad-word vector from a pointer
/// @tparam T The type of the vector to load
/// @param ptr The pointer to load from
/// @return The loaded vector
template <typename T>
ace Argon<T> load(const T* ptr) {
  return Argon<T>::Load(ptr);
}

/// @brief Load a double-word vector from a pointer
/// @tparam T The type of the vector to load
/// @param ptr The pointer to load from
/// @return The loaded vector
template <typename T>
ace ArgonHalf<T> load_half(const T* ptr) {
  return ArgonHalf<T>::Load(ptr);
}

namespace helpers {
/// @brief The lane type for a ScalarType value used alongside VectorType's lanes.
/// @details An integer of the same size and signedness as VectorType's lanes becomes that lane type, so a literal
/// like `3` (int) pairs with int32_t lanes even where int32_t is long (arm-none-eabi), which has no Argon<int>.
template <typename VectorType, typename ScalarType>
using LaneFor_t = std::conditional_t<std::is_integral_v<ScalarType> && std::is_integral_v<simd::Scalar_t<VectorType>> &&
                                         sizeof(ScalarType) == sizeof(simd::Scalar_t<VectorType>) &&
                                         std::is_signed_v<ScalarType> == std::is_signed_v<simd::Scalar_t<VectorType>>,
                                     simd::Scalar_t<VectorType>, ScalarType>;
}  // namespace helpers

/// @brief The Argon type holding ScalarType values with the same width as VectorType (Argon or ArgonHalf).
template <typename VectorType, typename ScalarType>
using VectorFor_t = std::conditional_t<sizeof(VectorType) == 16, Argon<helpers::LaneFor_t<VectorType, ScalarType>>,
                                       ArgonHalf<helpers::LaneFor_t<VectorType, ScalarType>>>;

/// @brief Create a new vector depending on the result of a conditional
/// @tparam VectorType The vector type the condition was computed from
/// @tparam BranchType The type of the branches
/// @param condition The predicate to select by
/// @param true_value The vector to select lanes from if the condition is true
/// @param false_value The vector to select lanes from if the condition is false
/// @return The new vector
/// @warning This function does not short-circuit. It will evaluate both branches regardless of the condition.
/// Due to the way the NEON pipeline works (i.e. without conditional execution flags the way that VFP has),
/// we're required to execute _both_ branches of the conditional and then select the lanes we want, _even if_ one of the
/// branches is completely unused.
template <typename VectorType, typename BranchType>
  requires(BranchType::lanes == Predicate<VectorType>::lanes)
ace BranchType ternary(Predicate<VectorType> condition, BranchType true_value, BranchType false_value) {
#ifndef ARGON_PLATFORM_MVE
  if constexpr (BranchType::extension_arithmetic) {
    return condition.native() ? true_value.vec() : false_value.vec();
  }
#endif
  return condition.Select(true_value, false_value);
}

/// @copydoc ternary
/// @details Selects by a mask vector (all ones / all zeros per lane), e.g. from Predicate::ToMask().
template <typename MaskType, typename BranchType>
  requires std::is_unsigned_v<typename MaskType::scalar_type> && (MaskType::lanes == BranchType::lanes) &&
           (sizeof(typename MaskType::vector_type) == sizeof(typename BranchType::vector_type))
ace BranchType ternary(MaskType mask, BranchType true_value, BranchType false_value) {
  if constexpr (BranchType::extension_arithmetic) {
    return mask.vec() ? true_value.vec() : false_value.vec();
  } else {
    return mask.Select(true_value, false_value);
  }
}

/// @copydoc ternary
template <typename MaskType, typename ValueType>
  requires std::is_unsigned_v<typename MaskType::scalar_type> && std::is_arithmetic_v<ValueType> &&
           (sizeof(ValueType) == sizeof(typename MaskType::scalar_type))
ace auto ternary(MaskType mask, ValueType true_value, ValueType false_value) {
  using result_type = VectorFor_t<typename MaskType::vector_type, ValueType>;
  return ternary(mask, result_type{true_value}, result_type{false_value});
}

template <typename BranchType, typename CondType>
  requires simd::is_vector_type<CondType> && (sizeof(CondType) == sizeof(BranchType))
ace BranchType ternary(CondType condition, BranchType true_value, BranchType false_value) {
  if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
    return condition ? true_value.vec() : false_value.vec();
  } else {
    return helpers::ArgonFor_t<CondType>{condition}.Select(true_value, false_value);
  }
}

/// @copydoc ternary
template <typename VectorType, typename ValueType>
  requires std::is_arithmetic_v<ValueType> && (sizeof(ValueType) == sizeof(simd::Scalar_t<VectorType>))
ace auto ternary(Predicate<VectorType> condition, ValueType true_value, ValueType false_value) {
  using result_type = VectorFor_t<VectorType, ValueType>;
  return ternary(condition, result_type{true_value}, result_type{false_value});
}

/// @brief The result of `if_(...)` and each `else_if_(...)`: a value chosen per lane by a chain of conditions.
/// @tparam VectorType The vector type the conditions were computed from.
/// @tparam ValueType The Argon type of the values being chosen.
/// @details Lanes take the value of the first condition that holds for them, as in an if / else-if chain;
/// `else_` supplies the value for lanes where none held and ends the chain. Every branch is evaluated (see ternary).
template <typename VectorType, typename ValueType>
  requires(ValueType::lanes == Predicate<VectorType>::lanes)
class CondMonad {
  using predicate_type = Predicate<VectorType>;
  using scalar_type = typename ValueType::scalar_type;

 public:
  /// @brief Start a chain: `value` where `condition` holds.
  ace CondMonad(predicate_type condition, ValueType value) : condition_{condition}, value_{value} {}

  /// @brief The lanes some condition in the chain has claimed so far.
  ace predicate_type condition() const { return condition_; }

  /// @brief The values chosen so far; lanes no condition has claimed are unspecified until else_.
  ace ValueType value() const { return value_; }

  /// @brief `new_value` in the lanes where `new_condition` holds and no earlier condition did.
  ace CondMonad else_if_(predicate_type new_condition, ValueType new_value) const {
    return {condition_ | new_condition, condition_.Select(value_, new_value)};
  }

  /// @copydoc else_if_
  ace CondMonad else_if_(predicate_type new_condition, scalar_type new_value) const {
    return else_if_(new_condition, ValueType{new_value});
  }

  /// @copydoc else_if_
  template <std::invocable FunctionType>
  ace CondMonad else_if_(predicate_type new_condition, FunctionType func) const {
    return else_if_(new_condition, ValueType{func()});
  }

  /// @brief `new_value` in the lanes no condition claimed; ends the chain.
  ace ValueType else_(ValueType new_value) const { return condition_.Select(value_, new_value); }

  /// @copydoc else_
  ace ValueType else_(scalar_type new_value) const { return else_(ValueType{new_value}); }

  /// @copydoc else_
  template <std::invocable FunctionType>
  ace ValueType else_(FunctionType func) const {
    return else_(ValueType{func()});
  }

 private:
  predicate_type condition_;
  ValueType value_;
};

/// @brief Start a per-lane if / else-if / else chain: `value` in the lanes where `condition` holds.
/// @details `argon::if_(x < lo, lo).else_if_(x > hi, hi).else_(x)` clamps x to [lo, hi].
template <typename VectorType, typename ValueType>
  requires(ValueType::lanes == Predicate<VectorType>::lanes)
ace CondMonad<VectorType, ValueType> if_(Predicate<VectorType> condition, ValueType value) {
  return {condition, value};
}

/// @copydoc if_
template <typename VectorType, typename ScalarType>
  requires std::is_arithmetic_v<ScalarType> && (sizeof(ScalarType) == sizeof(simd::Scalar_t<VectorType>))
ace auto if_(Predicate<VectorType> condition, ScalarType value) {
  using value_type = VectorFor_t<VectorType, ScalarType>;
  return CondMonad<VectorType, value_type>{condition, value_type{value}};
}

/// @copydoc if_
template <typename VectorType, std::invocable FunctionType>
ace auto if_(Predicate<VectorType> condition, FunctionType func) {
  return if_(condition, func());
}

}  // namespace argon

#undef ace
#undef simd
