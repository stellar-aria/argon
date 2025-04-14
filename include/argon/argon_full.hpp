#pragma once
#include <array>
#include <numeric>
#include <type_traits>
#include "arm_simd.hpp"
#include "helpers.hpp"
#include "helpers/argon_for.hpp"
#include "vector.hpp"

#ifdef __ARM_FEATURE_MVE
#define simd mve
#else
#define simd neon
#endif

#ifdef __clang__
#define ace [[nodiscard]] [[gnu::always_inline]] constexpr
#else
#define ace [[nodiscard]] [[gnu::always_inline]] inline
#endif

template <typename ScalarType>
  requires std::is_arithmetic_v<ScalarType>
class Argon : public argon::Vector<simd::Vec128_t<ScalarType>> {
  using T = argon::Vector<simd::Vec128_t<ScalarType>>;

 public:
  using vector_type = simd::Vec128_t<ScalarType>;
  using lane_type = const argon::Lane<vector_type>;

  static_assert(simd::is_quadword_v<vector_type>);

  static constexpr size_t bytes = 16;
  static constexpr size_t lanes = bytes / sizeof(ScalarType);

  using argon::Vector<vector_type>::Vector;
  ace Argon(argon::Vector<vector_type> vec) : T{std::move(vec)} {};
  ace Argon(std::array<ScalarType, 4> value_list) : T{T::Load(value_list.data())} {};
  ace Argon(ArgonHalf<ScalarType> low, ArgonHalf<ScalarType> high) : T{Combine(low, high)} {};

#ifndef ARGON_PLATFORM_MVE
  ace Argon(argon::Lane<vector_type> b) : T{b} {};
  ace Argon(argon::ConstLane<0, vector_type> b) : T{b} {};
#endif

  template <simd::is_vector_type intrinsic_type>
  ace Argon(argon::Lane<intrinsic_type> b) : T{b} {};

  template <typename new_scalar_type>
  ace Argon<new_scalar_type> As() const {
    return simd::reinterpret<simd::Vec128_t<new_scalar_type>>(this->vec_);
  }

#ifndef ARGON_PLATFORM_MVE
  ace static Argon<ScalarType> Combine(ArgonHalf<ScalarType> low, ArgonHalf<ScalarType> high) {
    return simd::combine(low, high);
  }

  ace Argon<ScalarType> Reverse() {
    auto rev_half = this->Reverse64bit();
    return Combine(rev_half.GetHigh(), rev_half.GetLow());
  }

  template <typename U>
    requires argon::helpers::has_smaller_v<ScalarType> &&
             std::is_same_v<U, typename argon::helpers::NextSmaller<ScalarType>::type>
  ace Argon<ScalarType> MultiplyAddLong(ArgonHalf<U> b, ArgonHalf<U> c) {
    return simd::multiply_add_long(this->vec_, b, c);
  }
  template <typename U, typename C>
    requires argon::helpers::has_smaller_v<ScalarType> &&
             std::is_same_v<C, simd::Vec64_t<argon::helpers::NextSmaller_t<ScalarType>>>
  ace Argon<ScalarType> MultiplyAddLong(ArgonHalf<U> b, C c) {
    return simd::multiply_add_long(this->vec_, b, c);
  }

  template <typename U>
    requires argon::helpers::has_smaller_v<ScalarType> &&
             std::is_same_v<U, typename argon::helpers::NextSmaller<ScalarType>::type>
  ace Argon<ScalarType> MultiplyAddLong(ArgonHalf<U> b, U c) {
    return simd::multiply_add_long(this->vec_, b, c);
  }

  template <typename U>
    requires argon::helpers::has_smaller_v<ScalarType> &&
             std::is_same_v<U, typename argon::helpers::NextSmaller<ScalarType>::type>
  ace Argon<ScalarType> MultiplyAddLong(ArgonHalf<U> b, typename ArgonHalf<U>::lane_type c) {
    return simd::multiply_add_long(this->vec_, b, c.vec(), c.lane());
  }

  template <typename U>
    requires argon::helpers::has_smaller_v<ScalarType> &&
             std::is_same_v<U, typename argon::helpers::NextSmaller<ScalarType>::type>
  ace Argon<ScalarType> MultiplySubtractLong(ArgonHalf<U> b, ArgonHalf<U> c) {
    return simd::multiply_subtract_long(this->vec_, b, c);
  }

  template <typename U>
    requires argon::helpers::has_smaller_v<ScalarType> &&
             std::is_same_v<U, typename argon::helpers::NextSmaller<ScalarType>::type>
  ace Argon<ScalarType> MultiplySubtractLong(ArgonHalf<U> b, U c) {
    return simd::multiply_subtract_long(this->vec_, b, c);
  }

  template <typename U>
    requires argon::helpers::has_smaller_v<ScalarType> &&
             std::is_same_v<U, typename argon::helpers::NextSmaller<ScalarType>::type>
  ace Argon<ScalarType> MultiplySubtractLong(ArgonHalf<U> b, typename ArgonHalf<U>::lane_type c) {
    return simd::multiply_subtract_long(this->vec_, b, c.vec(), c.lane());
  }

  ace auto AddNarrow(Argon<ScalarType> b) const
    requires argon::helpers::has_smaller_v<ScalarType>
  {
    auto result = simd::add_narrow(this->vec_, b);
    return argon::helpers::ArgonFor_t<decltype(result)>{result};
  }

  ace auto AddRoundNarrow(Argon<ScalarType> b) const
    requires argon::helpers::has_smaller_v<ScalarType>
  {
    auto result = simd::add_round_narrow(this->vec_, b);
    return argon::helpers::ArgonFor_t<decltype(result)>{result};
  }

  ace auto SubtractNarrow(Argon<ScalarType> b) const
    requires argon::helpers::has_smaller_v<ScalarType>
  {
    auto result = simd::subtract_narrow(this->vec_, b);
    return argon::helpers::ArgonFor_t<decltype(result)>{result};
  }

  ace auto SubtractRoundNarrow(Argon<ScalarType> b) const
    requires argon::helpers::has_smaller_v<ScalarType>
  {
    auto result = simd::subtract_round_narrow(this->vec_, b);
    return argon::helpers::ArgonFor_t<decltype(result)>{result};
  }

  template <size_t n>
    requires argon::helpers::has_smaller_v<ScalarType>
  ace auto ShiftRightNarrow() const {
    auto result = simd::shift_right_narrow<n>(this->vec_);
    return argon::helpers::ArgonFor_t<decltype(result)>{result};
  }

  template <size_t n>
    requires argon::helpers::has_smaller_v<ScalarType>
  ace auto ShiftRightSaturateNarrow() const {
    auto result = simd::shift_right_saturate_narrow<n>(this->vec_);
    return argon::helpers::ArgonFor_t<decltype(result)>{result};
  }

  template <size_t n>
    requires argon::helpers::has_smaller_v<ScalarType>
  ace auto ShiftRightRoundSaturateNarrow() const {
    auto result = simd::shift_right_round_saturate_narrow<n>(this->vec_);
    return argon::helpers::ArgonFor_t<decltype(result)>{result};
  }

  template <size_t n>
    requires argon::helpers::has_smaller_v<ScalarType>
  ace auto ShiftRightRoundNarrow() const {
    auto result = simd::shift_right_round_narrow<n>(this->vec_);
    return argon::helpers::ArgonFor_t<decltype(result)>{result};
  }

  ace auto Narrow() const
    requires argon::helpers::has_smaller_v<ScalarType>
  {
    auto result = simd::move_narrow(this->vec_);
    return argon::helpers::ArgonFor_t<decltype(result)>{result};
  }

  ace auto SaturateNarrow() const
    requires argon::helpers::has_smaller_v<ScalarType>
  {
    auto result = simd::move_saturate_narrow(this->vec_);
    return argon::helpers::ArgonFor_t<decltype(result)>{result};
  }

  template <typename NextSmallerType>
    requires argon::helpers::has_smaller_v<ScalarType> &&
             std::is_same_v<NextSmallerType, argon::helpers::NextSmaller_t<ScalarType>>
  ace Argon<ScalarType> MultiplyDoubleAddSaturateLong(ArgonHalf<NextSmallerType> b, ArgonHalf<NextSmallerType> c) {
    return neon::multiply_double_add_saturate_long(this->vec_, b, c);
  }

  ace ArgonHalf<ScalarType> GetHigh() const { return simd::get_high(this->vec_); }
  ace ArgonHalf<ScalarType> GetLow() const { return simd::get_low(this->vec_); }
#endif

  template <typename U>
  ace Argon<U> ConvertTo() const {
    return simd::convert<typename simd::Vec128<U>::type>(this->vec_);
  }

  template <typename U, int fracbits>
    requires(std::is_same_v<U, uint32_t> || std::is_same_v<U, int32_t> || std::is_same_v<U, float>)
  ace Argon<U> ConvertTo() const {
    if constexpr (std::is_same_v<U, float>) {
      return simd::convert_n<fracbits>(this->vec_);
    } else if constexpr (std::is_unsigned_v<U>) {
      return simd::convert_n_unsigned<fracbits>(this->vec_);
    } else if constexpr (std::is_signed_v<U>) {
      return simd::convert_n_signed<fracbits>(this->vec_);
    }
  }

  ace Argon<ScalarType> Reverse() const {
    Argon<ScalarType> rev = this->Reverse64bit();  // rev within dword
    return Argon{rev.GetHigh(), rev.GetLow()};     // swap dwords
  }

  template <typename CommutableOpType>
  ScalarType Reduce(CommutableOpType op) {
    auto rev = this->SwapDoublewords();
    auto sum = op(*this, rev);
    if constexpr (lanes == 16) {
      sum = op(*this, sum.Reverse16bit());
    }
    if constexpr (lanes == 8 || lanes == 16) {
      sum = op(*this, sum.Reverse32bit());
    }
    if constexpr (lanes == 4 || lanes == 8 || lanes == 16) {
      sum = op(*this, sum.Reverse64bit());
    }
    return sum[0];
  }

  ScalarType ReduceAdd() {
#ifdef __aarch64__
    return simd::reduce_add(this->vec_);
#else
    return this->Reduce([](auto a, auto b) { return a + b; });
#endif
  }

  ScalarType ReduceMax() {
#ifdef __aarch64__
    return simd::reduce_max(this->vec_);
#else
    return this->Reduce([](auto a, auto b) { return std::max(a, b); });
#endif
  }

  ScalarType ReduceMin() {
#ifdef __aarch64__
    return simd::reduce_min(this->vec_);
#else
    auto arr = this->to_array();
    return std::reduce(arr.begin(), arr.end(), arr[0], [](auto a, auto b) { return std::min(a, b); });
#endif
  }

#ifndef ARGON_PLATFORM_MVE
  ace Argon<ScalarType> SwapDoublewords() { return Combine(GetHigh(), GetLow()); }
#endif
};

template <typename... arg_types>
  requires(sizeof...(arg_types) > 1)
// Argon(arg_types...) -> Argon<arg_types...[0]>;
Argon(arg_types...) -> Argon<std::tuple_element_t<0, std::tuple<arg_types...>>>;

#ifndef ARGON_PLATFORM_MVE
template <typename VectorType>
Argon(argon::Lane<VectorType>) -> Argon<simd::Scalar_t<VectorType>>;

template <typename VectorType>
Argon(argon::ConstLane<0, VectorType>) -> Argon<simd::Scalar_t<VectorType>>;
#endif

template <typename ScalarType>
  requires std::is_scalar_v<ScalarType>
Argon(ScalarType) -> Argon<ScalarType>;

template <typename V>
  requires std::is_scalar_v<V>
ace Argon<V> operator+(const V a, const Argon<V> b) {
  return b.Add(a);
}

template <typename V>
  requires std::is_scalar_v<V>
ace Argon<V> operator-(const V a, const Argon<V> b) {
  return Argon<V>{a}.Subtract(b);
}

template <typename V>
  requires std::is_scalar_v<V>
ace Argon<V> operator*(const V a, const Argon<V> b) {
  return b.Multiply(a);
}

template <typename V>
  requires std::is_scalar_v<V>
ace Argon<V> operator/(const V a, const Argon<V> b) {
  return Argon<V>{a}.Divide(b);
}

namespace std {

template <typename T>
struct tuple_size<Argon<T>> {
  static constexpr size_t value = Argon<T>::lanes;
};

template <size_t Index, typename T>
struct tuple_element<Index, Argon<T>> {
  static_assert(Index < Argon<T>::lanes);
  using type = argon::Lane<typename Argon<T>::vector_type>;
};
}  // namespace std

#undef ace
#undef simd
