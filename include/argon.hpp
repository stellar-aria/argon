#pragma once
#include <arm_neon.h>
#include <array>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <type_traits>
#include <span>
#include "neon.hpp"
#include "neon/helpers.hpp"
#include <cassert>

#ifdef __clang__
#define ace [[gnu::always_inline]] constexpr
#else
#define ace [[gnu::always_inline]] inline
#endif

namespace argon {
namespace impl {
template <typename type>
struct Vec64 {};
template <typename type>
struct Vec128 {};

// clang-format off
template <> struct Vec64<int8_t> {using type = int8x8_t; };
template <> struct Vec128<int8_t>  {using type = int8x16_t; };

template <> struct Vec64<uint8_t> {using type = uint8x8_t; };
template <> struct Vec128<uint8_t>  {using type = uint8x16_t; };

template <> struct Vec64<int16_t> {using type = int16x4_t; };
template <> struct Vec128<int16_t>  {using type = int16x8_t; };

template <> struct Vec64<uint16_t> {using type = uint16x4_t; };
template <> struct Vec128<uint16_t>  {using type = uint16x8_t; };

template <> struct Vec64<int32_t> {using type = int32x2_t; };
template <> struct Vec128<int32_t>  {using type = int32x4_t; };

template <> struct Vec64<uint32_t> {using type = uint32x2_t; };
template <> struct Vec128<uint32_t>  {using type = uint32x4_t; };

template <> struct Vec64<int64_t> {using type = int64x1_t; };
template <> struct Vec128<int64_t>  {using type = int64x2_t; };

template <> struct Vec64<uint64_t> {using type = uint64x1_t; };
template <> struct Vec128<uint64_t>  {using type = uint64x2_t; };

template <> struct Vec64<float> {using type = float32x2_t; };
template <> struct Vec128<float>  {using type = float32x4_t; };

template <typename T> struct NextLarger;
template <> struct NextLarger<int8_t> {using type = int16_t; };
template <> struct NextLarger<uint8_t> {using type = uint16_t; };
template <> struct NextLarger<int16_t> {using type = int32_t; };
template <> struct NextLarger<uint16_t> {using type = uint32_t; };
template <> struct NextLarger<int32_t> {using type = int64_t; };
template <> struct NextLarger<uint32_t> {using type = uint64_t; };
template <> struct NextLarger<float> {using type = double; };

template <typename T> struct Result;
template <> struct Result<int8x8_t> {using type = uint8x8_t; };
template <> struct Result<uint8x8_t> {using type = uint8x8_t; };
template <> struct Result<int16x4_t> {using type = uint16x4_t; };
template <> struct Result<uint16x4_t> {using type = uint16x4_t; };
template <> struct Result<int32x2_t> {using type = uint32x2_t; };
template <> struct Result<uint32x2_t> {using type = uint32x2_t; };
template <> struct Result<int8x16_t> {using type = uint8x16_t; };
template <> struct Result<uint8x16_t> {using type = uint8x16_t; };
template <> struct Result<int16x8_t> {using type = uint16x8_t; };
template <> struct Result<uint16x8_t> {using type = uint16x8_t; };
template <> struct Result<int32x4_t> {using type = uint32x4_t; };
template <> struct Result<uint32x4_t> {using type = uint32x4_t; };
template <> struct Result<int64x1_t> {using type = uint64x1_t; };
template <> struct Result<uint64x1_t> {using type = uint64x1_t; };
template <> struct Result<int64x2_t> {using type = uint64x2_t; };
template <> struct Result<uint64x2_t> {using type = uint64x2_t; };
template <> struct Result<float32x2_t> {using type = uint32x2_t; };
template <> struct Result<float32x4_t> {using type = uint32x4_t; };

// clang-format on

template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template <typename vector_type>
class FloatCommon {
  using base_type = neon::NonVec<vector_type>::type;

 public:
  using T = FloatCommon<vector_type>;
};

template <typename vector_type>
class Lane;

template <typename vector_type>
class Common {
  using base_type = neon::NonVec<vector_type>::type;
  using result_type = Result<vector_type>::type;

 public:
  using T = Common<vector_type>;
  static constexpr size_t lanes = (neon::is_quadword_v<vector_type> ? 16 : 8) / sizeof(base_type);

  constexpr Common() : vec_{0} {};
  constexpr Common(vector_type vector) : vec_(vector){};
  ace Common(base_type base) : vec_(LoadCopy(base)){};
  ace Common(base_type const* base_ptr) : vec_(Load(base_ptr)){};
  ace Common(std::span<base_type> slice) : vec_(Load(slice.data())){
    static_assert(slice.size() == lanes);
  };
  ace Common(std::initializer_list<base_type> value_list) : vec_(Load(value_list.begin())) {};

  ace T operator=(base_type b) { return vec_ = LoadCopy(b); }

  ace T operator-() const { return Negate(); }

  ace T operator+(T b) const { return Add(b); }
  ace T operator-(T b) const { return Subtract(b); }
  ace T operator*(T b) const { return Multiply(b); }
  ace T operator/(T b) const { return Divide(b); }

  ace T operator+=(T b) { return vec_ = Add(b); }
  ace T operator-=(T b) { return vec_ = Subtract(b); }
  ace T operator*=(T b) { return vec_ = Multiply(b); }
  ace T operator/=(T b) { return vec_ = Divide(b); }

  ace Common<result_type> operator==(T b) const { return Equal(b); }
  ace Common<result_type> operator<(T b) const { return LessThan(b); }
  ace Common<result_type> operator>(T b) const { return GreaterThan(b); }
  ace Common<result_type> operator<=(T b) const { return LessThanOrEqual(b); }
  ace Common<result_type> operator>=(T b) const { return GreaterThanOrEqual(b); }

  ace T operator++() const { return Add(1); }
  ace T operator--() const { return Subtract(1); }

  ace T operator&(T b) const { return AndBitwise(b); }
  ace T operator|(T b) const { return OrBitwise(b); }
  ace T operator^(T b) const { return XorBitwise(b); }
  ace T operator~() const { return NotBitwise(); }

  ace Lane<vector_type> operator[](const int i) const { return Lane{vec_, i}; }

  ace T operator>>(const int i) const { return ShiftRight(i); }
  ace T operator<<(const int i) const { return ShiftLeft(i); }

  [[gnu::always_inline]] constexpr operator vector_type() const { return vec_; }

  ace std::array<base_type, lanes> as_array() {
    std::array<base_type, lanes> out{0};
    Store(out.data());
    return out;
  }

  ace vector_type vec() const { return vec_; }

  ace base_type Get(const int i) const { return neon::get<vector_type>(vec_, i); }

  ace base_type Set(const int i, base_type b) const { return neon::set(vec_, i, b); }

  ace T ShiftRight(const int i) const { return neon::shift_right(vec_, i); }

  ace T ShiftLeft(const int i) const { return neon::shift_left(vec_, i); }

  ace T Negate() const { return neon::negate(vec_); }

  ace T Add(T b) const { return neon::add(vec_, b); }

  ace T AddHalve(T b) const { return neon::add_halve(vec_, b); }

  ace T AddHalveRound(T b) const { return neon::add_halve_round(vec_, b); }

  ace T AddSaturate(T b) const { return neon::add_saturate(vec_, b); }

  ace T Multiply(T b) const { return neon::multiply(vec_, b); }

  ace T MultiplyAdd(T b, T c) const { return neon::multiply_add(vec_, b, b); }

  ace T MultiplySubtract(T b, T c) const { return neon::multiply_subtract(vec_, b, b); }

  ace T Subtract(T b) const { return neon::subtract(vec_, b); }

  ace T SubtractHigh(T b) const { return neon::subtract_high(vec_, b); }

  ace T SubtractSaturate(T b) const { return neon::subtract_saturate(vec_, b); }

  ace T SubtractAbs(T b) const { return neon::subtract_abs(vec_, b); }

  ace T SubtractAbsAdd(T b, T c) const { return neon::subtract_abs_add(vec_, b, c); }

  ace T Divide(T b) const requires std::floating_point<base_type> {
#ifdef __aarch64__
    return neon::divide(vec_, b);
#else
    return this->map2(b, [](base_type lane1, base_type lane2) {
        return lane1 / lane2;
    });
#endif
    }

  ace T Max(T b) const { return neon::max(vec_, b); }

  ace T Min(T b) const { return neon::min(vec_, b); }

  ace T AddPairwise(T b) const { return neon::add_pairwise(vec_, b); }

  ace T MaxPairwise(T b) const { return neon::max_pairwise(vec_, b); }

  ace T MinPairwise(T b) const { return neon::min_pairwise(vec_, b); }

  ace Common<result_type> Equal(T b) const { return neon::equal(vec_, b); }

  ace Common<result_type> GreaterThanOrEqual(T b) const { return neon::greater_than_or_equal(vec_, b); }

  ace Common<result_type> LessThanOrEqual(T b) const { return neon::less_than_or_equal(vec_, b); }

  ace Common<result_type> GreaterThan(T b) const { return neon::greater_than(vec_, b); }

  ace Common<result_type> LessThan(T b) const { return neon::less_than(vec_, b); }

  ace T AndTestNonzero(T b) const { return neon::and_test_nonzero(vec_, b); }

  ace T ShiftLeft(Common<typename neon::make_signed<vector_type>::type> b) const { return neon::shift_left(vec_, b); }

  ace T ShiftLeftSaturate(Common<typename neon::make_signed<vector_type>::type> b) const {
    return neon::shift_left_saturate(vec_, b);
  }

  template <int n>
  ace T ShiftLeftSaturate() const {
    return neon::shift_left_saturate<n>(vec_);
  }

  ace T ShiftLeftRound(T b) const { return neon::shift_left_round(vec_, b); }

  ace T ShiftLeftRoundSaturate(T b) const { return neon::shift_left_round_saturate(vec_, b); }

  template <int n>
  ace uint16x8_t ShiftLeftLong() const {
    return neon::shift_left_long<n>(vec_);
  }

  template <int n>
  ace T ShiftLeftInsert(T b) const {
    return neon::shift_left_insert<n>(vec_, b);
  }

  template <int n>
  ace T ShiftRight() const {
    return neon::shift_right<n>(vec_);
  }

  template <int n>
  ace T ShiftRightRound() const {
    return neon::shift_right_round<n>(vec_);
  }

  template <int n>
  ace T ShiftRightAccumulate(T b) const {
    return neon::shift_right_accumulate<n>(vec_, b);
  }

  template <int n>
  ace T ShiftRightAccumulateRound(T b) const {
    return neon::shift_right_accumulate_round<n>(vec_, b);
  }

  template <int n>
  ace T ShiftRightInsert(T b) const {
    return neon::shift_right_insert<n>(vec_, b);
  }

  ace static T Load(base_type const* ptr) { return neon::load1<vector_type>(ptr); }
  ace static T Load2(base_type const* ptr) { return neon::load2<vector_type>(ptr); }
  ace static T Load3(base_type const* ptr) { return neon::load3<vector_type>(ptr); }
  ace static T Load4(base_type const* ptr) { return neon::load4<vector_type>(ptr); }

  ace void Store(base_type* ptr) { neon::store1(ptr, vec_); }
  ace void Store2(base_type* ptr) { neon::store2(ptr, vec_); }
  ace void Store3(base_type* ptr) { neon::store3(ptr, vec_); }
  ace void Store4(base_type* ptr) { neon::store4(ptr, vec_); }

  template <int lane>
  ace void StoreLane(base_type* ptr) {
    neon::store1<lane>(ptr, vec_);
  }

  template <int lane>
  ace void StoreLane2(base_type* ptr) {
    neon::store2<lane>(ptr, vec_);
  }

  template <int lane>
  ace void StoreLane3(base_type* ptr) {
    neon::store3<lane>(ptr, vec_);
  }

  template <int lane>
  ace void StoreLane4(base_type* ptr) {
    neon::store4<lane>(ptr, vec_);
  }

  ace static T LoadCopy(base_type b) { return neon::duplicate_element<vector_type>(b); }
  ace static T Move(base_type b) { return neon::move<vector_type>(b); }

  ace T NotBitwise() const { return neon::not_bitwise(vec_); }

  ace T AndBitwise(T b) const { return neon::and_bitwise(vec_, b); }

  ace T OrBitwise(T b) const { return neon::or_bitwise(vec_, b); }

  ace T XorBitwise(T b) const { return neon::xor_bitwise(vec_, b); }

  ace T OrNotBitwise(T b) const { return neon::or_not_bitwise(vec_, b); }

  ace typename neon::make_signed<vector_type>::type CountLeadingSignBits() const {
    return neon::count_leading_sign_bits(vec_);
  }

  ace T CountLeadingZeroBits() const { return neon::count_leading_zero_bits(vec_); }

  ace T CountActiveBits() const { return neon::count_active_bits(vec_); }

  ace T ClearBitwise(T b) const { return neon::clear_bitwise(vec_, b); }

  ace T SelectBitwise(T b, T c) const { return neon::select_bitwise(vec_, b, b); }

  template <int lane>
  ace T DuplicateElement() const {
    return neon::duplicate_element(vec_, lane);
  }

  template <int lane>
  ace uint8x16_t DuplicateElement() const {
    return neon::duplicate_element(vec_, lane);
  }

  ace uint8x16_t Combine(T high) const { return neon::combine(vec_, high); }

  template <int lane>
  ace uint8_t Get() const {
    return neon::get(vec_, lane);
  }

  template <int n>
  ace T Extract(T b) const {
    return neon::extract(vec_, b, n);
  }

  ace T Reverse64bit() const { return neon::reverse_64bit(vec_); }

  ace T Reverse32bit() const { return neon::reverse_32bit(vec_); }

  ace T Reverse16bit() const { return neon::reverse_16bit(vec_); }

  ace uint8x8x2_t Zip(T b) const { return neon::zip(vec_, b); }

  uint8x8x2_t Unzip(T b) { return neon::unzip(vec_, b); }

  ace uint8x8x2_t Transpose(T b) const { return neon::transpose(vec_, b); }

  ace static int size() { return lanes; }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<base_type(base_type)>>
  ace T map(FuncType body) const {
    T out;
    for (int i = 0; i < lanes; ++i) {
      out[i] = body(vec_[i]);
    }
    return out;
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<base_type(base_type, base_type)>>
  ace T map2(T other, FuncType body) const {
    T out;
    for (int i = 0; i < lanes; ++i) {
      out[i] = body(vec_[i], other.vec_[i]);
    }
    return out;
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void(base_type&)>>
  ace void each(FuncType body) {
    for (int i = 0; i < lanes; ++i) {
      body(vec_[i]);
    }
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void(base_type&, int)>>
  ace void each_lane(FuncType body) {
    for (int i = 0; i < lanes; ++i) {
      body(vec_[i], i);
    }
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void()>>
  ace void if_(FuncType true_branch) {
    for (int i = 0; i < lanes; ++i) {
      if (vec_[i] != 0) {
        true_branch();
      }
    }
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void()>>
  ace void if_else(FuncType true_branch, FuncType false_branch) {
    for (int i = 0; i < lanes; ++i) {
      if (vec_[i] != 0) {
        true_branch();
      } else {
        false_branch();
      }
    }
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void(int)>>
  ace void if_lane(FuncType true_branch) {
    for (int i = 0; i < lanes; ++i) {
      if (vec_[i] != 0) {
        true_branch(i);
      }
    }
  }

  template <typename FuncType1, typename FuncType2>
    requires std::convertible_to<FuncType1, std::function<void(int)>> &&
             std::convertible_to<FuncType2, std::function<void(int)>>
  ace void if_else_lane(FuncType1 true_branch, FuncType2 false_branch) {
    for (int i = 0; i < lanes; ++i) {
      if (vec_[i] != 0) {
        true_branch(i);
      } else {
        false_branch(i);
      }
    }
  }

  ace bool any() {
    for (int i = 0; i < lanes; ++i) {
      if (vec_[i] != 0) {
        return true;
      }
    }
    return false;
  }

  ace bool all() {
    for (int i = 0; i < lanes; ++i) {
      if (vec_[i] == 0) {
        return false;
      }
    }
    return true;
  }

 protected:
  vector_type vec_;
};

template <typename vector_type>
class Lane {
  using base_type = neon::NonVec<vector_type>::type;

 public:
  using T = Lane<vector_type>;

  ace Lane(vector_type vec, const int lane) : vec_(vec), lane_(lane){};

  ace operator neon::NonVec<vector_type>::type() { return neon::get(vec_, lane_); }

  ace Common<vector_type> operator=(base_type b) { return neon::set(vec_, lane_, b); }
  ace Common<vector_type> operator=(T t) { return neon::set(vec_, lane_, neon::get(t.vec_, t.lane_)); }

  ace Common<vector_type> operator+=(base_type b) { return neon::set(vec_, lane_, neon::get(vec_, lane_) + b); }
  ace Common<vector_type> operator-=(base_type b) { return neon::set(vec_, lane_, neon::get(vec_, lane_) - b); }
  ace Common<vector_type> operator*=(base_type b) { return neon::set(vec_, lane_, neon::get(vec_, lane_) * b); }
  ace Common<vector_type> operator/=(base_type b) { return neon::set(vec_, lane_, neon::get(vec_, lane_) / b); }

 private:
  vector_type vec_;
  const int lane_;
};

}  // namespace impl

template <typename base>
class Neon128;

template <typename base_type>
class Neon64 : public impl::Common<typename impl::Vec64<base_type>::type> {
  using T = impl::Common<typename impl::Vec64<base_type>::type>;
  using next_larger_type = impl::NextLarger<base_type>::type;

 public:
  using vector_type = impl::Vec64<base_type>::type;

  static_assert(neon::is_doubleword_v<vector_type>);

  static constexpr size_t bytes = 8;
  static constexpr size_t lanes = bytes / sizeof(base_type);

  constexpr Neon64() : T(){};
  constexpr Neon64(vector_type vector) : T(vector){};
  constexpr Neon64(base_type base) : T(base){};
  constexpr Neon64(base_type const* base_ptr) : T(base_ptr){};
  constexpr Neon64(T&& in) : T(in){};
  constexpr Neon64(std::initializer_list<base_type> value_list) : T(value_list) {};

  ace Neon128<next_larger_type> AddLong(T b) const { return neon::add_long(this->vec_, b); }
  ace Neon128<next_larger_type> MultiplyLong(T b) const { return neon::multiply_long(this->vec_, b); }
  ace Neon128<next_larger_type> SubtractLong(T b) const { return neon::subtract_long(this->vec_, b); }
  ace Neon128<next_larger_type> MoveLong() const { return neon::move_long(this->vec_); }

  ace Neon128<next_larger_type> SubtractAbsLong(T b) const { return neon::subtract_abs_long(this->vec_, b); }
  ace Neon128<next_larger_type> AddPairwiseLong() const { return neon::add_pairwise_long(this->vec_); }

  ace T TableLookup1(T idx) const { return neon::table_lookup1(this->vec_, idx); }
  ace T TableLookupExtension1(T b, T idx) const { return neon::table_lookup_extension1(this->vec_, b, idx); }
  ace T TableLookupExtension2(uint8x8x2_t b, T idx) const { return neon::table_lookup_extension2(this->vec_, b, idx); }
  ace T TableLookupExtension3(uint8x8x3_t b, T idx) const { return neon::table_lookup_extension3(this->vec_, b, idx); }
  ace T TableLookupExtension4(uint8x8x4_t b, T idx) const { return neon::table_lookup_extension4(this->vec_, b, idx); }
};

template <typename base_type>
class Neon128 : public impl::Common<typename impl::Vec128<base_type>::type> {
  using T = impl::Common<typename impl::Vec128<base_type>::type>;

 public:
  using vector_type = impl::Vec128<base_type>::type;
  constexpr Neon128() : T(){};
  constexpr Neon128(vector_type vector) : T(vector){};
  constexpr Neon128(base_type base) : T(base){};
  constexpr Neon128(base_type const* base_ptr) : T(base_ptr){};
  constexpr Neon128(T&& in) : T(in){};
  constexpr Neon128(std::initializer_list<base_type> value_list) : T(value_list) {};

  static_assert(neon::is_quadword_v<vector_type>);

  static constexpr size_t bytes = 16;
  static constexpr size_t lanes = bytes / sizeof(base_type);

  ace Neon64<vector_type> GetHigh() { return vget_high_u8(this->vec_); }
  ace Neon64<vector_type> GetLow() { return vget_low_u8(this->vec_); }
};

template <typename NeonType, neon::is_vector_type V>
ace NeonType reinterpret(impl::Common<V> in) {
  static_assert(!std::is_same_v<typename NeonType::vector_type, V>);
  return NeonType{neon::reinterpret<typename NeonType::vector_type>(in.vec())};
}

template <typename NeonType, neon::is_vector_type V>
ace NeonType reinterpret(V in) {
  static_assert(!std::is_same_v<typename NeonType::vector_type, V>);
  return NeonType{neon::reinterpret<typename NeonType::vector_type>(in)};
}

template <neon::is_vector_type V>
ace impl::Common<V> operator+(typename neon::NonVec<V>::type a, impl::Common<V> b) {
  return b.Add(a);
}

template <neon::is_vector_type V>
ace impl::Common<V> operator-(typename neon::NonVec<V>::type a, impl::Common<V> b) {
  return impl::Common<V>{a}.Subtract(b);
}

template <neon::is_vector_type V>
ace impl::Common<V> operator*(typename neon::NonVec<V>::type a, impl::Common<V> b) {
  return b.Multiply(a);
}

template <neon::is_vector_type V>
ace impl::Common<V> operator/(typename neon::NonVec<V>::type a, impl::Common<V> b) {
  return impl::Common<V>{a}.Divide(b);
}

template <neon::is_vector_type V>
ace impl::Common<V> operator+(impl::Common<V> a, typename neon::NonVec<V>::type b) {
  return a.Add(b);
}

template <neon::is_vector_type V>
ace impl::Common<V> operator-(impl::Common<V> a, typename neon::NonVec<V>::type b) {
  return a.Subtract(b);
}

template <neon::is_vector_type V>
ace impl::Common<V> operator*(impl::Common<V> a, typename neon::NonVec<V>::type b) {
  return a.Multiply(b);
}

template <neon::is_vector_type V>
ace impl::Common<V> operator/(impl::Common<V> a, typename neon::NonVec<V>::type b) {
  return a.Divide(b);
}

template <neon::is_vector_type V>
ace impl::Common<V> operator+(V a, impl::Common<V> b) {
  return impl::Common<V>{a}.Add(b);
}

template <neon::is_vector_type V>
ace impl::Common<V> operator-(V a, impl::Common<V> b) {
  return impl::Common<V>{a}.Subtract(b);
}

template <neon::is_vector_type V>
ace impl::Common<V> operator*(V a, impl::Common<V> b) {
  return impl::Common<V>{a}.Multiply(a);
}

template <neon::is_vector_type V>
ace impl::Common<V> operator/(V a, impl::Common<V> b) {
  return impl::Common<V>{a}.Divide(b);
}

}  // namespace argon
#undef ace
