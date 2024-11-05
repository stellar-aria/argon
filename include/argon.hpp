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
#include <ranges>

#ifdef __clang__
#define ace [[gnu::always_inline]] constexpr
#else
#define ace [[gnu::always_inline]] inline
#endif

namespace argon {
template <typename T> class Neon64;
template <typename T> class Neon128;
namespace impl {

// clang-format off

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
template <> struct NextLarger<int8_t> { using type = int16_t; };
template <> struct NextLarger<uint8_t> { using type = uint16_t; };
template <> struct NextLarger<int16_t> { using type = int32_t; };
template <> struct NextLarger<uint16_t> { using type = uint32_t; };
template <> struct NextLarger<int32_t> { using type = int64_t; };
template <> struct NextLarger<uint32_t> { using type = uint64_t; };
template <> struct NextLarger<float> { using type = double; };

template <typename T> struct NextSmaller;
template <> struct NextSmaller<int16_t> { using type = int8_t; };
template <> struct NextSmaller<uint16_t> { using type = uint8_t; };
template <> struct NextSmaller<int32_t> { using type = int16_t; };
template <> struct NextSmaller<uint32_t> { using type = uint16_t; };
template <> struct NextSmaller<int64_t> { using type = int32_t; };
template <> struct NextSmaller<uint64_t> { using type = uint32_t; };
template <> struct NextSmaller<double> { using type = float; };

template <typename T> struct Result;
template <> struct Result<int8x8_t> { using type = uint8x8_t; };
template <> struct Result<uint8x8_t> { using type = uint8x8_t; };
template <> struct Result<int16x4_t> { using type = uint16x4_t; };
template <> struct Result<uint16x4_t> { using type = uint16x4_t; };
template <> struct Result<int32x2_t> { using type = uint32x2_t; };
template <> struct Result<uint32x2_t> { using type = uint32x2_t; };
template <> struct Result<int8x16_t> { using type = uint8x16_t; };
template <> struct Result<uint8x16_t> { using type = uint8x16_t; };
template <> struct Result<int16x8_t> { using type = uint16x8_t; };
template <> struct Result<uint16x8_t> { using type = uint16x8_t; };
template <> struct Result<int32x4_t> { using type = uint32x4_t; };
template <> struct Result<uint32x4_t> { using type = uint32x4_t; };
template <> struct Result<int64x1_t> { using type = uint64x1_t; };
template <> struct Result<uint64x1_t> { using type = uint64x1_t; };
template <> struct Result<int64x2_t> { using type = uint64x2_t; };
template <> struct Result<uint64x2_t> { using type = uint64x2_t; };
template <> struct Result<float32x2_t> { using type = uint32x2_t; };
template <> struct Result<float32x4_t> { using type = uint32x4_t; };

template <typename T, size_t size> struct MultiVec;
template <> struct MultiVec<int8x8_t, 2> { using type = int8x8x2_t; };
template <> struct MultiVec<uint8x8_t, 2> { using type = uint8x8x2_t; };
template <> struct MultiVec<int16x4_t, 2> { using type = int16x4x2_t; };
template <> struct MultiVec<uint16x4_t, 2> { using type = uint16x4x2_t; };
template <> struct MultiVec<int32x2_t, 2> { using type = int32x2x2_t; };
template <> struct MultiVec<uint32x2_t, 2> { using type = uint32x2x2_t; };
template <> struct MultiVec<int8x16_t, 2> { using type = int8x16x2_t; };
template <> struct MultiVec<uint8x16_t, 2> { using type = uint8x16x2_t; };
template <> struct MultiVec<int16x8_t, 2> { using type = int16x8x2_t; };
template <> struct MultiVec<uint16x8_t, 2> { using type = uint16x8x2_t; };
template <> struct MultiVec<int32x4_t, 2> { using type = int32x4x2_t; };
template <> struct MultiVec<uint32x4_t, 2> { using type = uint32x4x2_t; };
template <> struct MultiVec<int64x1_t, 2> { using type = int64x1x2_t; };
template <> struct MultiVec<uint64x1_t, 2> { using type = uint64x1x2_t; };
template <> struct MultiVec<int64x2_t, 2> { using type = int64x2x2_t; };
template <> struct MultiVec<uint64x2_t, 2> { using type = uint64x2x2_t; };
template <> struct MultiVec<float32x2_t, 2> { using type = float32x2x2_t; };
template <> struct MultiVec<float32x4_t, 2> { using type = float32x4x2_t; };

template <> struct MultiVec<int8x8_t, 3> { using type = int8x8x3_t; };
template <> struct MultiVec<uint8x8_t, 3> { using type = uint8x8x3_t; };
template <> struct MultiVec<int16x4_t, 3> { using type = int16x4x3_t; };
template <> struct MultiVec<uint16x4_t, 3> { using type = uint16x4x3_t; };
template <> struct MultiVec<int32x2_t, 3> { using type = int32x2x3_t; };
template <> struct MultiVec<uint32x2_t, 3> { using type = uint32x2x3_t; };
template <> struct MultiVec<int8x16_t, 3> { using type = int8x16x3_t; };
template <> struct MultiVec<uint8x16_t, 3> { using type = uint8x16x3_t; };
template <> struct MultiVec<int16x8_t, 3> { using type = int16x8x3_t; };
template <> struct MultiVec<uint16x8_t, 3> { using type = uint16x8x3_t; };
template <> struct MultiVec<int32x4_t, 3> { using type = int32x4x3_t; };
template <> struct MultiVec<uint32x4_t, 3> { using type = uint32x4x3_t; };
template <> struct MultiVec<int64x1_t, 3> { using type = int64x1x3_t; };
template <> struct MultiVec<uint64x1_t, 3> { using type = uint64x1x3_t; };
template <> struct MultiVec<int64x2_t, 3> { using type = int64x2x3_t; };
template <> struct MultiVec<uint64x2_t, 3> { using type = uint64x2x3_t; };
template <> struct MultiVec<float32x2_t, 3> { using type = float32x2x3_t; };
template <> struct MultiVec<float32x4_t, 3> { using type = float32x4x3_t; };

template <> struct MultiVec<int8x8_t, 4> { using type = int8x8x4_t; };
template <> struct MultiVec<uint8x8_t, 4> { using type = uint8x8x4_t; };
template <> struct MultiVec<int16x4_t, 4> { using type = int16x4x4_t; };
template <> struct MultiVec<uint16x4_t, 4> { using type = uint16x4x4_t; };
template <> struct MultiVec<int32x2_t, 4> { using type = int32x2x4_t; };
template <> struct MultiVec<uint32x2_t, 4> { using type = uint32x2x4_t; };
template <> struct MultiVec<int8x16_t, 4> { using type = int8x16x4_t; };
template <> struct MultiVec<uint8x16_t, 4> { using type = uint8x16x4_t; };
template <> struct MultiVec<int16x8_t, 4> { using type = int16x8x4_t; };
template <> struct MultiVec<uint16x8_t, 4> { using type = uint16x8x4_t; };
template <> struct MultiVec<int32x4_t, 4> { using type = int32x4x4_t; };
template <> struct MultiVec<uint32x4_t, 4> { using type = uint32x4x4_t; };
template <> struct MultiVec<int64x1_t, 4> { using type = int64x1x4_t; };
template <> struct MultiVec<uint64x1_t, 4> { using type = uint64x1x4_t; };
template <> struct MultiVec<int64x2_t, 4> { using type = int64x2x4_t; };
template <> struct MultiVec<uint64x2_t, 4> { using type = uint64x2x4_t; };
template <> struct MultiVec<float32x2_t, 4> { using type = float32x2x4_t; };
template <> struct MultiVec<float32x4_t, 4> { using type = float32x4x4_t; };
// clang-format on

template <typename T> struct Neon;


template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template <typename vector_type>
class Lane;

template <typename vector_type>
class Common {
 public:
  using scalar_type = neon::NonVec<vector_type>::type;
  using lane_type = Lane<vector_type>;
  using result_type = Result<vector_type>::type;
  using neon_result_type = Neon<result_type>::type;
  using neon_type = Neon<vector_type>::type;

  static constexpr size_t lanes = (neon::is_quadword_v<vector_type> ? 16 : 8) / sizeof(scalar_type);

  constexpr Common() : vec_{0} {};
  constexpr Common(vector_type vector) : vec_(vector){};
  ace Common(scalar_type scalar) : vec_(neon::duplicate<vector_type>(scalar)){};
  ace Common(scalar_type const* ptr) : vec_(Load(ptr)){};
  ace Common(std::span<scalar_type> slice) : vec_(Load(slice.data())){};
  ace Common(std::initializer_list<scalar_type> value_list) : vec_(Load(value_list.begin())) {};

  ace neon_type operator=(scalar_type b) { return vec_ = neon::duplicate<vector_type>(b); }
  ace neon_type operator=(Lane<typename neon::Vec64<scalar_type>::type> b) { return this->vec_ = neon::duplicate_lane<vector_type>(b.vec(), b.lane()); }
  ace neon_type operator=(Lane<typename neon::Vec128<scalar_type>::type> b) {
    constexpr size_t doubleword_lanes = Neon64<scalar_type>::lanes;
    size_t lane = b.lane();
    Neon128<scalar_type> vec = b.vec();
    Neon64<scalar_type> half;
    if (lane >= doubleword_lanes) {
        half = vec.GetHigh();
        lane -= doubleword_lanes;
    } else {
        half = vec.GetLow();
    }
    return this->vec_ = neon::duplicate_lane<vector_type>(half, lane);
  }

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

  ace neon_type operator&(neon_type b) const { return BitwiseAnd(b); }
  ace neon_type operator|(neon_type b) const { return BitwiseOr(b); }
  ace neon_type operator^(neon_type b) const { return BitwiseXor(b); }
  ace neon_type operator~() const { return BitwiseNot(); }

  ace Lane<vector_type> operator[](const int i) const { return Lane{vec_, i}; }

  ace neon_type operator>>(const int i) const { return ShiftRight(i); }
  ace neon_type operator<<(const int i) const { return ShiftLeft(i); }

  [[gnu::always_inline]] constexpr operator vector_type() const { return vec_; }

  ace std::array<scalar_type, lanes> as_array() {
    std::array<scalar_type, lanes> out;
    Store(out.data());
    return out;
  }

  ace vector_type vec() const { return vec_; }

  ace lane_type GetLane(const int i) { return neon::get_lane(vec_, i); }

  ace neon_type ShiftRight(const int i) const { return neon::shift_right(vec_, i); }
  ace neon_type ShiftLeft(const int i) const { return neon::shift_left(vec_, i); }

  ace neon_type Negate() const { return neon::negate(vec_); }

  ace neon_type Add(neon_type b) const { return neon::add(vec_, b); }
  ace neon_type AddHalve(neon_type b) const { return neon::add_halve(vec_, b); }
  ace neon_type AddHalveRound(neon_type b) const { return neon::add_halve_round(vec_, b); }
  ace neon_type AddSaturate(neon_type b) const { return neon::add_saturate(vec_, b); }

  ace neon_type Subtract(neon_type b) const { return neon::subtract(vec_, b); }
  ace neon_type SubtractHalve(neon_type b) const { return neon::subtract_halve(vec_, b); }
  ace neon_type SubtractSaturate(neon_type b) const { return neon::subtract_saturate(vec_, b); }
  ace neon_type SubtractAbs(neon_type b) const { return neon::subtract_abs(vec_, b); }
  ace neon_type SubtractAbsAdd(neon_type b, neon_type c) const { return neon::subtract_abs_add(vec_, b, c); }

  /** a * b */
  ace neon_type Multiply(neon_type b) const { return neon::multiply(vec_, b); }
  ace neon_type Multiply(scalar_type b) const { return neon::multiply(vec_, b); }
  ace neon_type Multiply(lane_type b) const { return neon::multiply_lane(vec_, b.vec(), b.lane()); }

  /** a + (b * c) */
  ace neon_type MultiplyAdd(neon_type b, neon_type c) const { return neon::multiply_add(vec_, b, c); }
  ace neon_type MultiplyAdd(neon_type b, scalar_type c) const { return neon::multiply_add(vec_, b, c); }
  ace neon_type MultiplyAdd(neon_type b, lane_type c) const { return neon::multiply_add_lane(vec_, b, c.vec(), c.lane()); }

  /** a - (b * c) */
  ace neon_type MultiplySubtract(neon_type b, neon_type c) const { return neon::multiply_subtract(vec_, b, c); }
  ace neon_type MultiplySubtract(neon_type b, scalar_type c) const { return neon::multiply_subtract(vec_, b, c); }
  ace neon_type MultiplySubtract(neon_type b, lane_type c) const { return neon::multiply_subtract(vec_, b, c.vec(), c.lane()); }

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

  ace neon_result_type Equal(neon_type b) const { return neon::equal(vec_, b); }
  ace neon_result_type GreaterThanOrEqual(neon_type b) const { return neon::greater_than_or_equal(vec_, b); }
  ace neon_result_type LessThanOrEqual(neon_type b) const { return neon::less_than_or_equal(vec_, b); }
  ace neon_result_type GreaterThan(neon_type b) const { return neon::greater_than(vec_, b); }
  ace neon_result_type LessThan(neon_type b) const { return neon::less_than(vec_, b); }

  ace neon_type ShiftLeft(Common<typename neon::make_signed<vector_type>::type> b) const { return neon::shift_left(vec_, b); }
  ace neon_type ShiftLeftSaturate(Common<typename neon::make_signed<vector_type>::type> b) const { return neon::shift_left_saturate(vec_, b);}
  ace neon_type ShiftLeftRound(neon_type b) const { return neon::shift_left_round(vec_, b); }
  ace neon_type ShiftLeftRoundSaturate(neon_type b) const { return neon::shift_left_round_saturate(vec_, b); }

  template <int n> ace neon_type ShiftLeftSaturate() const { return neon::shift_left_saturate<n>(vec_); }
  template <int n> ace neon_type ShiftLeftInsert(neon_type b) const { return neon::shift_left_insert<n>(vec_, b); }

  template <int n> ace neon_type ShiftRight() const { return neon::shift_right<n>(vec_); }
  template <int n> ace neon_type ShiftRightRound() const { return neon::shift_right_round<n>(vec_); }
  template <int n> ace neon_type ShiftRightAccumulate(neon_type b) const { return neon::shift_right_accumulate<n>(vec_, b); }
  template <int n> ace neon_type ShiftRightAccumulateRound(neon_type b) const { return neon::shift_right_accumulate_round<n>(vec_, b); }
  template <int n> ace neon_type ShiftRightInsert(neon_type b) const { return neon::shift_right_insert<n>(vec_, b); }

  ace static neon_type Load(scalar_type const* ptr) { return neon::load1<vector_type>(ptr); }

  template <size_t stride>
  ace static std::array<neon_type, stride> LoadInterleaved(scalar_type const* ptr) {
    static_assert(stride > 1 && stride < 5, "De-interleaving Loads can only be performed with a stride of 2, 3, or 4");
    using multivec_type = MultiVec<vector_type, stride>::type;
    using array_type = std::array<neon_type, stride>;

    // Since we're using a dirty ugly hack of reinterpreting a C array as a std::array,
    // the validity and POD-ness of std::array needs to be verified
    static_assert(std::is_standard_layout_v<array_type>);
    static_assert(std::is_trivial_v<array_type>);
    static_assert(sizeof(multivec_type) == sizeof(array_type),
                  "std::array isn't layout-compatible with this NEON multi-vector.");

    if constexpr (stride == 2) {
      return *(array_type*)(neon::load2<multivec_type>(ptr).val);
    } else if constexpr (stride == 3) {
      return *(array_type*)(neon::load3<multivec_type>(ptr).val);
    } else if constexpr (stride == 4) {
      return *(array_type*)(neon::load4<multivec_type>(ptr).val);
    }
  }

  /**
   * @brief Load n vectors from a single contiguous set of memory.
   *
   * @tparam n The number of vectors to load
   * @param ptr The pointer to the location in memory to load from
   * @return std::array An array of NEON vectors.
   */
  template <size_t n>
  ace static std::array<neon_type, n> LoadMulti(scalar_type const* ptr) {
    std::array<neon_type, n> out;
#pragma unroll
    for (size_t i = 0; i < n; ++i) {
      out[i] = Load(ptr);
      ptr += lanes;
    }
    return out;
  }

  ace void StoreTo(scalar_type* ptr) const { neon::store1(ptr, vec_); }

  template <int lane>
  ace void StoreLaneTo(scalar_type* ptr) { neon::store1_lane<lane>(ptr, vec_); }

  /// Pairwise ops

  ace neon_type PairwiseAdd(neon_type b) const { return neon::pairwise_add(vec_, b); }
  ace neon_type PairwiseMax(neon_type b) const { return neon::pairwise_max(vec_, b); }
  ace neon_type PairwiseMin(neon_type b) const { return neon::pairwise_min(vec_, b); }


  /// Bitwise ops

  ace neon_type BitwiseNot() const { return neon::bitwise_not(vec_); }
  ace neon_type BitwiseAnd(neon_type b) const { return neon::bitwise_and(vec_, b); }
  ace neon_type BitwiseOr(neon_type b) const { return neon::bitwise_or(vec_, b); }
  ace neon_type BitwiseXor(neon_type b) const { return neon::bitwise_xor(vec_, b); }
  ace neon_type BitwiseOrNot(neon_type b) const { return neon::bitwise_or_not(vec_, b); }
  ace neon_type BitwiseClear(neon_type b) const { return neon::bitwise_clear(vec_, b); }
  ace neon_type BitwiseSelect(neon_type b, neon_type c) const { return neon::bitwise_select(vec_, b, c); }

  /// Ands the current vector with the given vector, then checks if nonzero.
  /// If so, fills the lane with all ones
  ace neon_type CompareTestNonzero(neon_type b) const { return neon::compare_test_nonzero(vec_, b); }
  ace neon_type TestNonzero() const { return neon::compare_test_nonzero(vec_, neon_type{1}); }

  ace typename neon::make_signed<vector_type>::type CountLeadingSignBits() const {
    return neon::count_leading_sign_bits(vec_);
  }

  ace neon_type CountLeadingZeroBits() const { return neon::count_leading_zero_bits(vec_); }
  ace neon_type CountActiveBits() const { return neon::count_active_bits(vec_); }


  /// Extract n elements from the lower end of this vector, and the remaining elements from the higher end of the
  /// operand, combining them into the result vector.
  template <int n>
  ace neon_type Extract(neon_type b) const { return neon::extract<n>(vec_, b); }

  ace neon_type Reverse64bit() const { return neon::reverse_64bit(vec_); }
  ace neon_type Reverse32bit() const { return neon::reverse_32bit(vec_); }
  ace neon_type Reverse16bit() const { return neon::reverse_16bit(vec_); }

  ace std::array<neon_type, 2> ZipWith(neon_type b) const {
    using multivec_type = MultiVec<vector_type, 2>::type;
    using array_type = std::array<neon_type, 2>;

    // Since we're using a dirty ugly hack of reinterpreting a C array as a std::array,
    // the validity and POD-ness of std::array needs to be verified
    static_assert(std::is_standard_layout_v<array_type>);
    static_assert(std::is_trivial_v<array_type>);
    static_assert(sizeof(multivec_type) == sizeof(array_type),
                  "std::array isn't layout-compatible with this NEON multi-vector.");

    return *(array_type*)neon::zip(vec_, b).val;
  }

  std::array<neon_type, 2> UnzipWith(neon_type b) {
    using multivec_type = MultiVec<vector_type, 2>::type;
    using array_type = std::array<neon_type, 2>;

    // Since we're using a dirty ugly hack of reinterpreting a C array as a std::array,
    // the validity and POD-ness of std::array needs to be verified
    static_assert(std::is_standard_layout_v<array_type>);
    static_assert(std::is_trivial_v<array_type>);
    static_assert(sizeof(multivec_type) == sizeof(array_type),
                  "std::array isn't layout-compatible with this NEON multi-vector.");

    return *(array_type*)neon::unzip(vec_, b).val;
  }

  std::array<neon_type, 2> TransposeWith(neon_type b) const {
    using multivec_type = MultiVec<vector_type, 2>::type;
    using array_type = std::array<neon_type, 2>;

    // Since we're using a dirty ugly hack of reinterpreting a C array as a std::array,
    // the validity and POD-ness of std::array needs to be verified
    static_assert(std::is_standard_layout_v<array_type>);
    static_assert(std::is_trivial_v<array_type>);
    static_assert(sizeof(multivec_type) == sizeof(array_type),
                  "std::array isn't layout-compatible with this NEON multi-vector.");

    return *(array_type*)neon::transpose(vec_, b).val;
  }

  ace static int size() { return lanes; }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<scalar_type(scalar_type)>>
  ace neon_type map(FuncType body) const {
    std::array<scalar_type, lanes> arr = this->as_array();
    std::array<scalar_type, lanes> out;
    for (size_t i = 0; i < lanes; ++i) {
      out[i] = body(arr[i]);
    }
    return neon_type::Load(out);
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<scalar_type(scalar_type, scalar_type)>>
  ace neon_type map2(neon_type other, FuncType body) const {
    std::array<scalar_type, lanes> arr0 = this->as_array();
    std::array<scalar_type, lanes> arr1 = other.as_array();
    std::array<scalar_type, lanes> out;
    for (size_t i = 0; i < lanes; ++i) {
      out[i] = body(arr0[i], arr1[i]);
    }
    return neon_type::Load(out);
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void(scalar_type&)>>
  ace void each_lane(FuncType body) {
    for (scalar_type s : this->as_array()) {
      body(s);
    }
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void(scalar_type&, int)>>
  ace void each_lane_with_index(FuncType body) {
    auto arr = this->as_array();
    for (size_t i = 0; i < lanes; ++i) {
      body(arr[i], i);
    }
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void()>>
  ace void if_lane(FuncType true_branch) {
    for (scalar_type s : this->as_array()) {
      if (s != 0) {
        true_branch();
      }
    }
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void()>>
  ace void if_else_lane(FuncType true_branch, FuncType false_branch) {
    for (scalar_type s : this->as_array()) {
      if (s != 0) {
        true_branch();
      } else {
        false_branch();
      }
    }
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void(int)>>
  ace void if_lane_with_index(FuncType true_branch) {
    std::array<scalar_type, lanes> arr = this->as_array();
    for (size_t i = 0; i < lanes; ++i) {
      if (arr[i] != 0) {
        true_branch(i);
      }
    }
  }

  template <typename FuncType1, typename FuncType2>
    requires std::convertible_to<FuncType1, std::function<void(int)>> &&
             std::convertible_to<FuncType2, std::function<void(int)>>
  ace void if_else_lane_with_index(FuncType1 true_branch, FuncType2 false_branch) {
    std::array<scalar_type, lanes> arr = this->as_array();
    for (size_t i = 0; i < lanes; ++i) {
      if (arr[i] != 0) {
        true_branch(i);
      } else {
        false_branch(i);
      }
    }
  }

  ace bool any() {
    for (scalar_type s : this->as_array()) {
      if (s) {
        return true;
      }
    }
    return false;
  }

  ace bool all() {
    for (scalar_type s : this->TestNonzero().as_array()) {
      if (s == 0) {
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
  using lane_type = Lane<vector_type>;

 public:
  ace Lane(vector_type vec, const int lane) : vec_(vec), lane_(lane){};

  ace operator scalar_type() { return neon::get_lane(vec_, lane_); }

  ace Common<vector_type> operator=(scalar_type b) { return neon::set_lane(vec_, lane_, b); }

  ace Common<vector_type> operator+=(scalar_type b) { return neon::set_lane(vec_, lane_, neon::get_lane(vec_, lane_) + b); }
  ace Common<vector_type> operator-=(scalar_type b) { return neon::set_lane(vec_, lane_, neon::get_lane(vec_, lane_) - b); }
  ace Common<vector_type> operator*=(scalar_type b) { return neon::set_lane(vec_, lane_, neon::get_lane(vec_, lane_) * b); }
  ace Common<vector_type> operator/=(scalar_type b) { return neon::set_lane(vec_, lane_, neon::get_lane(vec_, lane_) / b); }

  ace vector_type vec() { return vec_; }
  ace const int lane() { return lane_; }

 private:
  vector_type vec_;
  const int lane_;
};

}  // namespace impl

template <typename scalar_type>
class Neon64 : public impl::Common<typename neon::Vec64<scalar_type>::type> {
  using T = impl::Common<typename neon::Vec64<scalar_type>::type>;

 public:
  using vector_type = neon::Vec64<scalar_type>::type;
  using lane_type = impl::Lane<vector_type>;

  static_assert(neon::is_doubleword_v<vector_type>);

  static constexpr size_t bytes = 8;
  static constexpr size_t lanes = bytes / sizeof(scalar_type);

  ace Neon64() : T(){};
  ace Neon64(vector_type vector) : T(vector){};
  ace Neon64(scalar_type scalar) : T(scalar){};
  ace Neon64(scalar_type const* ptr) : T(ptr){};
  ace Neon64(T&& in) : T(in){};
  ace Neon64(std::initializer_list<scalar_type> value_list) : T(value_list) {};
  ace Neon64(std::span<scalar_type> slice) : T(slice) {};

  ace static Neon64<scalar_type> Create(uint64_t a) { return neon::create<vector_type>(a); }

  ace Neon64<scalar_type> operator=(scalar_type b) { return this->vec_ = neon::duplicate<vector_type>(b); }
  ace Neon64<scalar_type> operator=(impl::Lane<typename neon::Vec64<scalar_type>::type> b) { return this->vec_ = neon::duplicate_lane<vector_type>(b.vec(), b.lane()); }
  ace Neon64<scalar_type> operator=(impl::Lane<typename neon::Vec128<scalar_type>::type> b) {
    constexpr size_t doubleword_lanes = Neon64<scalar_type>::lanes;
    size_t lane = b.lane();
    Neon128<scalar_type> vec = b.vec();
    Neon64<scalar_type> half;
    if (lane >= doubleword_lanes) {
        half = vec.GetHigh();
        lane -= doubleword_lanes;
    } else {
        half = vec.GetLow();
    }
    return this->vec_ = neon::duplicate_lane<vector_type>(half, lane);
  }

  template <typename U>
  requires impl::has_larger_v<scalar_type>
  ace Neon128<U> AddLong(Neon64<scalar_type> b) const { return neon::add_long(this->vec_, b); }

  template <typename U>
  requires impl::has_larger_v<scalar_type>
  ace Neon128<U> MultiplyLong(Neon64<scalar_type> b) const { return neon::multiply_long(this->vec_, b); }

  template <typename U>
  requires impl::has_larger_v<scalar_type>
  ace Neon128<U> MultiplyLong(scalar_type b) const { return neon::multiply_long(this->vec_, b); }

  template <typename U>
  requires impl::has_larger_v<scalar_type>
  ace Neon128<U> MultiplyLong(lane_type b) const { return neon::multiply_long_lane(this->vec_, b.vec(), b.lane()); }

  template <typename U>
  requires (std::is_same_v<vector_type, int16x4_t> || std::is_same_v<vector_type, int32x2_t>)
  ace Neon128<U> MultiplyFixedLong(Neon64<scalar_type> b) const { return neon::multiply_subtract_long(this->vec_, b); }

  template <typename U>
  requires (std::is_same_v<vector_type, int16x4_t> || std::is_same_v<vector_type, int32x2_t>)
  ace Neon128<U> MultiplyFixedLong(scalar_type b) const { return neon::multiply_subtract_long(this->vec_, b); }

  template <typename U>
  requires (std::is_same_v<vector_type, int16x4_t> || std::is_same_v<vector_type, int32x2_t>)
  ace Neon128<U> MultiplyFixedLong(lane_type b) const { return neon::multiply_subtract_long(this->vec_, b.vec(), b.lane()); }

  template <typename U>
  requires impl::has_larger_v<scalar_type>
  ace Neon128<U> SubtractLong(Neon64<scalar_type> b) const { return neon::subtract_long(this->vec_, b); }

  template <typename U>
  requires impl::has_larger_v<scalar_type>
  ace Neon128<U> SubtractAbsLong(Neon64<scalar_type> b) const { return neon::subtract_abs_long(this->vec_, b); }

  template <typename U>
  requires impl::has_larger_v<scalar_type>
  ace Neon128<U> PairwiseAddLong() const { return neon::pairwise_add_long(this->vec_); }

  template <typename U>
  requires impl::has_smaller_v<scalar_type>
  ace Neon128<U> PairwiseAddLong(Neon64<typename impl::NextSmaller<scalar_type>> b) const { return neon::pairwise_add_long(this->vec_, b); }

  template <typename U>
  requires impl::has_larger_v<scalar_type>
  ace Neon128<U> Widen() const { return neon::move_long(this->vec_); }

  ace Neon64<scalar_type> TableLookup(Neon64<scalar_type> idx) { return neon::table_lookup1(this->vec_, idx); }
  ace Neon64<scalar_type> TableExtension(Neon64<scalar_type> b, Neon64<scalar_type> idx) { return neon::table_extension1(this->vec_, b, idx); }

  template <size_t num_tables>
  ace Neon64<scalar_type> TableExtension(std::array<Neon64<scalar_type>, num_tables> b, Neon64<scalar_type> idx) {
    return TableExtension<num_tables>((vector_type*)b.data(), idx);
  }

  template <size_t num_tables>
  ace Neon64<scalar_type> TableExtension(vector_type* b, Neon64<scalar_type> idx) {
    static_assert(num_tables > 1 && num_tables < 5, "Table Extension can only be performed with 1, 2, 3, or 4 tables");

    using multivec_type = impl::MultiVec<vector_type, num_tables>::type;

    multivec_type multivec = *(multivec_type*)b;

    if constexpr (num_tables == 2) {
      return neon::table_extension2(this->vec_, multivec, idx);
    } else if constexpr (num_tables == 3) {
      return neon::table_extension3(this->vec_, multivec, idx);
    } else if constexpr (num_tables == 4) {
      return neon::table_extension4(this->vec_, multivec, idx);
    }
  }

  template <typename U> ace Neon64<U> Convert() { return neon::convert<typename neon::Vec64<U>::type>(this->vec_); }
  template <typename U> ace Neon64<U> Convert(int n) { return neon::convert_n<typename neon::Vec64<U>::type>(this->vec_, n); }

  ace Neon128<scalar_type> CombineWith(Neon64<scalar_type> high) const { return neon::combine(this->vec_, high); }
};

template <typename scalar_type>
class Neon128 : public impl::Common<typename neon::Vec128<scalar_type>::type> {
  using T = impl::Common<typename neon::Vec128<scalar_type>::type>;

 public:
  using vector_type = neon::Vec128<scalar_type>::type;
  using lane_type = impl::Lane<vector_type>;

  static_assert(neon::is_quadword_v<vector_type>);

  static constexpr size_t bytes = 16;
  static constexpr size_t lanes = bytes / sizeof(scalar_type);

  ace Neon128() : T(){};
  ace Neon128(vector_type vector) : T(vector){};
  ace Neon128(scalar_type scalar) : T(scalar){};
  ace Neon128(scalar_type const* ptr) : T(ptr){};
  ace Neon128(T&& in) : T(in){};
  ace Neon128(std::initializer_list<scalar_type> value_list) : T(value_list) {};
  ace Neon128(std::span<scalar_type> slice) : T(slice) {};
  ace Neon128(Neon64<scalar_type> low, Neon64<scalar_type> high) : T(neon::combine(low, high)) {};

  ace static Neon128<scalar_type> Combine(Neon64<scalar_type> low, Neon64<scalar_type> high) { return neon::combine(low, high); }

  ace Neon128<scalar_type> operator=(scalar_type b) { return this->vec_ = neon::duplicate<vector_type>(b); }
  ace Neon128<scalar_type> operator=(impl::Lane<typename neon::Vec64<scalar_type>::type> b) { return this->vec_ = neon::duplicate_lane<vector_type>(b.vec(), b.lane()); }
  ace Neon128<scalar_type> operator=(impl::Lane<typename neon::Vec128<scalar_type>::type> b) {
    constexpr size_t doubleword_lanes = Neon64<scalar_type>::lanes;
    size_t lane = b.lane();
    Neon128<scalar_type> vec = b.vec();
    Neon64<scalar_type> half;
    if (lane >= doubleword_lanes) {
        half = vec.GetHigh();
        lane -= doubleword_lanes;
    } else {
        half = vec.GetLow();
    }
    return this->vec_ = neon::duplicate_lane<vector_type>(half, lane);
  }


  template <typename U>
  requires impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename impl::NextSmaller<scalar_type>::type>
  ace Neon128<scalar_type> MultiplyAddLong(Neon64<U> b, Neon64<U> c) const{ return neon::multiply_add_long(this->vec_, b, c); }

  template <typename U>
  requires impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename impl::NextSmaller<scalar_type>::type>
  ace Neon128<scalar_type> MultiplyAddLong(Neon64<U> b, U c) const { return neon::multiply_add_long(this->vec_, b, c); }

  template <typename U>
  requires impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename impl::NextSmaller<scalar_type>::type>
  ace Neon128<scalar_type> MultiplyAddLong(Neon64<U> b, typename Neon64<U>::lane_type c) const { return neon::multiply_add_long(this->vec_, b, c.vec(), c.lane()); }

  template <typename U>
  requires impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename impl::NextSmaller<scalar_type>::type>
  ace Neon128<scalar_type> MultiplySubtractLong(Neon64<U> b, Neon64<U> c) const { return neon::multiply_subtract_long(this->vec_, b, c); }

  template <typename U>
  requires impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename impl::NextSmaller<scalar_type>::type>
  ace Neon128<scalar_type> MultiplySubtractLong(Neon64<U> b, U c) const { return neon::multiply_subtract_long(this->vec_, b, c); }

  template <typename U>
  requires impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename impl::NextSmaller<scalar_type>::type>
  ace Neon128<scalar_type> MultiplySubtractLong(Neon64<U> b, typename Neon64<U>::lane_type c) const { return neon::multiply_subtract_long(this->vec_, b, c.vec(), c.lane()); }

  template <typename U>
  requires impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename impl::NextSmaller<scalar_type>::type>
  ace Neon64<U> AddNarrow(Neon128<scalar_type> b) { return neon::add_narrow(this->vec_, b); }

  template <typename U>
  requires impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename impl::NextSmaller<scalar_type>::type>
  ace Neon64<U> AddRoundNarrow(Neon128<scalar_type> b) { return neon::add_round_narrow(this->vec_, b); }

  template <typename U>
  requires impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename impl::NextSmaller<scalar_type>::type>
  ace Neon64<U> SubtractNarrow(Neon128<scalar_type> b) { return neon::subtract_narrow(this->vec_, b); }

  template <typename U>
  requires impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename impl::NextSmaller<scalar_type>::type>
  ace Neon64<U> SubtractRoundNarrow(Neon128<scalar_type> b) { return neon::subtract_round_narrow(this->vec_, b); }

  template <size_t n, typename U>
  requires impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename impl::NextSmaller<scalar_type>::type>
  ace Neon64<U> ShiftRightNarrow() { return neon::shift_right_narrow<n>(this->vec_); }

  template <size_t n, typename U>
  requires impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename impl::NextSmaller<scalar_type>::type>
  ace Neon64<U> ShiftRightSaturateNarrow() { return neon::shift_right_saturate_narrow<n>(this->vec_); }

  template <size_t n, typename U>
  requires impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename impl::NextSmaller<scalar_type>::type>
  ace Neon64<U> ShiftRightRoundSaturateNarrow() { return neon::shift_right_round_saturate_narrow<n>(this->vec_); }

  template <size_t n, typename U>
  requires impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename impl::NextSmaller<scalar_type>::type>
  ace Neon64<U> ShiftRightRoundNarrow() { return neon::shift_right_round_narrow<n>(this->vec_); }

  template <typename U>
  requires impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename impl::NextSmaller<scalar_type>::type>
  ace Neon64<U> Narrow(Neon128<scalar_type> b) { return neon::move_narrow(this->vec_); }

  template <typename U>
  requires impl::has_smaller_v<scalar_type> && std::is_same_v<U, typename impl::NextSmaller<scalar_type>::type>
  ace Neon64<U> SaturateNarrow(Neon128<scalar_type> b) { return neon::move_saturate_narrow(this->vec_); }

  ace Neon64<scalar_type> GetHigh() { return neon::get_high(this->vec_); }
  ace Neon64<scalar_type> GetLow() { return neon::get_low(this->vec_); }

  template <typename U> ace Neon128<U> Convert() { return neon::convert<typename neon::Vec128<U>::type>(this->vec_); }
  template <typename U> ace Neon128<U> Convert(int n) { return neon::convert_n<typename neon::Vec128<U>::type>(this->vec_, n); }
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

template <size_t stride, typename scalar_type, typename intrinsic_type>
ace void store_interleaved(scalar_type* ptr, std::array<intrinsic_type, stride> multi_vec) {
  store_interleaved<stride, scalar_type, intrinsic_type>(ptr, multi_vec.data());
}

template <size_t stride, typename scalar_type, typename intrinsic_type>
ace void store_interleaved(scalar_type* ptr, intrinsic_type* multi_vec) {
  static_assert(stride > 1 && stride < 5, "Interleaving Stores can only be performed with a stride of 2, 3, or 4");
  if constexpr (stride == 2) {
    neon::store2(ptr, *(typename impl::MultiVec<intrinsic_type, 2>::type*)multi_vec);
  } else if constexpr (stride == 3) {
    neon::store3(ptr, *(typename impl::MultiVec<intrinsic_type, 3>::type*)multi_vec);
  } else if constexpr (stride == 4) {
    neon::store4(ptr, *(typename impl::MultiVec<intrinsic_type, 4>::type*)multi_vec);
  }
}

template <typename scalar_type, typename intrinsic_type>
ace void store(scalar_type* ptr, intrinsic_type vector) {
  neon::store1(ptr, vector);
}

/**
 * @brief Store a contiguous collection of vectors to a location in memory, potentially with interleaving
 *
 * @tparam stride The interleaving stride: 2, 3, 4
 * @param ptr The location to store to
 * @param vectors The vectors to store.
 * @warning The length of vectors _must_ be a strict multiple of the stride.
 *          This function will attempt to store all vectors possible but WILL NOT STORE THE REMAINDER.
 */
template <size_t stride = 1, typename scalar_type, typename intrinsic_type>
requires std::is_same_v<scalar_type, typename neon::NonVec<intrinsic_type>::type>
ace void store(scalar_type* ptr, std::span<intrinsic_type> vectors) {
  // Best case scenerio: we know both length and stride
  static_assert(0 < stride && stride < 5, "Stores can only be performed with a stride of 1, 2, 3, or 4");
  //assert(vectors.size() >= stride, "You cannot store less vectors than your stride!");
  //assert(vectors.size() % stride == 0, "The number of vectors being stored must be a multiple of the stride!");

  if (stride == 1) {
    size_t tail_size = n % 4;
#pragma unroll
    for (auto v : vectors | std::views::chunk(4)) {
      if (v.size() == 4) {  // 4-element chunks
        using multi_type = impl::MultiVec<intrinsic_type, 4>::type;
        neon::store1_x4(ptr, *(multi_type*)v.begin());
        ptr += (sizeof(intrinsic_type) / sizeof(*ptr)) * 4; // increment output pointer
      } else {
        if (tail_size == 1) {  // 1-element tail
          neon::store1(ptr, v.begin());
        } else if (tail_size == 2) {
          using tail_multi_type = impl::MultiVec<intrinsic_type, 2>::type;
          neon::store1_x2(ptr, *(tail_multi_type*)v.begin());
        } else if (tail_size == 3) {
          using tail_multi_type = impl::MultiVec<intrinsic_type, 3>::type;
          neon::store1_x3(ptr, *(tail_multi_type*)v.begin());
        }
      }
    }
  } else {
#pragma unroll
    for (auto v : vectors | std::views::chunk(stride)) {
      if (v.size() != stride) {
        return;
      }

      if constexpr (stride == 2) {
        store_interleaved<2>(ptr, v.begin());
      } else if constexpr (stride == 3) {
        store_interleaved<3>(ptr, v.begin());
      } else if constexpr (stride == 4) {
        store_interleaved<4>(ptr, v.begin());
      }
      ptr += sizeof(intrinsic_type) / sizeof(*ptr); // increment output pointer
    }
  }
}

/**
 * @brief Store an array of vectors to a location in memory, potentially with interleaving
 *
 * @tparam stride The interleaving stride: 2, 3, 4
 * @param ptr The location to store to
 * @param vectors The vectors to store.
 * @warning The length of vectors _must_ be a strict multiple of the stride.
 *          This function will attempt to store all vectors possible but WILL NOT STORE THE REMAINDER.
 */
template <size_t stride = 1, size_t size, typename scalar_type, typename intrinsic_type>
requires std::is_same_v<scalar_type, typename neon::NonVec<intrinsic_type>::type>
ace void store(scalar_type* ptr, std::array<intrinsic_type, size> vectors) {
  // Best case scenerio: we know both length and stride
  static_assert(0 < stride && stride < 5, "Stores can only be performed with a stride of 1, 2, 3, or 4");
  static_assert(size >= stride, "You cannot store less vectors than your stride!");
  static_assert(size % stride == 0, "The number of vectors being stored must be a multiple of the stride!");

  if constexpr (stride == 1) {
    constexpr size_t tail_size = size % 4;
#pragma unroll
    for (auto v : vectors | std::views::chunk(4)) {
      if (v.size() == 4) {  // 4-element chunks
        using multi_type = impl::MultiVec<intrinsic_type, 4>::type;
        neon::store1_x4(ptr, *(multi_type*)v.begin());
        ptr += (sizeof(intrinsic_type) / sizeof(*ptr)) * 4; // increment output pointer
      } else {
        if constexpr (tail_size == 1) {  // 1-element tail
          neon::store1(ptr, v.begin());
        } else if constexpr (tail_size == 2) {
          using tail_multi_type = impl::MultiVec<intrinsic_type, 2>::type;
          neon::store1_x2(ptr, *(tail_multi_type*)v.begin());
        } else if constexpr (tail_size == 3) {
          using tail_multi_type = impl::MultiVec<intrinsic_type, 3>::type;
          neon::store1_x3(ptr, *(tail_multi_type*)v.begin());
        }
      }
    }
  } else {
#pragma unroll
    for (auto v : vectors | std::views::chunk(stride)) {
      if constexpr (stride == 2) {
        store_interleaved<2>(ptr, v.begin());
      } else if constexpr (stride == 3) {
        store_interleaved<3>(ptr, v.begin());
      } else if constexpr (stride == 4) {
        store_interleaved<4>(ptr, v.begin());
      }
      ptr += sizeof(intrinsic_type) / sizeof(*ptr); // increment output pointer
    }
  }
}


template <int lane, size_t stride, typename scalar_type, typename intrinsic_type>
ace void store_lane_interleaved(scalar_type* ptr, std::array<intrinsic_type, stride> multi_vec) {
  store_lane_interleaved<lane, stride, scalar_type, intrinsic_type>(ptr, multi_vec.data());
}

template <int lane, size_t stride, typename scalar_type, typename intrinsic_type>
ace void store_lane_interleaved(scalar_type* ptr, intrinsic_type* multi_vec) {
  static_assert(stride > 1 && stride < 5, "Interleaving Stores can only be performed with a stride of 2, 3, or 4");
  if constexpr (stride == 2) {
    neon::store2_lane<lane>(ptr, *(typename impl::MultiVec<intrinsic_type, 2>::type*)multi_vec);
  } else if constexpr (stride == 3) {
    neon::store3_lane<lane>(ptr, *(typename impl::MultiVec<intrinsic_type, 3>::type*)multi_vec);
  } else if constexpr (stride == 4) {
    neon::store4_lane<lane>(ptr, *(typename impl::MultiVec<intrinsic_type, 4>::type*)multi_vec);
  }
}

template <typename neon_type>
ace std::array<neon_type, 2> zip(neon_type a, neon_type b) {
  using multivec_type = impl::MultiVec<typename neon_type::vector_type, 2>::type;
  using array_type = std::array<neon_type, 2>;

  // Since we're using a dirty ugly hack of reinterpreting a C array as a std::array,
  // the validity and POD-ness of std::array needs to be verified
  static_assert(std::is_standard_layout_v<array_type>);
  static_assert(std::is_trivial_v<array_type>);
  static_assert(sizeof(multivec_type) == sizeof(array_type),
                "std::array isn't layout-compatible with this NEON multi-vector.");

  return *(array_type*)neon::zip(a, b).val;
}

template <typename neon_type>
ace std::array<neon_type, 2> unzip(neon_type a, neon_type b) {
  using multivec_type = impl::MultiVec<typename neon_type::vector_type, 2>::type;
  using array_type = std::array<neon_type, 2>;

  // Since we're using a dirty ugly hack of reinterpreting a C array as a std::array,
  // the validity and POD-ness of std::array needs to be verified
  static_assert(std::is_standard_layout_v<array_type>);
  static_assert(std::is_trivial_v<array_type>);
  static_assert(sizeof(multivec_type) == sizeof(array_type),
                "std::array isn't layout-compatible with this NEON multi-vector.");

  return *(array_type*)neon::unzip(a, b).val;
}

template <typename neon_type>
ace std::array<neon_type, 2> transpose(neon_type a, neon_type b) {
  using multivec_type = impl::MultiVec<typename neon_type::vector_type, 2>::type;
  using array_type = std::array<neon_type, 2>;

  // Since we're using a dirty ugly hack of reinterpreting a C array as a std::array,
  // the validity and POD-ness of std::array needs to be verified
  static_assert(std::is_standard_layout_v<array_type>);
  static_assert(std::is_trivial_v<array_type>);
  static_assert(sizeof(multivec_type) == sizeof(array_type),
                "std::array isn't layout-compatible with this NEON multi-vector.");

  return *(array_type*)neon::transpose(a, b).val;
}

template <typename T>
ace Neon128<T> combine(Neon64<T> low, Neon64<T> high) { return neon::combine(low, high); }

}  // namespace argon

namespace std {
template <typename T>
struct tuple_size<argon::impl::Common<T>> {
  static constexpr size_t value = argon::impl::Common<T>::lanes;
};

template <typename T>
struct tuple_size<argon::Neon128<T>> {
  static constexpr size_t value = argon::Neon128<T>::lanes;
};

template <typename T>
struct tuple_size<argon::Neon64<T>> {
  static constexpr size_t value = argon::Neon64<T>::lanes;
};

template <size_t Index, typename T>
struct tuple_element<Index, argon::impl::Common<T>> {
  static_assert(Index < argon::impl::Common<T>::lanes);
  using type = argon::impl::Common<T>::lane_type;
};

template <size_t Index, typename T>
struct tuple_element<Index, argon::Neon128<T>> {
  static_assert(Index < argon::Neon128<T>::lanes);
  using type = argon::impl::Lane<typename argon::Neon128<T>::vector_type>;
};

template <size_t Index, typename T>
struct tuple_element<Index, argon::Neon64<T>> {
  static_assert(Index < argon::Neon64<T>::lanes);
  using type = argon::impl::Lane<typename argon::Neon64<T>::vector_type>;
};
}  // namespace std

template <typename scalar_type>
using Argon64 = argon::Neon64<scalar_type>;
template <typename scalar_type>
using Argon128 = argon::Neon128<scalar_type>;

template <neon::is_vector_type V>
ace argon::impl::Neon<V> operator+(typename neon::NonVec<V>::type a, argon::impl::Neon<V> b) {
  return b.Add(a);
}

template <neon::is_vector_type V>
ace argon::impl::Neon<V> operator-(typename neon::NonVec<V>::type a, argon::impl::Neon<V> b) {
  return argon::impl::Neon<V>{a}.Subtract(b);
}

template <neon::is_vector_type V>
ace argon::impl::Neon<V> operator*(typename neon::NonVec<V>::type a, argon::impl::Neon<V> b) {
  return b.Multiply(a);
}

template <neon::is_vector_type V>
ace argon::impl::Neon<V> operator/(typename neon::NonVec<V>::type a, argon::impl::Neon<V> b) {
  return argon::impl::Neon<V>{a}.Divide(b);
}

template <neon::is_vector_type V>
ace argon::impl::Neon<V> operator+(argon::impl::Neon<V> a, typename neon::NonVec<V>::type b) {
  return a.Add(b);
}

template <neon::is_vector_type V>
ace argon::impl::Neon<V> operator-(argon::impl::Neon<V> a, typename neon::NonVec<V>::type b) {
  return a.Subtract(b);
}

template <neon::is_vector_type V>
ace argon::impl::Neon<V> operator*(argon::impl::Neon<V> a, typename neon::NonVec<V>::type b) {
  return a.Multiply(b);
}

template <neon::is_vector_type V>
ace argon::impl::Neon<V> operator/(argon::impl::Neon<V> a, typename neon::NonVec<V>::type b) {
  return a.Divide(b);
}

template <neon::is_vector_type V>
ace argon::impl::Neon<V> operator+(V a, argon::impl::Neon<V> b) {
  return argon::impl::Neon<V>{a}.Add(b);
}

template <neon::is_vector_type V>
ace argon::impl::Neon<V> operator-(V a, argon::impl::Neon<V> b) {
  return argon::impl::Neon<V>{a}.Subtract(b);
}

template <neon::is_vector_type V>
ace argon::impl::Neon<V> operator*(V a, argon::impl::Neon<V> b) {
  return argon::impl::Neon<V>{a}.Multiply(a);
}

template <neon::is_vector_type V>
ace argon::impl::Neon<V> operator/(V a, argon::impl::Neon<V> b) {
  return argon::impl::Neon<V>{a}.Divide(b);
}
#undef ace
