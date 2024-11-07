#pragma once
#include <initializer_list>
#include <span>
#include "common.hpp"

#ifdef __ARM_NEON
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#define simd helium
#endif
#endif

#ifdef __clang__
#define ace [[gnu::always_inline]] constexpr
#else
#define ace [[gnu::always_inline]] inline
#endif


template <typename scalar_type>
class Argon128 : public argon::impl::Common<typename simd::Vec128<scalar_type>::type> {
  using T = argon::impl::Common<typename simd::Vec128<scalar_type>::type>;

 public:
  using vector_type = simd::Vec128<scalar_type>::type;
  using lane_type = argon::impl::Lane<vector_type>;

  static_assert(simd::is_quadword_v<vector_type>);

  static constexpr size_t bytes = 16;
  static constexpr size_t lanes = bytes / sizeof(scalar_type);

  ace Argon128() : T(){};
  ace Argon128(vector_type vector) : T(vector){};
  ace Argon128(scalar_type scalar) : T(scalar){};
  ace Argon128(scalar_type const* ptr) : T(ptr){};
  ace Argon128(T&& in) : T(in){};
  ace Argon128(std::array<scalar_type, 4> value_list) : T(value_list.data()) {};
  ace Argon128(std::span<scalar_type> slice) : T(slice) {};
  ace Argon128(Argon64<scalar_type> low, Argon64<scalar_type> high) : T(simd::combine(low, high)) {};

  ace static Argon128<scalar_type> Combine(Argon64<scalar_type> low, Argon64<scalar_type> high) { return simd::combine(low, high); }

  ace Argon128<scalar_type> operator=(scalar_type b) { return this->vec_ = simd::duplicate<vector_type>(b); }
  ace Argon128<scalar_type> operator=(argon::impl::Lane<typename simd::Vec64<scalar_type>::type> b) { return this->vec_ = simd::duplicate_lane<vector_type>(b.vec(), b.lane()); }
  ace Argon128<scalar_type> operator=(argon::impl::Lane<typename simd::Vec128<scalar_type>::type> b) {
    constexpr size_t doubleword_lanes = Argon64<scalar_type>::lanes;
    size_t lane = b.lane();
    Argon128<scalar_type> vec = b.vec();
    Argon64<scalar_type> half;
    if (lane >= doubleword_lanes) {
        half = vec.GetHigh();
        lane -= doubleword_lanes;
    } else {
        half = vec.GetLow();
    }
    return this->vec_ = simd::duplicate_lane<vector_type>(half, lane);
  }


  template <typename U>
  requires argon::impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon128<scalar_type> MultiplyAddLong(Argon64<U> b, Argon64<U> c) const{ return simd::multiply_add_long(this->vec_, b, c); }

  template <typename U>
  requires argon::impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon128<scalar_type> MultiplyAddLong(Argon64<U> b, U c) const { return simd::multiply_add_long(this->vec_, b, c); }

  template <typename U>
  requires argon::impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon128<scalar_type> MultiplyAddLong(Argon64<U> b, typename Argon64<U>::lane_type c) const { return simd::multiply_add_long(this->vec_, b, c.vec(), c.lane()); }

  template <typename U>
  requires argon::impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon128<scalar_type> MultiplySubtractLong(Argon64<U> b, Argon64<U> c) const { return simd::multiply_subtract_long(this->vec_, b, c); }

  template <typename U>
  requires argon::impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon128<scalar_type> MultiplySubtractLong(Argon64<U> b, U c) const { return simd::multiply_subtract_long(this->vec_, b, c); }

  template <typename U>
  requires argon::impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon128<scalar_type> MultiplySubtractLong(Argon64<U> b, typename Argon64<U>::lane_type c) const { return simd::multiply_subtract_long(this->vec_, b, c.vec(), c.lane()); }

  template <typename U>
  requires argon::impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon64<U> AddNarrow(Argon128<scalar_type> b) { return simd::add_narrow(this->vec_, b); }

  template <typename U>
  requires argon::impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon64<U> AddRoundNarrow(Argon128<scalar_type> b) { return simd::add_round_narrow(this->vec_, b); }

  template <typename U>
  requires argon::impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon64<U> SubtractNarrow(Argon128<scalar_type> b) { return simd::subtract_narrow(this->vec_, b); }

  template <typename U>
  requires argon::impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon64<U> SubtractRoundNarrow(Argon128<scalar_type> b) { return simd::subtract_round_narrow(this->vec_, b); }

  template <size_t n, typename U>
  requires argon::impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon64<U> ShiftRightNarrow() { return simd::shift_right_narrow<n>(this->vec_); }

  template <size_t n, typename U>
  requires argon::impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon64<U> ShiftRightSaturateNarrow() { return simd::shift_right_saturate_narrow<n>(this->vec_); }

  template <size_t n, typename U>
  requires argon::impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon64<U> ShiftRightRoundSaturateNarrow() { return simd::shift_right_round_saturate_narrow<n>(this->vec_); }

  template <size_t n, typename U>
  requires argon::impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon64<U> ShiftRightRoundNarrow() { return simd::shift_right_round_narrow<n>(this->vec_); }

  template <typename U>
  requires argon::impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon64<U> Narrow(Argon128<scalar_type> b) { return simd::move_narrow(this->vec_); }

  template <typename U>
  requires argon::impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon64<U> SaturateNarrow(Argon128<scalar_type> b) { return simd::move_saturate_narrow(this->vec_); }

  ace Argon64<scalar_type> GetHigh() { return simd::get_high(this->vec_); }
  ace Argon64<scalar_type> GetLow() { return simd::get_low(this->vec_); }

  template <typename U> ace Argon128<U> Convert() { return simd::convert<typename simd::Vec128<U>::type>(this->vec_); }
  template <typename U> ace Argon128<U> Convert(int n) { return simd::convert_n<typename simd::Vec128<U>::type>(this->vec_, n); }
};

template <typename V>
requires std::is_scalar_v<V>
ace Argon128<V> operator+(V a, Argon128<V> b) {
  return b.Add(a);
}

template <typename V>
requires std::is_scalar_v<V>
ace Argon128<V> operator-(V a, Argon128<V> b) {
  return Argon128<V>{a}.Subtract(b);
}

template <typename V>
requires std::is_scalar_v<V>
ace Argon128<V> operator*(V a, Argon128<V> b) {
  return b.Multiply(a);
}

template <typename V>
requires std::is_scalar_v<V>
ace Argon128<V> operator/(V a, Argon128<V> b) {
  return Argon128<V>{a}.Divide(b);
}

#undef ace
#undef simd
