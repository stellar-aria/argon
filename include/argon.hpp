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

template <typename T>
constexpr bool has_smaller_v =
    std::is_same_v<T, uint16_t> ||
    std::is_same_v<T, uint32_t> ||
    std::is_same_v<T, uint64_t> ||
    std::is_same_v<T, int16_t> ||
    std::is_same_v<T, int32_t> ||
    std::is_same_v<T, int64_t> ||
    std::is_same_v<T, double>;

template <typename T>
constexpr bool has_larger_v =
    std::is_same_v<T, uint8_t> ||
    std::is_same_v<T, uint16_t> ||
    std::is_same_v<T, uint32_t> ||
    std::is_same_v<T, int8_t> ||
    std::is_same_v<T, int16_t> ||
    std::is_same_v<T, int32_t> ||
    std::is_same_v<T, float>;

template <typename T>
concept has_smaller = has_smaller_v<T>;

template <typename T>
concept has_larger = has_larger_v<T>;

template <typename T> struct NextLarger;
template <> struct NextLarger<int8_t> {using type = int16_t; };
template <> struct NextLarger<uint8_t> {using type = uint16_t; };
template <> struct NextLarger<int16_t> {using type = int32_t; };
template <> struct NextLarger<uint16_t> {using type = uint32_t; };
template <> struct NextLarger<int32_t> {using type = int64_t; };
template <> struct NextLarger<uint32_t> {using type = uint64_t; };
template <> struct NextLarger<float> {using type = double; };

template <typename T> struct NextSmaller;
template <> struct NextSmaller<int16_t> {using type = int8_t; };
template <> struct NextSmaller<uint16_t> {using type = uint8_t; };
template <> struct NextSmaller<int32_t> {using type = int16_t; };
template <> struct NextSmaller<uint32_t> {using type = uint16_t; };
template <> struct NextSmaller<int64_t> {using type = int32_t; };
template <> struct NextSmaller<uint64_t> {using type = uint32_t; };
template <> struct NextSmaller<double> {using type = float; };

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

template <typename T, size_t size> struct MultiVec;
template <> struct MultiVec<int8x8_t, 2> {using type = int8x8x2_t; };
template <> struct MultiVec<uint8x8_t, 2> {using type = uint8x8x2_t; };
template <> struct MultiVec<int16x4_t, 2> {using type = int16x4x2_t; };
template <> struct MultiVec<uint16x4_t, 2> {using type = uint16x4x2_t; };
template <> struct MultiVec<int32x2_t, 2> {using type = int32x2x2_t; };
template <> struct MultiVec<uint32x2_t, 2> {using type = uint32x2x2_t; };
template <> struct MultiVec<int8x16_t, 2> {using type = int8x16x2_t; };
template <> struct MultiVec<uint8x16_t, 2> {using type = uint8x16x2_t; };
template <> struct MultiVec<int16x8_t, 2> {using type = int16x8x2_t; };
template <> struct MultiVec<uint16x8_t, 2> {using type = uint16x8x2_t; };
template <> struct MultiVec<int32x4_t, 2> {using type = int32x4x2_t; };
template <> struct MultiVec<uint32x4_t, 2> {using type = uint32x4x2_t; };
template <> struct MultiVec<int64x1_t, 2> {using type = int64x1x2_t; };
template <> struct MultiVec<uint64x1_t, 2> {using type = uint64x1x2_t; };
template <> struct MultiVec<int64x2_t, 2> {using type = int64x2x2_t; };
template <> struct MultiVec<uint64x2_t, 2> {using type = uint64x2x2_t; };
template <> struct MultiVec<float32x2_t, 2> {using type = float32x2x2_t; };
template <> struct MultiVec<float32x4_t, 2> {using type = float32x4x2_t; };

template <> struct MultiVec<int8x8_t, 3> {using type = int8x8x3_t; };
template <> struct MultiVec<uint8x8_t, 3> {using type = uint8x8x3_t; };
template <> struct MultiVec<int16x4_t, 3> {using type = int16x4x3_t; };
template <> struct MultiVec<uint16x4_t, 3> {using type = uint16x4x3_t; };
template <> struct MultiVec<int32x2_t, 3> {using type = int32x2x3_t; };
template <> struct MultiVec<uint32x2_t, 3> {using type = uint32x2x3_t; };
template <> struct MultiVec<int8x16_t, 3> {using type = int8x16x3_t; };
template <> struct MultiVec<uint8x16_t, 3> {using type = uint8x16x3_t; };
template <> struct MultiVec<int16x8_t, 3> {using type = int16x8x3_t; };
template <> struct MultiVec<uint16x8_t, 3> {using type = uint16x8x3_t; };
template <> struct MultiVec<int32x4_t, 3> {using type = int32x4x3_t; };
template <> struct MultiVec<uint32x4_t, 3> {using type = uint32x4x3_t; };
template <> struct MultiVec<int64x1_t, 3> {using type = int64x1x3_t; };
template <> struct MultiVec<uint64x1_t, 3> {using type = uint64x1x3_t; };
template <> struct MultiVec<int64x2_t, 3> {using type = int64x2x3_t; };
template <> struct MultiVec<uint64x2_t, 3> {using type = uint64x2x3_t; };
template <> struct MultiVec<float32x2_t, 3> {using type = float32x2x3_t; };
template <> struct MultiVec<float32x4_t, 3> {using type = float32x4x3_t; };

template <> struct MultiVec<int8x8_t, 4> {using type = int8x8x4_t; };
template <> struct MultiVec<uint8x8_t, 4> {using type = uint8x8x4_t; };
template <> struct MultiVec<int16x4_t, 4> {using type = int16x4x4_t; };
template <> struct MultiVec<uint16x4_t, 4> {using type = uint16x4x4_t; };
template <> struct MultiVec<int32x2_t, 4> {using type = int32x2x4_t; };
template <> struct MultiVec<uint32x2_t, 4> {using type = uint32x2x4_t; };
template <> struct MultiVec<int8x16_t, 4> {using type = int8x16x4_t; };
template <> struct MultiVec<uint8x16_t, 4> {using type = uint8x16x4_t; };
template <> struct MultiVec<int16x8_t, 4> {using type = int16x8x4_t; };
template <> struct MultiVec<uint16x8_t, 4> {using type = uint16x8x4_t; };
template <> struct MultiVec<int32x4_t, 4> {using type = int32x4x4_t; };
template <> struct MultiVec<uint32x4_t, 4> {using type = uint32x4x4_t; };
template <> struct MultiVec<int64x1_t, 4> {using type = int64x1x4_t; };
template <> struct MultiVec<uint64x1_t, 4> {using type = uint64x1x4_t; };
template <> struct MultiVec<int64x2_t, 4> {using type = int64x2x4_t; };
template <> struct MultiVec<uint64x2_t, 4> {using type = uint64x2x4_t; };
template <> struct MultiVec<float32x2_t, 4> {using type = float32x2x4_t; };
template <> struct MultiVec<float32x4_t, 4> {using type = float32x4x4_t; };

template <typename T> struct Neon;

// clang-format on

template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template <typename vector_type>
class Lane;

template <typename vector_type>
class Common {
  using scalar_type = neon::NonVec<vector_type>::type;
  using result_type = Result<vector_type>::type;
  using neon_result_type = Neon<result_type>::type;

 public:
  using neon_type = Neon<vector_type>::type;
  static constexpr size_t lanes = (neon::is_quadword_v<vector_type> ? 16 : 8) / sizeof(scalar_type);

  constexpr Common() : vec_{0} {};
  constexpr Common(vector_type vector) : vec_(vector){};
  ace Common(scalar_type scalar) : vec_(LoadCopy(scalar)){};
  ace Common(scalar_type const* ptr) : vec_(Load(ptr)){};
  ace Common(std::span<scalar_type> slice) : vec_(Load(slice.data())){};
  ace Common(std::initializer_list<scalar_type> value_list) : vec_() {
    size_t i = 0;
    #pragma GCC unroll 16
    for (scalar_type val : value_list) {
      Set(i++, val);
    }
  };

  ace neon_type operator=(scalar_type b) { return vec_ = LoadCopy(b); }

  ace neon_type operator-() const { return Negate(); }

  ace neon_type operator+(neon_type b) const { return Add(b); }
  ace neon_type operator-(neon_type b) const { return Subtract(b); }
  ace neon_type operator*(neon_type b) const { return Multiply(b); }
  ace neon_type operator/(neon_type b) const { return Divide(b); }

  ace neon_type operator+=(neon_type b) { return vec_ = Add(b); }
  ace neon_type operator-=(neon_type b) { return vec_ = Subtract(b); }
  ace neon_type operator*=(neon_type b) { return vec_ = Multiply(b); }
  ace neon_type operator/=(neon_type b) { return vec_ = Divide(b); }

  ace neon_result_type operator==(neon_type b) const { return Equal(b); }
  ace neon_result_type operator<(neon_type b) const { return LessThan(b); }
  ace neon_result_type operator>(neon_type b) const { return GreaterThan(b); }
  ace neon_result_type operator<=(neon_type b) const { return LessThanOrEqual(b); }
  ace neon_result_type operator>=(neon_type b) const { return GreaterThanOrEqual(b); }

  ace neon_type operator++() const { return Add(1); }
  ace neon_type operator--() const { return Subtract(1); }

  ace neon_type operator&(neon_type b) const { return AndBitwise(b); }
  ace neon_type operator|(neon_type b) const { return OrBitwise(b); }
  ace neon_type operator^(neon_type b) const { return XorBitwise(b); }
  ace neon_type operator~() const { return NotBitwise(); }

  ace Lane<vector_type> operator[](const int i) const { return Lane{vec_, i}; }

  ace neon_type operator>>(const int i) const { return ShiftRight(i); }
  ace neon_type operator<<(const int i) const { return ShiftLeft(i); }

  [[gnu::always_inline]] constexpr operator vector_type() const { return vec_; }

  ace std::array<scalar_type, lanes> as_array() {
    std::array<scalar_type, lanes> out{0};
    Store(out.data());
    return out;
  }

  ace vector_type vec() const { return vec_; }

  ace scalar_type Get(const int i) const { return neon::get<vector_type>(vec_, i); }

  ace neon_type Set(const int i, scalar_type b) const { return neon::set(vec_, i, b); }

  ace neon_type ShiftRight(const int i) const { return neon::shift_right(vec_, i); }

  ace neon_type ShiftLeft(const int i) const { return neon::shift_left(vec_, i); }

  ace neon_type Negate() const { return neon::negate(vec_); }

  ace neon_type Add(neon_type b) const { return neon::add(vec_, b); }

  ace neon_type AddHalve(neon_type b) const { return neon::add_halve(vec_, b); }

  ace neon_type AddHalveRound(neon_type b) const { return neon::add_halve_round(vec_, b); }

  ace neon_type AddSaturate(neon_type b) const { return neon::add_saturate(vec_, b); }

  ace neon_type Multiply(neon_type b) const { return neon::multiply(vec_, b); }

  /** a + (b * c) */
  ace neon_type MultiplyAdd(neon_type b, neon_type c) const { return neon::multiply_add(vec_, b, c); }

  /** a + (b * c) */
  ace neon_type MultiplyAdd(neon_type b, scalar_type c) const { return neon::multiply_add(vec_, b, c); }

  /** a - (b * c) */
  ace neon_type MultiplySubtract(neon_type b, neon_type c) const { return neon::multiply_subtract(vec_, b, c); }

  /**
   * Multiply two fixed-point vectors, returning a fixed-point product
   * This is equivalent to (a * b) >> 31
   */
  ace neon_type MultiplyFixedPoint(neon_type v) const { return neon::multiply_double_saturate_high(vec_, v); }

  /**
   * Multiply a fixed-point vector by a scalar, returning a fixed-point product
   * This is equivalent to (a * b) >> 31
   */
  ace neon_type MultiplyFixedPoint(scalar_type s) const { return neon::multiply_double_saturate_high(vec_, s); }

  /**
   * Multiply two fixed-point vectors and round, returning a fixed-point product
   * This is equivalent to round(a * b) >> 31
   */
  ace neon_type MultiplyFixedPointRound(neon_type v) const { return neon::multiply_double_round_saturate_high(vec_, v); }

  /**
   * Multiply a fixed-point vector by a scalar and round, returning a fixed-point product
   * This is equivalent to round(a * b) >> 31
   */
  ace neon_type MultiplyFixedPointRound(scalar_type s) const { return neon::multiply_double_round_saturate_high(vec_, s); }

  ace neon_type Subtract(neon_type b) const { return neon::subtract(vec_, b); }

  ace neon_type SubtractHigh(neon_type b) const { return neon::subtract_high(vec_, b); }

  ace neon_type SubtractSaturate(neon_type b) const { return neon::subtract_saturate(vec_, b); }

  ace neon_type SubtractAbs(neon_type b) const { return neon::subtract_abs(vec_, b); }

  ace neon_type SubtractAbsAdd(neon_type b, neon_type c) const { return neon::subtract_abs_add(vec_, b, c); }

  ace neon_type Divide(neon_type b) const requires std::floating_point<scalar_type> {
#ifdef __aarch64__
    return neon::divide(vec_, b);
#else
    return this->map2(b, [](scalar_type lane1, scalar_type lane2) {
        return lane1 / lane2;
    });
#endif
    }

  ace neon_type Max(neon_type b) const { return neon::max(vec_, b); }

  ace neon_type Min(neon_type b) const { return neon::min(vec_, b); }

  ace neon_type AddPairwise(neon_type b) const { return neon::add_pairwise(vec_, b); }

  ace neon_type MaxPairwise(neon_type b) const { return neon::max_pairwise(vec_, b); }

  ace neon_type MinPairwise(neon_type b) const { return neon::min_pairwise(vec_, b); }

  ace neon_result_type Equal(neon_type b) const { return neon::equal(vec_, b); }
  ace neon_result_type GreaterThanOrEqual(neon_type b) const { return neon::greater_than_or_equal(vec_, b); }
  ace neon_result_type LessThanOrEqual(neon_type b) const { return neon::less_than_or_equal(vec_, b); }
  ace neon_result_type GreaterThan(neon_type b) const { return neon::greater_than(vec_, b); }
  ace neon_result_type LessThan(neon_type b) const { return neon::less_than(vec_, b); }

  ace neon_type AndTestNonzero(neon_type b) const { return neon::and_test_nonzero(vec_, b); }

  ace neon_type ShiftLeft(Common<typename neon::make_signed<vector_type>::type> b) const { return neon::shift_left(vec_, b); }

  ace neon_type ShiftLeftSaturate(Common<typename neon::make_signed<vector_type>::type> b) const {
    return neon::shift_left_saturate(vec_, b);
  }

  template <int n>
  ace neon_type ShiftLeftSaturate() const { return neon::shift_left_saturate<n>(vec_); }

  ace neon_type ShiftLeftRound(neon_type b) const { return neon::shift_left_round(vec_, b); }

  ace neon_type ShiftLeftRoundSaturate(neon_type b) const { return neon::shift_left_round_saturate(vec_, b); }

  template <int n>
  ace uint16x8_t ShiftLeftLong() const {
    return neon::shift_left_long<n>(vec_);
  }

  template <int n>
  ace neon_type ShiftLeftInsert(neon_type b) const {
    return neon::shift_left_insert<n>(vec_, b);
  }

  template <int n>
  ace neon_type ShiftRight() const {
    return neon::shift_right<n>(vec_);
  }

  template <int n>
  ace neon_type ShiftRightRound() const {
    return neon::shift_right_round<n>(vec_);
  }

  template <int n>
  ace neon_type ShiftRightAccumulate(neon_type b) const {
    return neon::shift_right_accumulate<n>(vec_, b);
  }

  template <int n>
  ace neon_type ShiftRightAccumulateRound(neon_type b) const {
    return neon::shift_right_accumulate_round<n>(vec_, b);
  }

  template <int n>
  ace neon_type ShiftRightInsert(neon_type b) const {
    return neon::shift_right_insert<n>(vec_, b);
  }

  ace static neon_type Load(scalar_type const* ptr) { return neon::load1<vector_type>(ptr); }
  ace static std::array<neon_type, 2> Load2(scalar_type const* ptr) { return *(std::array<neon_type, 2>*)(neon::load2<typename MultiVec<vector_type,2>::type>(ptr).val); }
  ace static std::array<neon_type, 3> Load3(scalar_type const* ptr) { return *(std::array<neon_type, 3>*)(neon::load3<typename MultiVec<vector_type,3>::type>(ptr).val); }
  ace static std::array<neon_type, 4> Load4(scalar_type const* ptr) { return *(std::array<neon_type, 4>*)(neon::load4<typename MultiVec<vector_type,4>::type>(ptr).val); }

  ace void Store(scalar_type* ptr) { neon::store1(ptr, vec_); }
  ace static void Store2(std::array<neon_type, 2> multi_vec, scalar_type* ptr) { neon::store2(ptr, *(typename MultiVec<vector_type, 2>::type*)multi_vec.data()); }
  ace static void Store3(std::array<neon_type, 3> multi_vec, scalar_type* ptr) { neon::store3(ptr, *(typename MultiVec<vector_type, 3>::type*)multi_vec.data()); }
  ace static void Store4(std::array<neon_type, 4> multi_vec, scalar_type* ptr) { neon::store4(ptr, *(typename MultiVec<vector_type, 4>::type*)multi_vec.data()); }

  template <int lane>
  ace void StoreLane(scalar_type* ptr) {
    neon::store1<lane>(ptr, vec_);
  }

  template <int lane>
  ace static void StoreLane2(std::array<neon_type, 2> multi_vec, scalar_type* ptr) {
    neon::store2<lane>(ptr, *(typename MultiVec<vector_type, 2>::type*)multi_vec.data());
  }

  template <int lane>
  ace static void StoreLane3(std::array<neon_type, 3> multi_vec, scalar_type* ptr) {
    neon::store3<lane>(ptr, *(typename MultiVec<vector_type, 3>::type*)multi_vec.data());
  }

  template <int lane>
  ace static void StoreLane4(std::array<neon_type, 4> multi_vec, scalar_type* ptr) {
    neon::store4<lane>(ptr, *(typename MultiVec<vector_type, 4>::type*)multi_vec.data());
  }

  ace static neon_type LoadCopy(scalar_type b) { return neon::duplicate_element<vector_type>(b); }
  ace static neon_type Move(scalar_type b) { return neon::move<vector_type>(b); }

  ace neon_type NotBitwise() const { return neon::not_bitwise(vec_); }

  ace neon_type AndBitwise(neon_type b) const { return neon::and_bitwise(vec_, b); }

  ace neon_type OrBitwise(neon_type b) const { return neon::or_bitwise(vec_, b); }

  ace neon_type XorBitwise(neon_type b) const { return neon::xor_bitwise(vec_, b); }

  ace neon_type OrNotBitwise(neon_type b) const { return neon::or_not_bitwise(vec_, b); }

  ace typename neon::make_signed<vector_type>::type CountLeadingSignBits() const {
    return neon::count_leading_sign_bits(vec_);
  }

  ace neon_type CountLeadingZeroBits() const { return neon::count_leading_zero_bits(vec_); }

  ace neon_type CountActiveBits() const { return neon::count_active_bits(vec_); }

  ace neon_type ClearBitwise(neon_type b) const { return neon::clear_bitwise(vec_, b); }

  ace neon_type SelectBitwise(neon_type b, neon_type c) const { return neon::select_bitwise(vec_, b, c); }

  template <int lane>
  ace neon_type DuplicateElement() const {
    return neon::duplicate_element(vec_, lane);
  }

  template <int lane>
  ace uint8x16_t DuplicateElement() const {
    return neon::duplicate_element(vec_, lane);
  }

  template <int lane>
  ace uint8_t Get() const {
    return neon::get(vec_, lane);
  }

  /// Extract n elements from the lower end of this vector, and the remaining elements from the higher end of the
  /// operand, combining them into the result vector.
  template <int n>
  ace neon_type Extract(neon_type b) const {
    return neon::extract<n>(vec_, b);
  }

  ace neon_type Reverse64bit() const { return neon::reverse_64bit(vec_); }

  ace neon_type Reverse32bit() const { return neon::reverse_32bit(vec_); }

  ace neon_type Reverse16bit() const { return neon::reverse_16bit(vec_); }

  ace auto Zip(neon_type b) const { return neon::zip(vec_, b); }

  auto Unzip(neon_type b) { return neon::unzip(vec_, b); }

  ace auto Transpose(neon_type b) const { return neon::transpose(vec_, b); }

  ace static int size() { return lanes; }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<scalar_type(scalar_type)>>
  ace neon_type map(FuncType body) const {
    neon_type out;
    for (int i = 0; i < lanes; ++i) {
      out[i] = body(vec_[i]);
    }
    return out;
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<scalar_type(scalar_type, scalar_type)>>
  ace neon_type map2(neon_type other, FuncType body) const {
    neon_type out;
    for (int i = 0; i < lanes; ++i) {
      out[i] = body(vec_[i], other.vec_[i]);
    }
    return out;
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void(scalar_type&)>>
  ace void each(FuncType body) {
    for (int i = 0; i < lanes; ++i) {
      body(vec_[i]);
    }
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void(scalar_type&, int)>>
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

  template<std::size_t Index>
  std::tuple_element_t<Index, neon_type> get() {
    return Lane{vec_, Index};
  }

 protected:
  vector_type vec_;
};

template <typename vector_type>
class Lane {
  using scalar_type = neon::NonVec<vector_type>::type;

 public:
  using T = Lane<vector_type>;

  ace Lane(vector_type vec, const int lane) : vec_(vec), lane_(lane){};

  ace operator neon::NonVec<vector_type>::type() { return neon::get(vec_, lane_); }

  ace Common<vector_type> operator=(scalar_type b) { return neon::set(vec_, lane_, b); }
  ace Common<vector_type> operator=(T t) { return neon::set(vec_, lane_, neon::get(t.vec_, t.lane_)); }

  ace Common<vector_type> operator+=(scalar_type b) { return neon::set(vec_, lane_, neon::get(vec_, lane_) + b); }
  ace Common<vector_type> operator-=(scalar_type b) { return neon::set(vec_, lane_, neon::get(vec_, lane_) - b); }
  ace Common<vector_type> operator*=(scalar_type b) { return neon::set(vec_, lane_, neon::get(vec_, lane_) * b); }
  ace Common<vector_type> operator/=(scalar_type b) { return neon::set(vec_, lane_, neon::get(vec_, lane_) / b); }

 private:
  vector_type vec_;
  const int lane_;
};

}  // namespace impl

template <typename scalar_type>
class Neon128;

template <typename scalar_type>
class Neon64 : public impl::Common<typename impl::Vec64<scalar_type>::type> {
  using T = impl::Common<typename impl::Vec64<scalar_type>::type>;

 public:
  using vector_type = impl::Vec64<scalar_type>::type;

  static_assert(neon::is_doubleword_v<vector_type>);

  static constexpr size_t bytes = 8;
  static constexpr size_t lanes = bytes / sizeof(scalar_type);

  constexpr Neon64() : T(){};
  constexpr Neon64(vector_type vector) : T(vector){};
  constexpr Neon64(scalar_type scalar) : T(scalar){};
  constexpr Neon64(scalar_type const* ptr) : T(ptr){};
  constexpr Neon64(T&& in) : T(in){};
  constexpr Neon64(std::initializer_list<scalar_type> value_list) : T(value_list) {};
  constexpr Neon64(std::span<scalar_type> slice) : T(slice) {};

  ace static Neon64<scalar_type> Load(scalar_type const* ptr) { return neon::load1<vector_type>(ptr); }
  ace static Neon64<scalar_type> LoadCopy(scalar_type b) { return neon::duplicate_element<vector_type>(b); }
  ace static Neon64<scalar_type> Move(scalar_type b) { return neon::move<vector_type>(b); }

  ace static std::array<Neon64<scalar_type>, 2> Load2(scalar_type const* ptr) { return *(std::array<Neon64<scalar_type>, 2>*)(neon::load2<typename impl::MultiVec<vector_type,2>::type>(ptr).val); }
  ace static std::array<Neon64<scalar_type>, 3> Load3(scalar_type const* ptr) { return *(std::array<Neon64<scalar_type>, 3>*)(neon::load3<typename impl::MultiVec<vector_type,3>::type>(ptr).val); }
  ace static std::array<Neon64<scalar_type>, 4> Load4(scalar_type const* ptr) { return *(std::array<Neon64<scalar_type>, 4>*)(neon::load4<typename impl::MultiVec<vector_type,4>::type>(ptr).val); }


  template <typename U>
  requires impl::has_larger_v<scalar_type>
  ace Neon128<U> AddLong(Neon64<scalar_type> b) const { return neon::add_long(this->vec_, b); }

  template <typename U>
  requires impl::has_larger_v<scalar_type>
  ace Neon128<U> MultiplyLong(Neon64<scalar_type> b) const { return neon::multiply_long(this->vec_, b); }

  template <typename U>
  requires impl::has_larger_v<scalar_type>
  ace Neon128<U> SubtractLong(Neon64<scalar_type> b) const { return neon::subtract_long(this->vec_, b); }

  template <typename U>
  requires impl::has_larger_v<scalar_type>
  ace Neon128<U> MoveLong() const { return neon::move_long(this->vec_); }

  template <typename U>
  requires impl::has_larger_v<scalar_type>
  ace Neon128<U> SubtractAbsLong(Neon64<scalar_type> b) const { return neon::subtract_abs_long(this->vec_, b); }

  template <typename U>
  requires impl::has_larger_v<scalar_type>
  ace Neon128<U> AddPairwiseLong() const { return neon::add_pairwise_long(this->vec_); }

  ace T TableLookup1(T idx) const { return neon::table_lookup1(this->vec_, idx); }
  ace T TableLookupExtension1(T b, T idx) const { return neon::table_lookup_extension1(this->vec_, b, idx); }
  ace T TableLookupExtension2(uint8x8x2_t b, T idx) const { return neon::table_lookup_extension2(this->vec_, b, idx); }
  ace T TableLookupExtension3(uint8x8x3_t b, T idx) const { return neon::table_lookup_extension3(this->vec_, b, idx); }
  ace T TableLookupExtension4(uint8x8x4_t b, T idx) const { return neon::table_lookup_extension4(this->vec_, b, idx); }

  template <typename U>
  ace Neon64<U> Convert(int n) {
    return neon::convert<typename impl::Vec64<U>::type>(this->vec_, n);
  }

  template <typename U>
  ace Neon64<U> Convert() {
    return neon::convert<typename impl::Vec64<U>::type>(this->vec_);
  }

  ace Neon128<scalar_type> Combine(Neon64<scalar_type> high) const { return neon::combine(this->vec_, high); }
};

template <typename scalar_type>
class Neon128 : public impl::Common<typename impl::Vec128<scalar_type>::type> {
  using T = impl::Common<typename impl::Vec128<scalar_type>::type>;

 public:
  using vector_type = impl::Vec128<scalar_type>::type;

  static_assert(neon::is_quadword_v<vector_type>);

  static constexpr size_t bytes = 16;
  static constexpr size_t lanes = bytes / sizeof(scalar_type);

  constexpr Neon128() : T(){};
  constexpr Neon128(vector_type vector) : T(vector){};
  constexpr Neon128(scalar_type scalar) : T(scalar){};
  constexpr Neon128(scalar_type const* ptr) : T(ptr){};
  constexpr Neon128(T&& in) : T(in){};
  constexpr Neon128(std::initializer_list<scalar_type> value_list) : T(value_list) {};
  constexpr Neon128(std::span<scalar_type> slice) : T(slice) {};
  constexpr Neon128(Neon64<scalar_type> low, Neon64<scalar_type> high) : T(neon::combine(low, high)) {};

  ace static Neon128<scalar_type> Load(scalar_type const* ptr) { return neon::load1<vector_type>(ptr); }
  ace static Neon128<scalar_type> LoadCopy(scalar_type b) { return neon::duplicate_element<vector_type>(b); }
  ace static Neon128<scalar_type> Move(scalar_type b) { return neon::move<vector_type>(b); }
  ace static Neon128<scalar_type> Combine(Neon64<scalar_type> low, Neon64<scalar_type> high) { return neon::combine(low, high); }

  ace static std::array<Neon128<scalar_type>, 2> Load2(scalar_type const* ptr) { return *(std::array<Neon128<scalar_type>, 2>*)(neon::load2<typename impl::MultiVec<vector_type,2>::type>(ptr).val); }
  ace static std::array<Neon128<scalar_type>, 3> Load3(scalar_type const* ptr) { return *(std::array<Neon128<scalar_type>, 3>*)(neon::load3<typename impl::MultiVec<vector_type,3>::type>(ptr).val); }
  ace static std::array<Neon128<scalar_type>, 4> Load4(scalar_type const* ptr) { return *(std::array<Neon128<scalar_type>, 4>*)(neon::load4<typename impl::MultiVec<vector_type,4>::type>(ptr).val); }

  template <typename U>
  requires impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename impl::NextSmaller<scalar_type>::type>
  ace Neon128<scalar_type> MultiplyAddLong(Neon64<U> b, Neon64<U> c) const{ return neon::multiply_add_long(this->vec_, b, c); }

  template <size_t n=32, typename U>
  requires impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename impl::NextSmaller<scalar_type>::type>
  ace Neon64<U> ShiftRightNarrow() { return neon::shift_right_narrow<n>(this->vec_); }

  template <size_t n=32, typename U>
  requires impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename impl::NextSmaller<scalar_type>::type>
  ace Neon64<U> ShiftRightNarrowRounded() { return neon::shift_right_round_narrow<n>(this->vec_); }

  ace Neon64<scalar_type> GetHigh() { return neon::get_high(this->vec_); }
  ace Neon64<scalar_type> GetLow() { return neon::get_low(this->vec_); }

  template <typename U>
  ace Neon128<U> Convert(int n) {
    return neon::convert<typename impl::Vec128<U>::type>(this->vec_, n);
  }

  template <typename U>
  ace Neon128<U> Convert() {
    return neon::convert<typename impl::Vec128<U>::type>(this->vec_);
  }
};

namespace impl {
template <neon::is_vector_type T>
requires neon::is_quadword<T>
struct Neon<T> { using type = Neon128<typename neon::NonVec<T>::type>; };

template <neon::is_vector_type T>
requires neon::is_doubleword<T>
struct Neon<T> { using type = Neon64<typename neon::NonVec<T>::type>; };
}

template <typename T, typename V>
ace auto reinterpret(impl::Common<V> in) {
  if constexpr(neon::is_quadword_v<V>) {
    return Neon128<T>{neon::reinterpret<typename Neon128<T>::vector_type>(in.vec())};
  } else if constexpr(neon::is_doubleword_v<V>) {
    return Neon64<T>{neon::reinterpret<typename Neon64<T>::vector_type>(in.vec())};
  }
}

template <typename NeonType, neon::is_vector_type V>
ace NeonType reinterpret(V in) {
  static_assert(!std::is_same_v<typename NeonType::vector_type, V>);
  return NeonType{neon::reinterpret<typename NeonType::vector_type>(in)};
}

template <typename V>
requires std::is_scalar_v<V>
ace Neon128<V> operator+(V a, Neon128<V> b) {
  return b.Add(a);
}

template <typename V>
requires std::is_scalar_v<V>
ace Neon128<V> operator-(V a, Neon128<V> b) {
  return Neon128<V>{a}.Subtract(b);
}

template <typename V>
requires std::is_scalar_v<V>
ace Neon128<V> operator*(V a, Neon128<V> b) {
  return b.Multiply(a);
}

template <typename V>
requires std::is_scalar_v<V>
ace Neon128<V> operator/(V a, Neon128<V> b) {
  return Neon128<V>{a}.Divide(b);
}

}  // namespace argon
#undef ace


namespace std {
  template<typename T>
  struct tuple_size<argon::impl::Common<T>> {
    static constexpr size_t value = argon::impl::Common<T>::lanes;
  };

  template<typename T>
  struct tuple_size<argon::Neon128<T>> {
    static constexpr size_t value = argon::Neon128<T>::lanes;
  };

  template<typename T>
  struct tuple_size<argon::Neon64<T>> {
    static constexpr size_t value = argon::Neon64<T>::lanes;
  };

  template<size_t Index, typename T>
  struct tuple_element<Index, argon::impl::Common<T>> {
    static_assert(Index < argon::impl::Common<T>::lanes);
    using type = argon::impl::Common<T>::lane_type;
  };

  template<size_t Index, typename T>
  struct tuple_element<Index, argon::Neon128<T>> {
    static_assert(Index < argon::Neon128<T>::lanes);
    using type = argon::impl::Lane<typename argon::Neon128<T>::vector_type>;
  };

  template<size_t Index, typename T>
  struct tuple_element<Index, argon::Neon64<T>> {
    static_assert(Index < argon::Neon64<T>::lanes);
    using type = argon::impl::Lane<typename argon::Neon64<T>::vector_type>;
  };
}
