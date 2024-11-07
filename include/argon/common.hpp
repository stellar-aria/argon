#pragma once
#include <array>
#include <functional>
#include <type_traits>
#include "arm_simd/helpers.hpp"
#include "features.h"
#include "helpers.hpp"
#include "helpers/multivec.hpp"
#include "helpers/result.hpp"

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

template <typename T>
class Argon64;
template <typename T>
class Argon128;

namespace argon::impl {

template <typename T>
struct Neon;

template <simd::is_vector_type T>
  requires simd::is_quadword<T>
struct Neon<T> {
  using type = Argon128<typename simd::NonVec<T>::type>;
};

#if ARGON_HAS_DWORD
template <simd::is_vector_type T>
  requires simd::is_doubleword<T>
struct Neon<T> {
  using type = Argon64<typename simd::NonVec<T>::type>;
};
#endif

template <typename T>
using Neon_t = typename Neon<T>::type;

template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template <typename vector_type>
class Lane;

template <typename vector_type>
class Common {
 public:
  using scalar_type = simd::NonVec<vector_type>::type;
  using lane_type = Lane<vector_type>;
  using result_type = typename Result<vector_type>::type;
  using neon_result_type = typename Neon<result_type>::type;
  using neon_type = typename Neon<vector_type>::type;

  static constexpr size_t lanes = (simd::is_quadword_v<vector_type> ? 16 : 8) / sizeof(scalar_type);

  constexpr Common() : vec_{0} {};
  constexpr Common(vector_type vector) : vec_(vector) {};
  ace Common(scalar_type scalar) : vec_(FromScalar(scalar)) {};
  ace Common(scalar_type const* ptr) : vec_(Load(ptr)) {};
  ace Common(std::span<scalar_type> slice) : vec_(Load(slice.data())) {};

  ace static neon_type FromScalar(scalar_type scalar) {
#if ARGON_HAS_DWORD
    return simd::duplicate<vector_type>(scalar);
#else
    return simd::duplicate(scalar);
#endif
  }

  ace neon_type operator=(scalar_type b) { return vec_ = FromScalar(b); }

#if ARGON_HAS_DWORD
  ace neon_type operator=(Lane<simd::Vec64_t<scalar_type>> b) {
    return this->vec_ = simd::duplicate_lane<vector_type>(b.vec(), b.lane());
  }

  ace neon_type operator=(Lane<simd::Vec128_t<scalar_type>> b) {
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
#endif

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

  ace lane_type GetLane(const int i) { return simd::get_lane(vec_, i); }

  ace neon_type ShiftRight(const int i) const { return simd::shift_right(vec_, i); }
  ace neon_type ShiftLeft(const int i) const { return simd::shift_left(vec_, i); }

  ace neon_type Negate() const { return simd::negate(vec_); }

  ace neon_type Add(neon_type b) const { return simd::add(vec_, b); }
  ace neon_type AddHalve(neon_type b) const { return simd::add_halve(vec_, b); }
  ace neon_type AddHalveRound(neon_type b) const { return simd::add_halve_round(vec_, b); }
  ace neon_type AddSaturate(neon_type b) const { return simd::add_saturate(vec_, b); }

  ace neon_type Subtract(neon_type b) const { return simd::subtract(vec_, b); }
  ace neon_type SubtractHalve(neon_type b) const { return simd::subtract_halve(vec_, b); }
  ace neon_type SubtractSaturate(neon_type b) const { return simd::subtract_saturate(vec_, b); }
  ace neon_type SubtractAbs(neon_type b) const { return simd::subtract_abs(vec_, b); }
  ace neon_type SubtractAbsAdd(neon_type b, neon_type c) const { return simd::subtract_abs_add(vec_, b, c); }

  /** a * b */
  ace neon_type Multiply(neon_type b) const { return simd::multiply(vec_, b); }
  ace neon_type Multiply(scalar_type b) const { return simd::multiply(vec_, b); }
  ace neon_type Multiply(lane_type b) const { return simd::multiply_lane(vec_, b.vec(), b.lane()); }

  /** a + (b * c) */
  ace neon_type MultiplyAdd(neon_type b, neon_type c) const { return simd::multiply_add(vec_, b, c); }
  ace neon_type MultiplyAdd(neon_type b, scalar_type c) const { return simd::multiply_add(vec_, b, c); }
  ace neon_type MultiplyAdd(neon_type b, lane_type c) const {
    return simd::multiply_add_lane(vec_, b, c.vec(), c.lane());
  }

  /** a - (b * c) */
  ace neon_type MultiplySubtract(neon_type b, neon_type c) const { return simd::multiply_subtract(vec_, b, c); }
  ace neon_type MultiplySubtract(neon_type b, scalar_type c) const { return simd::multiply_subtract(vec_, b, c); }
  ace neon_type MultiplySubtract(neon_type b, lane_type c) const {
    return simd::multiply_subtract(vec_, b, c.vec(), c.lane());
  }

  /**
   * Multiply two fixed-point vectors, returning a fixed-point product
   * This is equivalent to (a * b) >> 31
   */
  ace neon_type MultiplyFixedPoint(neon_type v) const { return simd::multiply_double_saturate_high(vec_, v); }

  /**
   * Multiply a fixed-point vector by a scalar, returning a fixed-point product
   * This is equivalent to (a * b) >> 31
   */
  ace neon_type MultiplyFixedPoint(scalar_type s) const { return simd::multiply_double_saturate_high(vec_, s); }

  /**
   * Multiply two fixed-point vectors and round, returning a fixed-point product
   * This is equivalent to round(a * b) >> 31
   */
  ace neon_type MultiplyFixedPointRound(neon_type v) const {
    return simd::multiply_double_round_saturate_high(vec_, v);
  }

  /**
   * Multiply a fixed-point vector by a scalar and round, returning a fixed-point product
   * This is equivalent to round(a * b) >> 31
   */
  ace neon_type MultiplyFixedPointRound(scalar_type s) const {
    return simd::multiply_double_round_saturate_high(vec_, s);
  }

  ace neon_type Divide(neon_type b) const
    requires std::floating_point<scalar_type>
  {
#ifdef __aarch64__
    return simd::divide(vec_, b);
#else
    return this->map2(b, [](scalar_type lane1, scalar_type lane2) { return lane1 / lane2; });
#endif
  }

  ace neon_type Max(neon_type b) const { return simd::max(vec_, b); }
  ace neon_type Min(neon_type b) const { return simd::min(vec_, b); }

  ace neon_result_type Equal(neon_type b) const { return simd::equal(vec_, b); }
  ace neon_result_type GreaterThanOrEqual(neon_type b) const { return simd::greater_than_or_equal(vec_, b); }
  ace neon_result_type LessThanOrEqual(neon_type b) const { return simd::less_than_or_equal(vec_, b); }
  ace neon_result_type GreaterThan(neon_type b) const { return simd::greater_than(vec_, b); }
  ace neon_result_type LessThan(neon_type b) const { return simd::less_than(vec_, b); }

  template <typename signed_vector>
    requires(std::is_integral_v<scalar_type> &&
             std::is_same_v<signed_vector, typename Neon<simd::make_signed_t<vector_type>>::type>)
  ace neon_type ShiftLeft(signed_vector b) const
    requires std::is_integral_v<scalar_type>
  {
    return simd::shift_left(vec_, b);
  }

  template <typename signed_vector>
    requires(std::is_integral_v<scalar_type> &&
             std::is_same_v<signed_vector, typename Neon<simd::make_signed_t<vector_type>>::type>)
  ace neon_type ShiftLeftSaturate(signed_vector b) const {
    return simd::shift_left_saturate(vec_, b);
  }

  ace neon_type ShiftLeftRound(neon_type b) const { return simd::shift_left_round(vec_, b); }
  ace neon_type ShiftLeftRoundSaturate(neon_type b) const { return simd::shift_left_round_saturate(vec_, b); }

  template <int n>
  ace neon_type ShiftLeftSaturate() const {
    return simd::shift_left_saturate<n>(vec_);
  }
  template <int n>
  ace neon_type ShiftLeftInsert(neon_type b) const {
    return simd::shift_left_insert<n>(vec_, b);
  }

  template <int n>
  ace neon_type ShiftRight() const {
    return simd::shift_right<n>(vec_);
  }
  template <int n>
  ace neon_type ShiftRightRound() const {
    return simd::shift_right_round<n>(vec_);
  }
  template <int n>
  ace neon_type ShiftRightAccumulate(neon_type b) const {
    return simd::shift_right_accumulate<n>(vec_, b);
  }
  template <int n>
  ace neon_type ShiftRightAccumulateRound(neon_type b) const {
    return simd::shift_right_accumulate_round<n>(vec_, b);
  }
  template <int n>
  ace neon_type ShiftRightInsert(neon_type b) const {
    return simd::shift_right_insert<n>(vec_, b);
  }

  ace static neon_type Load(scalar_type const* ptr) { return simd::load1<vector_type>(ptr); }

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
      return *(array_type*)(simd::load2<multivec_type>(ptr).val);
    } else if constexpr (stride == 3) {
      return *(array_type*)(simd::load3<multivec_type>(ptr).val);
    } else if constexpr (stride == 4) {
      return *(array_type*)(simd::load4<multivec_type>(ptr).val);
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

  ace void StoreTo(scalar_type* ptr) const { simd::store1(ptr, vec_); }

  template <int lane>
  ace void StoreLaneTo(scalar_type* ptr) {
    simd::store1_lane<lane>(ptr, vec_);
  }

  /// Pairwise ops

  ace neon_type PairwiseAdd(neon_type b) const { return simd::pairwise_add(vec_, b); }
  ace neon_type PairwiseMax(neon_type b) const { return simd::pairwise_max(vec_, b); }
  ace neon_type PairwiseMin(neon_type b) const { return simd::pairwise_min(vec_, b); }

  /// Bitwise ops

  ace neon_type BitwiseNot() const { return simd::bitwise_not(vec_); }
  ace neon_type BitwiseAnd(neon_type b) const { return simd::bitwise_and(vec_, b); }
  ace neon_type BitwiseOr(neon_type b) const { return simd::bitwise_or(vec_, b); }
  ace neon_type BitwiseXor(neon_type b) const { return simd::bitwise_xor(vec_, b); }
  ace neon_type BitwiseOrNot(neon_type b) const { return simd::bitwise_or_not(vec_, b); }
  ace neon_type BitwiseClear(neon_type b) const { return simd::bitwise_clear(vec_, b); }
  ace neon_type BitwiseSelect(neon_type b, neon_type c) const { return simd::bitwise_select(vec_, b, c); }

  /// Ands the current vector with the given vector, then checks if nonzero.
  /// If so, fills the lane with all ones
  ace neon_type CompareTestNonzero(neon_type b) const { return simd::compare_test_nonzero(vec_, b); }
  ace neon_type TestNonzero() const { return simd::compare_test_nonzero(vec_, neon_type{1}); }

  template <typename signed_vector>
    requires(std::is_integral_v<scalar_type> &&
             std::is_same_v<signed_vector, typename Neon<simd::make_signed_t<vector_type>>::type>)
  ace signed_vector CountLeadingSignBits() const {
    return simd::count_leading_sign_bits(vec_);
  }

  ace neon_type CountLeadingZeroBits() const { return simd::count_leading_zero_bits(vec_); }
  ace neon_type CountActiveBits() const { return simd::count_active_bits(vec_); }

  /// Extract n elements from the lower end of this vector, and the remaining elements from the higher end of the
  /// operand, combining them into the result vector.
  template <int n>
  ace neon_type Extract(neon_type b) const {
    return simd::extract<n>(vec_, b);
  }

  ace neon_type Reverse64bit() const { return simd::reverse_64bit(vec_); }
  ace neon_type Reverse32bit() const { return simd::reverse_32bit(vec_); }
  ace neon_type Reverse16bit() const { return simd::reverse_16bit(vec_); }

  ace std::array<neon_type, 2> ZipWith(neon_type b) const {
    using multivec_type = MultiVec<vector_type, 2>::type;
    using array_type = std::array<neon_type, 2>;

    // Since we're using a dirty ugly hack of reinterpreting a C array as a std::array,
    // the validity and POD-ness of std::array needs to be verified
    static_assert(std::is_standard_layout_v<array_type>);
    static_assert(std::is_trivial_v<array_type>);
    static_assert(sizeof(multivec_type) == sizeof(array_type),
                  "std::array isn't layout-compatible with this NEON multi-vector.");

    return *(array_type*)simd::zip(vec_, b).val;
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

    return *(array_type*)simd::unzip(vec_, b).val;
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

    return *(array_type*)simd::transpose(vec_, b).val;
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

  template <std::size_t Index>
  std::tuple_element_t<Index, neon_type> get() {
    return Lane{vec_, Index};
  }

 protected:
  vector_type vec_;
};

template <typename vector_type>
class Lane {
  using scalar_type = simd::NonVec<vector_type>::type;
  using lane_type = Lane<vector_type>;

 public:
  ace Lane(vector_type vec, const int lane) : vec_(vec), lane_(lane) {};

  ace operator scalar_type() { return simd::get_lane(vec_, lane_); }

  ace Common<vector_type> operator=(scalar_type b) { return simd::set_lane(vec_, lane_, b); }

  ace Common<vector_type> operator+=(scalar_type b) {
    return simd::set_lane(vec_, lane_, simd::get_lane(vec_, lane_) + b);
  }
  ace Common<vector_type> operator-=(scalar_type b) {
    return simd::set_lane(vec_, lane_, simd::get_lane(vec_, lane_) - b);
  }
  ace Common<vector_type> operator*=(scalar_type b) {
    return simd::set_lane(vec_, lane_, simd::get_lane(vec_, lane_) * b);
  }
  ace Common<vector_type> operator/=(scalar_type b) {
    return simd::set_lane(vec_, lane_, simd::get_lane(vec_, lane_) / b);
  }

  ace vector_type vec() { return vec_; }
  ace const int lane() { return lane_; }

 private:
  vector_type vec_;
  const int lane_;
};

}  // namespace argon::impl

#undef ace
