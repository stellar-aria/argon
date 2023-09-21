#pragma once
#include <cstddef>
#include <concepts>
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

template <typename vector_type>
class Common {
  // using next_larger_type = typename NextLarger<vector_type>::type;

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

  ace auto Get(const int i) const {
		return neon::get<vector_type>(vec_, i);
  }

  ace T ShiftRight(const int i) const {
    switch (i) {
      case 1:
        return ShiftRight<1>(vec_);
      case 2:
        return ShiftRight<2>(vec_);
      case 3:
        return ShiftRight<3>(vec_);
      case 4:
        return ShiftRight<4>(vec_);
      case 5:
        return ShiftRight<5>(vec_);
      case 6:
        return ShiftRight<6>(vec_);
      case 7:
        return ShiftRight<7>(vec_);
      case 8:
        return ShiftRight<8>(vec_);
      case 9:
        return ShiftRight<9>(vec_);
      case 10:
        return ShiftRight<10>(vec_);
      case 11:
        return ShiftRight<11>(vec_);
      case 12:
        return ShiftRight<12>(vec_);
      case 13:
        return ShiftRight<13>(vec_);
      case 14:
        return ShiftRight<14>(vec_);
      case 15:
        return ShiftRight<15>(vec_);
      case 16:
        return ShiftRight<16>(vec_);
      case 17:
        return ShiftRight<17>(vec_);
      case 18:
        return ShiftRight<18>(vec_);
      case 19:
        return ShiftRight<19>(vec_);
      case 20:
        return ShiftRight<20>(vec_);
      case 21:
        return ShiftRight<21>(vec_);
      case 22:
        return ShiftRight<22>(vec_);
      case 23:
        return ShiftRight<23>(vec_);
      case 24:
        return ShiftRight<24>(vec_);
      case 25:
        return ShiftRight<25>(vec_);
      case 26:
        return ShiftRight<26>(vec_);
      case 27:
        return ShiftRight<27>(vec_);
      case 28:
        return ShiftRight<28>(vec_);
      case 29:
        return ShiftRight<29>(vec_);
      case 30:
        return ShiftRight<30>(vec_);
      case 31:
        return ShiftRight<31>(vec_);
      case 32:
        return ShiftRight<32>(vec_);
      case 33:
        return ShiftRight<33>(vec_);
      case 34:
        return ShiftRight<34>(vec_);
      case 35:
        return ShiftRight<35>(vec_);
      case 36:
        return ShiftRight<36>(vec_);
      case 37:
        return ShiftRight<37>(vec_);
      case 38:
        return ShiftRight<38>(vec_);
      case 39:
        return ShiftRight<39>(vec_);
      case 40:
        return ShiftRight<40>(vec_);
      case 41:
        return ShiftRight<41>(vec_);
      case 42:
        return ShiftRight<42>(vec_);
      case 43:
        return ShiftRight<43>(vec_);
      case 44:
        return ShiftRight<44>(vec_);
      case 45:
        return ShiftRight<45>(vec_);
      case 46:
        return ShiftRight<46>(vec_);
      case 47:
        return ShiftRight<47>(vec_);
      case 48:
        return ShiftRight<48>(vec_);
      case 49:
        return ShiftRight<49>(vec_);
      case 50:
        return ShiftRight<50>(vec_);
      case 51:
        return ShiftRight<51>(vec_);
      case 52:
        return ShiftRight<52>(vec_);
      case 53:
        return ShiftRight<53>(vec_);
      case 54:
        return ShiftRight<54>(vec_);
      case 55:
        return ShiftRight<55>(vec_);
      case 56:
        return ShiftRight<56>(vec_);
      case 57:
        return ShiftRight<57>(vec_);
      case 58:
        return ShiftRight<58>(vec_);
      case 59:
        return ShiftRight<59>(vec_);
      case 60:
        return ShiftRight<60>(vec_);
      case 61:
        return ShiftRight<61>(vec_);
      case 62:
        return ShiftRight<62>(vec_);
      case 63:
        return ShiftRight<63>(vec_);
      default:
        __builtin_unreachable();
    }
  }

  ace T ShiftLeft(const int i) const {
    switch (i) {
      case 1:
        return ShiftLeft<1>(vec_);
      case 2:
        return ShiftLeft<2>(vec_);
      case 3:
        return ShiftLeft<3>(vec_);
      case 4:
        return ShiftLeft<4>(vec_);
      case 5:
        return ShiftLeft<5>(vec_);
      case 6:
        return ShiftLeft<6>(vec_);
      case 7:
        return ShiftLeft<7>(vec_);
      case 8:
        return ShiftLeft<8>(vec_);
      case 9:
        return ShiftLeft<9>(vec_);
      case 10:
        return ShiftLeft<10>(vec_);
      case 11:
        return ShiftLeft<11>(vec_);
      case 12:
        return ShiftLeft<12>(vec_);
      case 13:
        return ShiftLeft<13>(vec_);
      case 14:
        return ShiftLeft<14>(vec_);
      case 15:
        return ShiftLeft<15>(vec_);
      case 16:
        return ShiftLeft<16>(vec_);
      case 17:
        return ShiftLeft<17>(vec_);
      case 18:
        return ShiftLeft<18>(vec_);
      case 19:
        return ShiftLeft<19>(vec_);
      case 20:
        return ShiftLeft<20>(vec_);
      case 21:
        return ShiftLeft<21>(vec_);
      case 22:
        return ShiftLeft<22>(vec_);
      case 23:
        return ShiftLeft<23>(vec_);
      case 24:
        return ShiftLeft<24>(vec_);
      case 25:
        return ShiftLeft<25>(vec_);
      case 26:
        return ShiftLeft<26>(vec_);
      case 27:
        return ShiftLeft<27>(vec_);
      case 28:
        return ShiftLeft<28>(vec_);
      case 29:
        return ShiftLeft<29>(vec_);
      case 30:
        return ShiftLeft<30>(vec_);
      case 31:
        return ShiftLeft<31>(vec_);
      case 32:
        return ShiftLeft<32>(vec_);
      case 33:
        return ShiftLeft<33>(vec_);
      case 34:
        return ShiftLeft<34>(vec_);
      case 35:
        return ShiftLeft<35>(vec_);
      case 36:
        return ShiftLeft<36>(vec_);
      case 37:
        return ShiftLeft<37>(vec_);
      case 38:
        return ShiftLeft<38>(vec_);
      case 39:
        return ShiftLeft<39>(vec_);
      case 40:
        return ShiftLeft<40>(vec_);
      case 41:
        return ShiftLeft<41>(vec_);
      case 42:
        return ShiftLeft<42>(vec_);
      case 43:
        return ShiftLeft<43>(vec_);
      case 44:
        return ShiftLeft<44>(vec_);
      case 45:
        return ShiftLeft<45>(vec_);
      case 46:
        return ShiftLeft<46>(vec_);
      case 47:
        return ShiftLeft<47>(vec_);
      case 48:
        return ShiftLeft<48>(vec_);
      case 49:
        return ShiftLeft<49>(vec_);
      case 50:
        return ShiftLeft<50>(vec_);
      case 51:
        return ShiftLeft<51>(vec_);
      case 52:
        return ShiftLeft<52>(vec_);
      case 53:
        return ShiftLeft<53>(vec_);
      case 54:
        return ShiftLeft<54>(vec_);
      case 55:
        return ShiftLeft<55>(vec_);
      case 56:
        return ShiftLeft<56>(vec_);
      case 57:
        return ShiftLeft<57>(vec_);
      case 58:
        return ShiftLeft<58>(vec_);
      case 59:
        return ShiftLeft<59>(vec_);
      case 60:
        return ShiftLeft<60>(vec_);
      case 61:
        return ShiftLeft<61>(vec_);
      case 62:
        return ShiftLeft<62>(vec_);
      case 63:
        return ShiftLeft<63>(vec_);
      default:
        __builtin_unreachable();
    }
  }

  ace T Add(T b) const { return neon::add(vec_, b); }

  // ace Common<typename Vec128<next_larger_type>::type> AddLong(T b) const { return neon::add_long(vec_, b); }

  ace T AddHalve(T b) const { return neon::add_halve(vec_, b); }

  ace T AddHalveRound(T b) const { return neon::add_halve_round(vec_, b); }

  ace T AddSaturate(T b) const { return neon::add_saturate(vec_, b); }

  ace T Multiply(T b) const { return neon::multiply(vec_, b); }

  ace T MultiplyAdd(T b, T c) const { return neon::multiply_add(vec_, b, b); }

  ace T MultiplySubtract(T b, T c) const { return neon::multiply_subtract(vec_, b, b); }

  // ace Common<typename Vec128<next_larger_type>::type> MultiplyLong(T b) const { return neon::multiply_long(vec_, b);
  // }

  ace T Subtract(T b) const { return neon::subtract(vec_, b); }

  // ace Common<typename Vec128<next_larger_type>::type> SubtractLong(T b) const { return neon::subtract_long(vec_, b);
  // }

  ace T SubtractHigh(T b) const { return neon::subtract_high(vec_, b); }

  ace T SubtractSaturate(T b) const { return neon::subtract_saturate(vec_, b); }

  ace T SubtractAbs(T b) const { return neon::subtract_abs(vec_, b); }

  // ace Common<typename Vec128<next_larger_type>::type> SubtractAbsLong(T b) const { return
  // neon::subtract_abs_long(vec_, b); }

  ace T SubtractAbsAdd(T b, T c) const { return neon::subtract_abs_add(vec_, b, c); }

  ace T Max(T b) const { return neon::max(vec_, b); }

  ace T Min(T b) const { return neon::min(vec_, b); }

  ace T AddPairwise(T b) const { return neon::add_pairwise(vec_, b); }

  // ace Common<next_larger_type> AddPairwiseLong() const { return neon::add_pairwise_long(vec_); }

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

template <typename T>
concept doubleword = std::is_same_v<T, uint8x8_t> || std::is_same_v<T, uint16x4_t> || std::is_same_v<T, uint32x2_t> ||
                     std::is_same_v<T, uint64x1_t>;

template <typename T>
concept quadword = std::is_same_v<T, uint8x16_t> || std::is_same_v<T, uint16x8_t> || std::is_same_v<T, uint32x4_t> ||
                   std::is_same_v<T, uint64x2_t>;

template <typename T>
concept vector_type = doubleword<T> || quadword<T>;

template <typename N, vector_type V>
N reinterpret(impl::Common<V> in) {
  return {neon::reinterpret<typename N::vector_type>(in.vec())};
}

template <typename N, vector_type V>
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