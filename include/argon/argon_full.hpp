#pragma once
#include "arm_simd.hpp"
#include "common.hpp"
#include "helpers.hpp"

#ifdef __ARM_NEON
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#define simd helium
#endif
#endif

#ifdef __clang__
#define ace [[nodiscard]] [[gnu::always_inline]] constexpr
#else
#define ace [[nodiscard]] [[gnu::always_inline]] inline
#endif

template <typename scalar_type>
class Argon : public argon::impl::Common<simd::Vec128_t<scalar_type>> {
  using T = argon::impl::Common<simd::Vec128_t<scalar_type>>;

 public:
  using vector_type = simd::Vec128_t<scalar_type>;
  using lane_type = const argon::impl::Lane<vector_type>;

  static_assert(simd::is_quadword_v<vector_type>);

  static constexpr size_t bytes = 16;
  static constexpr size_t lanes = bytes / sizeof(scalar_type);

  ace Argon() : T() {};
  ace Argon(vector_type vector) : T{vector} {};
  ace Argon(scalar_type scalar) : T{scalar} {};
  // ace Argon(scalar_type const* ptr) : T{ptr} {};
  ace Argon(T&& in) : T(in) {};
  ace Argon(std::array<scalar_type, 4> value_list) : T{T::Load(value_list.data())} {};
  // ace Argon(std::span<scalar_type> slice) : T{slice} {};
  ace Argon(ArgonHalf<scalar_type> low, ArgonHalf<scalar_type> high) : T{Combine(low, high)} {};

  template <typename... arg_types>
    requires(sizeof...(arg_types) > 1)
  ace Argon(arg_types... args) : T{vector_type{args...}} {}

  template <simd::is_vector_type intrinsic_type>
  ace Argon(argon::impl::Lane<intrinsic_type> b) : T{b} {};

  template <typename new_scalar_type>
  ace Argon<new_scalar_type> As() const {
    return simd::reinterpret<simd::Vec128_t<new_scalar_type>>(this->vec_);
  }

  ace static Argon<scalar_type> Combine(ArgonHalf<scalar_type> low, ArgonHalf<scalar_type> high) {
    return simd::combine(low, high);
  }

  ace Argon<scalar_type> Reverse() {
    auto rev_half = this->Reverse64bit();
    return Combine(rev_half.GetHigh(), rev_half.GetLow());
  }

  template <typename U>
    requires argon::impl::has_smaller_v<scalar_type> &&
             std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon<scalar_type> MultiplyAddLong(ArgonHalf<U> b, ArgonHalf<U> c) {
    return simd::multiply_add_long(this->vec_, b, c);
  }
  template <typename U>
    requires argon::impl::has_smaller_v<scalar_type>
  ace Argon<scalar_type> MultiplyAddLong(ArgonHalf<U> b, simd::Vec64_t<argon::impl::NextSmaller_t<scalar_type>> c) {
    return simd::multiply_add_long(this->vec_, b, c);
  }

  template <typename U>
    requires argon::impl::has_smaller_v<scalar_type> &&
             std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon<scalar_type> MultiplyAddLong(ArgonHalf<U> b, U c) {
    return simd::multiply_add_long(this->vec_, b, c);
  }

  template <typename U>
    requires argon::impl::has_smaller_v<scalar_type> &&
             std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon<scalar_type> MultiplyAddLong(ArgonHalf<U> b, typename ArgonHalf<U>::lane_type c) {
    return simd::multiply_add_long(this->vec_, b, c.vec(), c.lane());
  }

  template <typename U>
    requires argon::impl::has_smaller_v<scalar_type> &&
             std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon<scalar_type> MultiplySubtractLong(ArgonHalf<U> b, ArgonHalf<U> c) {
    return simd::multiply_subtract_long(this->vec_, b, c);
  }

  template <typename U>
    requires argon::impl::has_smaller_v<scalar_type> &&
             std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon<scalar_type> MultiplySubtractLong(ArgonHalf<U> b, U c) {
    return simd::multiply_subtract_long(this->vec_, b, c);
  }

  template <typename U>
    requires argon::impl::has_smaller_v<scalar_type> &&
             std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon<scalar_type> MultiplySubtractLong(ArgonHalf<U> b, typename ArgonHalf<U>::lane_type c) {
    return simd::multiply_subtract_long(this->vec_, b, c.vec(), c.lane());
  }

  ace ArgonHalf<argon::impl::NextSmaller_t<scalar_type>> AddNarrow(Argon<scalar_type> b) const
    requires argon::impl::has_smaller_v<scalar_type>
  {
    return simd::add_narrow(this->vec_, b);
  }

  ace ArgonHalf<argon::impl::NextSmaller_t<scalar_type>> AddRoundNarrow(Argon<scalar_type> b) const
    requires argon::impl::has_smaller_v<scalar_type>
  {
    return simd::add_round_narrow(this->vec_, b);
  }

  ace ArgonHalf<argon::impl::NextSmaller_t<scalar_type>> SubtractNarrow(Argon<scalar_type> b) const
    requires argon::impl::has_smaller_v<scalar_type>
  {
    return simd::subtract_narrow(this->vec_, b);
  }

  ace ArgonHalf<argon::impl::NextSmaller_t<scalar_type>> SubtractRoundNarrow(Argon<scalar_type> b) const
    requires argon::impl::has_smaller_v<scalar_type>
  {
    return simd::subtract_round_narrow(this->vec_, b);
  }

  template <size_t n>
    requires argon::impl::has_smaller_v<scalar_type>
  ace ArgonHalf<argon::impl::NextSmaller_t<scalar_type>> ShiftRightNarrow() const {
    return simd::shift_right_narrow<n>(this->vec_);
  }

  template <size_t n>
    requires argon::impl::has_smaller_v<scalar_type>
  ace ArgonHalf<argon::impl::NextSmaller_t<scalar_type>> ShiftRightSaturateNarrow() const {
    return simd::shift_right_saturate_narrow<n>(this->vec_);
  }

  template <size_t n>
    requires argon::impl::has_smaller_v<scalar_type>
  ace ArgonHalf<argon::impl::NextSmaller_t<scalar_type>> ShiftRightRoundSaturateNarrow() const {
    return simd::shift_right_round_saturate_narrow<n>(this->vec_);
  }

  template <size_t n>
    requires argon::impl::has_smaller_v<scalar_type>
  ace ArgonHalf<argon::impl::NextSmaller_t<scalar_type>> ShiftRightRoundNarrow() const {
    return simd::shift_right_round_narrow<n>(this->vec_);
  }

  ace ArgonHalf<argon::impl::NextSmaller_t<scalar_type>> Narrow() const
    requires argon::impl::has_smaller_v<scalar_type>
  {
    return simd::move_narrow(this->vec_);
  }

  ace ArgonHalf<argon::impl::NextSmaller_t<scalar_type>> SaturateNarrow() const
    requires argon::impl::has_smaller_v<scalar_type>
  {
    return simd::move_saturate_narrow(this->vec_);
  }

  ace Argon<scalar_type> MultiplyDoubleAddSaturateLong(ArgonHalf<argon::impl::NextSmaller_t<scalar_type>> b,
                                                       ArgonHalf<argon::impl::NextSmaller_t<scalar_type>> c)
    requires argon::impl::has_smaller_v<scalar_type>
  {
    return neon::multiply_double_add_saturate_long(this->vec_, b, c);
  }

  ace ArgonHalf<scalar_type> GetHigh() const { return simd::get_high(this->vec_); }
  ace ArgonHalf<scalar_type> GetLow() const { return simd::get_low(this->vec_); }

  template <typename U>
  ace Argon<U> ConvertTo() const {
    return simd::convert<typename simd::Vec128<U>::type>(this->vec_);
  }
  template <typename U, int fracbits>
    requires(std::is_same_v<U, uint32_t> || std::is_same_v<U, int32_t> || std::is_same_v<U, float>)
  ace Argon<U> ConvertTo() const {
    if constexpr (std::is_same_v<U, float>) {
      return neon::convert_n<fracbits>(this->vec_);
    } else if constexpr (std::is_unsigned_v<U>) {
      return neon::convert_n_unsigned<fracbits>(this->vec_);
    } else if constexpr (std::is_signed_v<U>) {
      return neon::convert_n_signed<fracbits>(this->vec_);
    }
  }

  scalar_type ReduceAdd() {
#ifdef __aarch64__
    return simd::reduce_add(this->vec_);
#else
    auto rev = SwapDoublewords();
    auto sum = Add(rev);
    if constexpr (lanes == 16) {
      rev = sum.Reverse16bit();
      sum = sum.Add(rev);
    }
    if constexpr (lanes == 8 || lanes == 16) {
      rev = sum.Reverse32bit();
      sum = sum.Add(rev);
    }
    if constexpr (lanes == 4 || lanes == 8 || lanes == 16) {
      rev = sum.Reverse64bit();
      sum = sum.Add(rev);
    }
    return sum[0];
#endif
  }

  ace Argon<scalar_type> SwapDoublewords() { return Combine(GetHigh(), GetLow()); }
};

template <typename... arg_types>
  requires(sizeof...(arg_types) > 1)
// Argon(arg_types...) -> Argon<arg_types...[0]>;
Argon(arg_types...) -> Argon<std::tuple_element_t<0, std::tuple<arg_types...>>>;

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
  using type = argon::impl::Lane<typename Argon<T>::vector_type>;
};
}  // namespace std

#undef ace
#undef simd
