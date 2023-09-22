#pragma once
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#include "neon.hpp"

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
template <> struct NextLarger<int8x8_t> {using type = int16x4_t; };
template <> struct NextLarger<uint8x8_t> {using type = uint16x4_t; };
template <> struct NextLarger<int16x4_t> {using type = int32x2_t; };
template <> struct NextLarger<uint16x4_t> {using type = uint32x2_t; };
template <> struct NextLarger<int32x2_t> {using type = int64x1_t; };
template <> struct NextLarger<uint32x2_t> {using type = uint64x1_t; };

template <> struct NextLarger<int8x16_t> {using type = int16x8_t; };
template <> struct NextLarger<uint8x16_t> {using type = uint16x8_t; };
template <> struct NextLarger<int16x8_t> {using type = int32x4_t; };
template <> struct NextLarger<uint16x8_t> {using type = uint32x4_t; };
template <> struct NextLarger<int32x4_t> {using type = int64x2_t; };
template <> struct NextLarger<uint32x4_t> {using type = uint64x2_t; };

template <typename T> struct NonVec;
template <> struct NonVec<int8x8_t> {using type = int8_t; };
template <> struct NonVec<uint8x8_t> {using type = uint8_t; };
template <> struct NonVec<int16x4_t> {using type = int16_t; };
template <> struct NonVec<uint16x4_t> {using type = uint16_t; };
template <> struct NonVec<int32x2_t> {using type = int32_t; };
template <> struct NonVec<uint32x2_t> {using type = uint32_t; };
template <> struct NonVec<int64x1_t> {using type = int64_t; };
template <> struct NonVec<uint64x1_t> {using type = uint64_t; };

template <> struct NonVec<int8x16_t> {using type = int8_t; };
template <> struct NonVec<uint8x16_t> {using type = uint8_t; };
template <> struct NonVec<int16x8_t> {using type = int16_t; };
template <> struct NonVec<uint16x8_t> {using type = uint16_t; };
template <> struct NonVec<int32x4_t> {using type = int32_t; };
template <> struct NonVec<uint32x4_t> {using type = uint32_t; };
template <> struct NonVec<int64x2_t> {using type = int64_t; };
template <> struct NonVec<uint64x2_t> {using type = uint64_t; };
// clang-format on

template <typename T>
using is_doubleword_v = std::is_same_v<T, uint8x8_t> || std::is_same_v<T, uint16x4_t> ||
                        std::is_same_v<T, uint32x2_t> || std::is_same_v<T, uint64x1_t>;

template <typename T>
using is_quadword_v = std::is_same_v<T, uint8x16_t> || std::is_same_v<T, uint16x8_t> || std::is_same_v<T, uint32x4_t> ||
                      std::is_same_v<T, uint64x2_t>;

template <typename T>
concept doubleword = is_doubleword_v<T>;

template <typename T>
concept quadword = is_quadword_v<T>;

template <typename T>
concept vector_type = doubleword<T> || quadword<T>;

template <typename vector_type, std::enable_if<is_doubleword_v<vector_type>::value, int> = 0>
class Common {
  using next_larger_type = typename NextLarger<vector_type>::type;

 public:
  using T = Common<vector_type>;

  ace static T Load(auto const* elem) { return neon::load1<vector_type>(elem); }
  ace static T Load_2(auto const* elem) { return neon::load2<vector_type>(elem); }
  ace static T Load_3(auto const* elem) { return neon::load3<vector_type>(elem); }
  ace static T Load_4(auto const* elem) { return neon::load4<vector_type>(elem); }

  constexpr Common(vector_type vector) : vec_(vector){};

  ace T operator+(T b) const { return Add(b); }
  ace T operator-(T b) const { return Subtract(b); }
  ace T operator*(T b) const { return Multiply(b); }
  ace T operator/(T b) const { return Divide(b); }

  ace T operator+=(T b) {
    vec_ = Add(b);
    return vec_;
  }

  template <std::integral U>
  ace T operator+(const U b) const {
    return Add(b);
  }

  template <std::integral U>
  ace T operator+=(const U b) {
    return vec_ = Add(b);
  }

  template <std::integral U>
  ace T Add(const U b) const {
    T rhs = LoadCopy(b);
    return Add(rhs);
  }

  ace T operator==(T b) const { return Equal(b); }
  ace T operator<(T b) const { return LessThan(b); }
  ace T operator>(T b) const { return GreaterThan(b); }
  ace T operator<=(T b) const { return LessThanOrEqual(b); }
  ace T operator>=(T b) const { return GreaterThanOrEqual(b); }

  ace T operator++() const { return Add(1); }
  ace T operator--() const { return Subtract(1); }

  ace T operator&(T b) const { return AndBitwise(b); }
  ace T operator|(T b) const { return OrBitwise(b); }
  ace T operator^(T b) const { return XorBitwise(b); }
  ace T operator~() const { return NotBitwise(); }

  ace auto operator[](const int i) const { return Get(i); }

  ace T operator>>(const int i) const { return ShiftRight(i); }
  ace T operator<<(const int i) const { return ShiftLeft(i); }

  ace operator vector_type() const { return vec_; }

  ace vector_type vec() const { return vec_; }

  ace T LoadCopy(typename NonVec<vector_type>::type v) const { return neon::duplicate_element<vector_type>(v); }

  ace auto Get(const int i) const { return neon::get<vector_type>(vec_, i); }

  ace T ShiftRight(const int i) const { return neon::shift_right(vec_, i); }

  ace T ShiftLeft(const int i) const { return neon::shift_left(vec_, i); }

  ace T Add(T b) const { return neon::add(vec_, b); }

  ace Common<typename Vec128<next_larger_type>::type> AddLong(T b) const { return neon::add_long(vec_, b); }

  ace T AddHalve(T b) const { return neon::add_halve(vec_, b); }

  ace T AddHalveRound(T b) const { return neon::add_halve_round(vec_, b); }

  ace T AddSaturate(T b) const { return neon::add_saturate(vec_, b); }

  ace T Multiply(T b) const { return neon::multiply(vec_, b); }

  ace T MultiplyAdd(T b, T c) const { return neon::multiply_add(vec_, b, b); }

  ace T MultiplySubtract(T b, T c) const { return neon::multiply_subtract(vec_, b, b); }

  ace Common<typename Vec128<next_larger_type>::type> MultiplyLong(T b) const { return neon::multiply_long(vec_, b); }

  ace T Subtract(T b) const { return neon::subtract(vec_, b); }

  ace Common<typename Vec128<next_larger_type>::type> SubtractLong(T b) const { return neon::subtract_long(vec_, b); }

  ace T SubtractHigh(T b) const { return neon::subtract_high(vec_, b); }

  ace T SubtractSaturate(T b) const { return neon::subtract_saturate(vec_, b); }

  ace T SubtractAbs(T b) const { return neon::subtract_abs(vec_, b); }

  ace Common<typename Vec128<next_larger_type>::type> SubtractAbsLong(T b) const {
    return neon::subtract_abs_long(vec_, b);
  }

  ace T SubtractAbsAdd(T b, T c) const { return neon::subtract_abs_add(vec_, b, c); }

  ace T Max(T b) const { return neon::max(vec_, b); }

  ace T Min(T b) const { return neon::min(vec_, b); }

  ace T AddPairwise(T b) const { return neon::add_pairwise(vec_, b); }

  ace Common<next_larger_type> AddPairwiseLong() const { return neon::add_pairwise_long(vec_); }

  ace T MaxPairwise(T b) const { return neon::max_pairwise(vec_, b); }

  ace T MinPairwise(T b) const { return neon::min_pairwise(vec_, b); }

  ace T Equal(T b) const { return neon::equal(vec_, b); }

  ace T GreaterThanOrEqual(T b) const { return neon::greater_than_or_equal(vec_, b); }

  ace T LessThanOrEqual(T b) const { return neon::less_than_or_equal(vec_, b); }

  ace T GreaterThan(T b) const { return neon::greater_than(vec_, b); }

  ace T LessThan(T b) const { return neon::less_than(vec_, b); }

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

  ace uint16x8_t MoveLong() const { return neon::move_long(vec_); }

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

 protected:
  vector_type vec_;
};

template <typename vector_type, std::enable_if<is_quadword_v<vector_type>::value, int> = 0>
class Common {
 public:
  using T = Common<vector_type>;

  ace static T Load(auto const* elem) { return neon::load1<vector_type>(elem); }
  ace static T Load_2(auto const* elem) { return neon::load2<vector_type>(elem); }
  ace static T Load_3(auto const* elem) { return neon::load3<vector_type>(elem); }
  ace static T Load_4(auto const* elem) { return neon::load4<vector_type>(elem); }

  constexpr Common(vector_type vector) : vec_(vector){};

  ace T operator+(T b) const { return Add(b); }
  ace T operator-(T b) const { return Subtract(b); }
  ace T operator*(T b) const { return Multiply(b); }
  ace T operator/(T b) const { return Divide(b); }

  ace T operator+=(T b) {
    vec_ = Add(b);
    return vec_;
  }

  template <std::integral U>
  ace T operator+(const U b) const {
    return Add(b);
  }

  template <std::integral U>
  ace T operator+=(const U b) {
    return vec_ = Add(b);
  }

  template <std::integral U>
  ace T Add(const U b) const {
    T rhs = LoadCopy(b);
    return Add(rhs);
  }

  ace T operator==(T b) const { return Equal(b); }
  ace T operator<(T b) const { return LessThan(b); }
  ace T operator>(T b) const { return GreaterThan(b); }
  ace T operator<=(T b) const { return LessThanOrEqual(b); }
  ace T operator>=(T b) const { return GreaterThanOrEqual(b); }

  ace T operator++() const { return Add(1); }
  ace T operator--() const { return Subtract(1); }

  ace T operator&(T b) const { return AndBitwise(b); }
  ace T operator|(T b) const { return OrBitwise(b); }
  ace T operator^(T b) const { return XorBitwise(b); }
  ace T operator~() const { return NotBitwise(); }

  ace auto operator[](const int i) const { return Get(i); }

  ace T operator>>(const int i) const { return ShiftRight(i); }
  ace T operator<<(const int i) const { return ShiftLeft(i); }

  ace operator vector_type() const { return vec_; }

  ace vector_type vec() const { return vec_; }

  ace T LoadCopy(typename NonVec<vector_type>::type v) const { return neon::duplicate_element<vector_type>(v); }

  ace auto Get(const int i) const { return neon::get<vector_type>(vec_, i); }

  ace T ShiftRight(const int i) const { return neon::shift_right(vec_, i); }

  ace T ShiftLeft(const int i) const { return neon::shift_left(vec_, i); }

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

  ace T Max(T b) const { return neon::max(vec_, b); }

  ace T Min(T b) const { return neon::min(vec_, b); }

  ace T AddPairwise(T b) const { return neon::add_pairwise(vec_, b); }

  ace T MaxPairwise(T b) const { return neon::max_pairwise(vec_, b); }

  ace T MinPairwise(T b) const { return neon::min_pairwise(vec_, b); }

  ace T Equal(T b) const { return neon::equal(vec_, b); }

  ace T GreaterThanOrEqual(T b) const { return neon::greater_than_or_equal(vec_, b); }

  ace T LessThanOrEqual(T b) const { return neon::less_than_or_equal(vec_, b); }

  ace T GreaterThan(T b) const { return neon::greater_than(vec_, b); }

  ace T LessThan(T b) const { return neon::less_than(vec_, b); }

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

  ace uint16x8_t MoveLong() const { return neon::move_long(vec_); }

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

 protected:
  vector_type vec_;
};

}  // namespace impl

template <typename base>
class Neon64 : public impl::Common<typename impl::Vec64<base>::type> {
  using T = impl::Common<typename impl::Vec64<base>::type>;

 public:
  using vector_type = impl::Vec64<base>::type;
  using T::T;

  static constexpr size_t bytes = 8;
  static constexpr size_t lanes = bytes / sizeof(base);

  constexpr Neon64(T&& in) : T(in){};

  ace T TableLookup1(T idx) const { return neon::table_lookup1(this->vec_, idx); }
  ace T TableLookupExtension1(T b, T idx) const { return neon::table_lookup_extension1(this->vec_, b, idx); }
  ace T TableLookupExtension2(uint8x8x2_t b, T idx) const { return neon::table_lookup_extension2(this->vec_, b, idx); }
  ace T TableLookupExtension3(uint8x8x3_t b, T idx) const { return neon::table_lookup_extension3(this->vec_, b, idx); }
  ace T TableLookupExtension4(uint8x8x4_t b, T idx) const { return neon::table_lookup_extension4(this->vec_, b, idx); }
};

template <typename base>
class Neon128 : public impl::Common<typename impl::Vec128<base>::type> {
  using T = impl::Common<typename impl::Vec128<base>::type>;

 public:
  using vector_type = impl::Vec128<base>::type;
  using T::T;

  static constexpr size_t bytes = 16;
  static constexpr size_t lanes = bytes / sizeof(base);

  constexpr Neon128(T&& in) : T(in){};

  ace Neon64<vector_type> GetHigh() { return vget_high_u8(this->vec_); }
  ace Neon64<vector_type> GetLow() { return vget_low_u8(this->vec_); }

  ace static T Load(base elem) { return neon::load1(elem); }
  ace static T Load_2(base elem) { return neon::load2(elem); }
  ace static T Load_3(base elem) { return neon::load3(elem); }
  ace static T Load_4(base elem) { return neon::load4(elem); }
};

template <typename N, impl::vector_type V>
N reinterpret(impl::Common<V> in) {
  return {neon::reinterpret<typename N::vector_type>(in.vec())};
}

template <typename N, impl::vector_type V>
N reinterpret(V in) {
  static_assert(!std::is_same_v<typename N::vector_type, V>);
  return N{neon::reinterpret<typename N::vector_type>(in)};
}

using uint8 = Neon64<uint8_t>;
using uint8_q = Neon128<uint8_t>;
using uint16 = Neon64<uint16_t>;
using uint16_q = Neon128<uint16_t>;
using uint32 = Neon64<uint32_t>;
using uint32_q = Neon128<uint32_t>;
using uint64 = Neon64<uint64_t>;
using uint64_q = Neon128<uint64_t>;

using int8 = Neon64<int8_t>;
using int8_q = Neon128<int8_t>;
using int16 = Neon64<int16_t>;
using int16_q = Neon128<int16_t>;
using int32 = Neon64<int32_t>;
using int32_q = Neon128<int32_t>;
using int64 = Neon64<int64_t>;
using int64_q = Neon128<int64_t>;

using float32 = Neon64<float>;
using float32_q = Neon128<float>;

}  // namespace argon
#undef ace