#pragma once
#include <array>
#include <cstddef>
#include <ranges>
#include <span>
#include <type_traits>
#include "argon/argon_full.hpp"
#include "argon/argon_half.hpp"
#include "argon/vector.hpp"
#include "argon/helpers/multivec.hpp"
#include "argon/store.hpp"
#include "argon/vectorize.hpp"
#include "arm_simd/helpers/scalar.hpp"

#ifdef __ARM_FEATURE_MVE
#define simd helium
#else
#define simd neon
#endif

#ifdef ARGON_PLATFORM_SIMDE
#define ace
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

/// @brief Load data to a set of vector lanes from a pointer with interleaving
/// @tparam lane The lane to load to
/// @tparam stride The stride
/// @tparam argon_type The type to load
/// @param multi The multi-vector to load to
/// @param ptr The pointer to load from
/// @return The altered array of vectors
template <size_t lane, size_t stride, typename argon_type>
ace static std::array<argon_type, stride> load_to_lane_interleaved(
    helpers::MultiVec_t<typename argon_type::vector_type, stride> multi,
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
  return argon::to_array(simd::zip(a, b).val);
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
  return argon::to_array(simd::unzip(a, b).val);
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
  return argon::to_array(simd::transpose(a, b).val);
}

/// @brief Combine two double-word vectors into a single quad-word vector
/// @tparam T The type of the vectors to combine
/// @param low The low half of the vector
/// @param high The high half of the vector
/// @return The combined vector
template <typename T>
ace Argon<T> combine(ArgonHalf<T> low, ArgonHalf<T> high) {
  return simd::combine(low, high);
}

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

/// @brief Create a new vector depending on the result of a conditional
/// @tparam BranchType The type of the branches
/// @tparam CondType The type of the conditional
/// @param condition The condition to check
/// @param true_value The vector to select lanes from if the condition is true
/// @param false_value The vector to select lanes from if the condition is false
/// @return The new vector
/// @warning This function does not short-circuit. It will evaluate both branches regardless of the condition.
/// Due to the way the NEON pipeline works (i.e. without conditional execution flags the way that VFP has),
/// we're required to execute _both_ branches of the conditional and then select the lanes we want, _even if_ one of the branches is
/// completely unused.
template <typename BranchType, typename CondType>
  requires std::is_same_v<Argon<CondType>, typename Argon<BranchType>::argon_result_type>
ace Argon<BranchType> ternary(Argon<CondType> condition, Argon<BranchType> true_value, Argon<BranchType> false_value) {
  if constexpr (std::is_same_v<CondType, BranchType>) {
    return ((condition & true_value) | (~condition & false_value));
  } else {
    return ((condition & true_value.template As<CondType>()) | (~condition & false_value.template As<CondType>()))
        .template As<BranchType>();
  }
}

/// @copydoc ternary
template <typename ValueType, typename CondType>
  requires std::is_arithmetic_v<ValueType> &&
           std::is_same_v<Argon<CondType>, typename Argon<ValueType>::argon_result_type>
ace Argon<ValueType> ternary(Argon<CondType> condition, ValueType true_value, ValueType false_value) {
  return ternary(condition, Argon<ValueType>{true_value}, Argon<ValueType>{false_value});
}

template <typename CondType, typename ScalarType>
  requires std::is_arithmetic_v<ScalarType> && std::is_same_v<CondType, typename Argon<ScalarType>::argon_result_type>
class CondMonad : public std::pair<CondType, Argon<ScalarType>> {
  using ArgonType = Argon<ScalarType>;

 public:
  using PairType = std::pair<CondType, ArgonType>;
  using PairType::PairType;

  constexpr CondType condition() const { return this->first; }
  constexpr ArgonType value() const { return this->second; }

  CondMonad else_if_(CondType new_condition, ArgonType new_value) const {
    CondType exclusive_condition = new_condition & ~condition();
    if constexpr (std::is_same_v<CondType, ArgonType>) {
      // if condition and value are the same type, we can just use the value directly
      new_value = (exclusive_condition & new_value) | (~exclusive_condition & value());
    } else {
      new_value = ((exclusive_condition & new_value.template As<typename CondType::scalar_type>()) |
                   (~exclusive_condition & value().template As<typename CondType::scalar_type>()))
                      .template As<typename ArgonType::scalar_type>();
    }
    return CondMonad{condition() | new_condition, new_value};
  }

  template <typename FunctionType>
  CondMonad else_if_(CondType condition, FunctionType func) const {
    return else_if_(condition, func());
  }

  CondMonad else_if_(CondType condition, ScalarType value) const { return else_if_(condition, ArgonType{value}); }

  ArgonType else_(ArgonType new_value) const {
    if constexpr (std::is_same_v<CondType, ArgonType>) {
      // if condition and value are the same type, we can just use the value directly
      return (condition() & new_value) | (~condition() & value());
    } else {
      // negate mask to get what's left, and select those lanes from the input
      return ((~condition() & new_value.template As<typename CondType::scalar_type>()) |
              (condition() & value().template As<typename CondType::scalar_type>()))
          .template As<typename ArgonType::scalar_type>();
    }
  }

  template <typename FunctionType>
  ArgonType else_(FunctionType func) const {
    return else_(func());
  }

  ArgonType else_(ScalarType value) const { return else_(ArgonType{value}); }
};

template <typename ScalarType, typename CondType>
  requires std::is_arithmetic_v<ScalarType> && std::is_same_v<CondType, typename Argon<ScalarType>::argon_result_type>
ace CondMonad<CondType, ScalarType> if_(CondType condition, Argon<ScalarType> value) {
  return {condition, value};
}

template <typename ScalarType, typename CondType>
  requires std::is_arithmetic_v<ScalarType> && std::is_same_v<CondType, typename Argon<ScalarType>::argon_result_type>
ace CondMonad<CondType, ScalarType> if_(CondType condition, ScalarType value) {
  return {condition, value};
}

template <typename FunctionType, typename CondType>
  requires std::is_arithmetic_v<decltype(std::declval<FunctionType>()())> &&
           std::is_same_v<CondType, decltype(std::declval<FunctionType>()())>
ace CondMonad<CondType, decltype(std::declval<FunctionType>()())> if_(CondType condition, FunctionType func) {
  return {condition, func()};
}

}  // namespace argon

#undef ace
#undef simd
