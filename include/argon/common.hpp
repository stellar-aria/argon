#pragma once
#include <array>
#include <functional>
#include <span>
#include <type_traits>
#include "arm_simd/helpers.hpp"
#include "arm_simd/helpers/vec64.hpp"
#include "features.h"
#include "helpers.hpp"
#include "helpers/multivec.hpp"
#include "helpers/result.hpp"
#include "vectorize.hpp"

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
class ArgonHalf;
template <typename T>
class Argon;

namespace argon::impl {

template <typename T>
struct ArgonFor;

template <simd::is_vector_type T>
  requires simd::is_quadword<T>
struct ArgonFor<T> {
  using type = Argon<typename simd::NonVec<T>::type>;
};

#if ARGON_HAS_DWORD
template <simd::is_vector_type T>
  requires simd::is_doubleword<T>
struct ArgonFor<T> {
  using type = ArgonHalf<typename simd::NonVec<T>::type>;
};
#endif

template <typename T>
using ArgonFor_t = typename ArgonFor<T>::type;

template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template <typename T, typename... Ts>
inline constexpr bool is_one_of = std::disjunction_v<std::is_same<T, Ts>...>;

template <typename vector_type>
class Lane;

template <typename vector_type>
class Common {
 public:
  using scalar_type = simd::NonVec_t<vector_type>;
#if defined(__ARM_NEON) && !defined(__aarch64__)  // ARMv7
  using lane_type = Lane<neon::Vec64_t<scalar_type>>;
#else
  using lane_type = Lane<vector_type>;
#endif
  using result_type = Result_t<vector_type>;
  using argon_result_type = ArgonFor_t<result_type>;
  using argon_type = ArgonFor_t<vector_type>;

  static constexpr size_t lanes = (simd::is_quadword_v<vector_type> ? 16 : 8) / sizeof(scalar_type);

  constexpr Common() : vec_{0} {};
  constexpr Common(vector_type vector) : vec_(vector) {};
  ace Common(scalar_type scalar) : vec_(FromScalar(scalar)) {};
  ace Common(scalar_type const* ptr) : vec_(Load(ptr)) {};
  ace Common(std::span<scalar_type> slice) : vec_(Load(slice.data())) {};

  template <simd::is_vector_type intrinsic_type>
    requires std::is_same_v<scalar_type, simd::NonVec_t<intrinsic_type>>
  ace Common(argon::impl::Lane<intrinsic_type> lane) : vec_(FromLane(lane)) {};

  struct vectorize {
    static constexpr size_t step = lanes;
    static constexpr size_t main_size(size_t size) { return size & ~(lanes - 1); }
    static constexpr size_t tail_start(size_t size) { return size & ~(lanes - 1); }

    static constexpr ::argon::vectorize::main<vector_type> main(scalar_type* start, scalar_type* end) {
      return ::argon::vectorize::main<vector_type>{start, end};
    }

    static constexpr ::argon::vectorize::main<vector_type> main(std::span<scalar_type> span) {
      return ::argon::vectorize::main<vector_type>{span};
    }

    static constexpr ::argon::vectorize::main<vector_type> main(scalar_type* start, size_t size) {
      return ::argon::vectorize::main<vector_type>{start, size};
    }

    static constexpr ::argon::vectorize::tail<vector_type> tail(scalar_type* start, scalar_type* end) {
      return ::argon::vectorize::tail<vector_type>{start, end};
    }

    static constexpr ::argon::vectorize::tail<vector_type> tail(std::span<scalar_type> span) {
      return ::argon::vectorize::tail<vector_type>{span};
    }

    static constexpr ::argon::vectorize::tail<vector_type> tail(scalar_type* start, size_t size) {
      return ::argon::vectorize::tail<vector_type>{start, size};
    }
  };

  ace static argon_type FromScalar(scalar_type* ptr) { return simd::load1_duplicate(ptr); }

  ace static argon_type FromScalar(scalar_type scalar) {
#if ARGON_HAS_DWORD
    return simd::duplicate<vector_type>(scalar);
#else
    return simd::duplicate(scalar);
#endif
  }

  template <simd::is_vector_type intrinsic_type>
  ace static argon_type FromLane(argon::impl::Lane<intrinsic_type> lane)
    requires simd::is_quadword<vector_type>
  {
    return simd::duplicate_lane_quad(lane.vec(), lane.lane());
  }

#if ARGON_HAS_DWORD
  template <simd::is_vector_type intrinsic_type>
  ace static argon_type FromLane(argon::impl::Lane<intrinsic_type> lane)
    requires simd::is_doubleword<vector_type>
  {
    return simd::duplicate_lane(lane.vec(), lane.lane());
  }
#endif

  ace argon_type operator-() const { return Negate(); }

  ace argon_type operator+(argon_type b) const { return Add(b); }
  ace argon_type operator-(argon_type b) const { return Subtract(b); }
  ace argon_type operator*(argon_type b) const { return Multiply(b); }
  ace argon_type operator/(argon_type b) const { return Divide(b); }

  ace argon_result_type operator==(argon_type b) const { return Equal(b); }
  ace argon_result_type operator<(argon_type b) const { return LessThan(b); }
  ace argon_result_type operator>(argon_type b) const { return GreaterThan(b); }
  ace argon_result_type operator<=(argon_type b) const { return LessThanOrEqual(b); }
  ace argon_result_type operator>=(argon_type b) const { return GreaterThanOrEqual(b); }

  ace argon_type operator++() const { return Add(1); }
  ace argon_type operator--() const { return Subtract(1); }

  ace argon_type operator&(argon_type b) const { return BitwiseAnd(b); }
  ace argon_type operator|(argon_type b) const { return BitwiseOr(b); }
  ace argon_type operator^(argon_type b) const { return BitwiseXor(b); }
  ace argon_type operator~() const { return BitwiseNot(); }

  ace const lane_type operator[](const int i) const { return lane_type{vec_, i}; }
  ace lane_type operator[](const int i) { return lane_type{vec_, i}; }

  ace argon_type operator>>(const int i) const { return ShiftRight(i); }
  ace argon_type operator<<(const int i) const { return ShiftLeft(i); }

  [[gnu::always_inline]] constexpr operator vector_type() const { return vec_; }

  ace std::array<scalar_type, lanes> as_array() {
    std::array<scalar_type, lanes> out;
    StoreTo(out.data());
    return out;
  }

  ace vector_type vec() const { return vec_; }

  ace scalar_type GetLane(const int i) { return simd::get_lane(vec_, i); }

  ace argon_type ShiftRight(const int i) const { return simd::shift_right(vec_, i); }
  ace argon_type ShiftLeft(const int i) const { return simd::shift_left(vec_, i); }

  ace argon_type Negate() const { return simd::negate(vec_); }

  ace argon_type Add(argon_type b) const { return simd::add(vec_, b); }
  ace argon_type AddHalve(argon_type b) const { return simd::add_halve(vec_, b); }
  ace argon_type AddHalveRound(argon_type b) const { return simd::add_halve_round(vec_, b); }
  ace argon_type AddSaturate(argon_type b) const { return simd::add_saturate(vec_, b); }

  ace argon_type Subtract(argon_type b) const { return simd::subtract(vec_, b); }
  ace argon_type SubtractHalve(argon_type b) const { return simd::subtract_halve(vec_, b); }
  ace argon_type SubtractSaturate(argon_type b) const { return simd::subtract_saturate(vec_, b); }
  ace argon_type SubtractAbs(argon_type b) const { return simd::subtract_absolute(vec_, b); }
  ace argon_type SubtractAbsAdd(argon_type b, argon_type c) const { return simd::subtract_absolute_add(vec_, b, c); }

  /** a * b */
  ace argon_type Multiply(argon_type b) const { return simd::multiply(vec_, b); }
  ace argon_type Multiply(scalar_type b) const { return simd::multiply(vec_, b); }
  ace argon_type Multiply(lane_type b) const { return simd::multiply_lane(vec_, b.vec(), b.lane()); }

  /** a + (b * c) */
  ace argon_type MultiplyAdd(argon_type b, argon_type c) const { return simd::multiply_add(vec_, b, c); }
  ace argon_type MultiplyAdd(argon_type b, scalar_type c) const { return simd::multiply_add(vec_, b, c); }
  ace argon_type MultiplyAdd(argon_type b, lane_type c) const {
    return simd::multiply_add_lane(vec_, b.vec(), c.vec(), c.lane());
  }

  /** a - (b * c) */
  ace argon_type MultiplySubtract(argon_type b, argon_type c) const { return simd::multiply_subtract(vec_, b, c); }
  ace argon_type MultiplySubtract(argon_type b, scalar_type c) const { return simd::multiply_subtract(vec_, b, c); }
  ace argon_type MultiplySubtract(argon_type b, lane_type c) const {
    return simd::multiply_subtract_lane(vec_, b.vec(), c.vec(), c.lane());
  }

  /**
   * Multiply two fixed-point vectors, returning a fixed-point product
   * This is equivalent to (a * b) >> 31
   */
  ace argon_type MultiplyFixedPoint(argon_type v) const { return simd::multiply_double_saturate_high(vec_, v); }
  ace argon_type MultiplyFixedPoint(scalar_type s) const { return simd::multiply_double_saturate_high(vec_, s); }
  ace argon_type MultiplyFixedPoint(lane_type l) const {
    return simd::multiply_double_saturate_high_lane(vec_, l.vec(), l.lane());
  }

  /**
   * Multiply two fixed-point vectors, returning a fixed-point product
   * This is equivalent to round(a * b) >> 31
   */
  ace argon_type MultiplyRoundFixedPoint(argon_type v) const {
    return simd::multiply_double_round_saturate_high(vec_, v);
  }
  ace argon_type MultiplyRoundFixedPoint(scalar_type s) const {
    return simd::multiply_double_round_saturate_high(vec_, s);
  }
  ace argon_type MultiplyRoundFixedPoint(lane_type l) const {
    return simd::multiply_double_round_saturate_high_lane(vec_, l.vec(), l.lane());
  }

  /**
   * Multiply-add three fixed-point vectors, returning a fixed-point sum
   * This is equivalent to a + ((b * c) >> 31)
   */
  template <typename arg_type>
    requires(is_one_of<arg_type, argon_type, scalar_type, lane_type> || std::is_convertible_v<arg_type, argon_type> ||
             std::is_convertible_v<arg_type, scalar_type>)
  ace argon_type MultiplyAddFixedPoint(argon_type b, arg_type c) const {
    return Add(b.MultiplyFixedPoint(c));
  }

  /**
   * Multiply-round-add three fixed-point vectors, returning a fixed-point sum
   * This is equivalent to a + (rnd(b * c) >> 31)
   */
  template <typename arg_type>
    requires(is_one_of<arg_type, argon_type, scalar_type, lane_type> || std::is_convertible_v<arg_type, argon_type> ||
             std::is_convertible_v<arg_type, scalar_type>)
  ace argon_type MultiplyRoundAddFixedPoint(argon_type b, arg_type c) const {
    return Add(b.MultiplyRoundFixedPoint(c));
  }

  ace argon_type Divide(argon_type b) const
    requires std::floating_point<scalar_type>
  {
#ifdef __aarch64__
    return simd::divide(vec_, b);
#else
    return this->map2(b, [](scalar_type lane1, scalar_type lane2) { return lane1 / lane2; });
#endif
  }

  ace argon_type Max(argon_type b) const { return simd::max(vec_, b); }
  ace argon_type Min(argon_type b) const { return simd::min(vec_, b); }

  ace argon_result_type Equal(argon_type b) const { return simd::equal(vec_, b); }
  ace argon_result_type GreaterThanOrEqual(argon_type b) const { return simd::greater_than_or_equal(vec_, b); }
  ace argon_result_type LessThanOrEqual(argon_type b) const { return simd::less_than_or_equal(vec_, b); }
  ace argon_result_type GreaterThan(argon_type b) const { return simd::greater_than(vec_, b); }
  ace argon_result_type LessThan(argon_type b) const { return simd::less_than(vec_, b); }

  template <typename signed_vector>
    requires(std::is_integral_v<scalar_type> &&
             std::is_same_v<signed_vector, typename ArgonFor<simd::make_signed_t<vector_type>>::type>)
  ace argon_type ShiftLeft(signed_vector b) const
    requires std::is_integral_v<scalar_type>
  {
    return simd::shift_left(vec_, b);
  }

  template <typename signed_vector>
    requires(std::is_integral_v<scalar_type> &&
             std::is_same_v<signed_vector, typename ArgonFor<simd::make_signed_t<vector_type>>::type>)
  ace argon_type ShiftLeftSaturate(signed_vector b) const {
    return simd::shift_left_saturate(vec_, b);
  }

  ace argon_type ShiftLeftRound(argon_type b) const { return simd::shift_left_round(vec_, b); }
  ace argon_type ShiftLeftRoundSaturate(argon_type b) const { return simd::shift_left_round_saturate(vec_, b); }

  template <int n>
  ace argon_type ShiftLeftSaturate() const {
    return simd::shift_left_saturate<n>(vec_);
  }
  template <int n>
  ace argon_type ShiftLeftInsert(argon_type b) const {
    return simd::shift_left_insert<n>(vec_, b);
  }

  template <int n>
  ace argon_type ShiftRight() const {
    return simd::shift_right<n>(vec_);
  }
  template <int n>
  ace argon_type ShiftRightRound() const {
    return simd::shift_right_round<n>(vec_);
  }
  template <int n>
  ace argon_type ShiftRightAccumulate(argon_type b) const {
    return simd::shift_right_accumulate<n>(vec_, b);
  }
  template <int n>
  ace argon_type ShiftRightAccumulateRound(argon_type b) const {
    return simd::shift_right_accumulate_round<n>(vec_, b);
  }
  template <int n>
  ace argon_type ShiftRightInsert(argon_type b) const {
    return simd::shift_right_insert<n>(vec_, b);
  }

  ace static argon_type Load(scalar_type const* ptr) { return simd::load1<vector_type>(ptr); }
  ace static argon_type LoadCopy(scalar_type const* ptr) { return simd::load1_duplicate(ptr); }

  template <size_t lane>
  ace argon_type LoadToLane(scalar_type const* ptr) {
    return simd::load1_lane<lane>(ptr, vec_);
  }

  template <size_t stride>
  ace static std::array<argon_type, stride> LoadCopyInterleaved(scalar_type const* ptr) {
    static_assert(stride > 1 && stride < 5,
                  "De-interleaving LoadCopy can only be performed with a stride of 2, 3, or 4");
    using multivec_type = MultiVec<vector_type, stride>::type;
    using array_type = std::array<argon_type, stride>;

    // Since we're using a dirty ugly hack of reinterpreting a C array as a std::array,
    // the validity and POD-ness of std::array needs to be verified
    static_assert(std::is_standard_layout_v<array_type>);
    static_assert(std::is_trivial_v<array_type>);
    static_assert(sizeof(multivec_type) == sizeof(array_type),
                  "std::array isn't layout-compatible with this NEON multi-vector.");

    if constexpr (stride == 2) {
      return *(array_type*)(&simd::load2_duplicate<multivec_type>(ptr).val);
    } else if constexpr (stride == 3) {
      return *(array_type*)(&simd::load3_duplicate<multivec_type>(ptr).val);
    } else if constexpr (stride == 4) {
      return *(array_type*)(&simd::load4_duplicate<multivec_type>(ptr).val);
    }
  }

  template <size_t stride>
  ace static std::array<argon_type, stride> LoadInterleaved(scalar_type const* ptr) {
    static_assert(stride > 1 && stride < 5, "De-interleaving Loads can only be performed with a stride of 2, 3, or 4");
    using multivec_type = MultiVec_t<vector_type, stride>;
    using array_type = std::array<argon_type, stride>;

    // Since we're using a dirty ugly hack of reinterpreting a C array as a std::array,
    // the validity and POD-ness of std::array needs to be verified
    static_assert(std::is_standard_layout_v<array_type>);
    static_assert(std::is_trivial_v<array_type>);
    static_assert(sizeof(multivec_type) == sizeof(array_type),
                  "std::array isn't layout-compatible with this NEON multi-vector.");

    if constexpr (stride == 2) {
      return *(array_type*)(&simd::load2<multivec_type>(ptr).val);
    } else if constexpr (stride == 3) {
      return *(array_type*)(&simd::load3<multivec_type>(ptr).val);
    } else if constexpr (stride == 4) {
      return *(array_type*)(&simd::load4<multivec_type>(ptr).val);
    }
  }

  template <size_t lane, size_t stride>
  ace static std::array<argon_type, stride> LoadInterleavedToLane(MultiVec_t<vector_type, stride> multi,
                                                                   scalar_type const* ptr) {
    using array_type = std::array<argon_type, stride>;

    // Since we're using a dirty ugly hack of reinterpreting a C array as a std::array,
    // the validity and POD-ness of std::array needs to be verified
    static_assert(std::is_standard_layout_v<array_type>);
    static_assert(std::is_trivial_v<array_type>);
    static_assert(sizeof(MultiVec_t<vector_type, stride>) == sizeof(array_type),
                  "std::array isn't layout-compatible with this NEON multi-vector.");

    if constexpr (stride == 2) {
      if constexpr (simd::is_quadword_v<vector_type>) {
        return *(array_type*)(&simd::load2_lane_quad<lane>(ptr, multi).val);
      } else {
        return *(array_type*)(&simd::load2_lane<lane>(ptr, multi).val);
      }
    } else if constexpr (stride == 3) {
      if constexpr (simd::is_quadword_v<vector_type>) {
        return *(array_type*)(&simd::load3_lane_quad<lane>(ptr, multi).val);
      } else {
        return *(array_type*)(&simd::load3_lane<lane>(ptr, multi).val);
      }
    } else if constexpr (stride == 4) {
      if constexpr (simd::is_quadword_v<vector_type>) {
        return *(array_type*)(&simd::load4_lane_quad<lane>(ptr, multi).val);
      } else {
        return *(array_type*)(&simd::load4_lane<lane>(ptr, multi).val);
      }
    }
  }

  template <size_t lane, size_t stride>
  ace static std::array<argon_type, stride> LoadInterleavedToLane(std::array<vector_type, stride> multi,
                                                                   scalar_type const* ptr) {
    using multivec_type = MultiVec_t<vector_type, stride>;
    return LoadInterleavedToLane(*(multivec_type*)(multi.data()));
  }

  /**
   * @brief Load n vectors from a single contiguous set of memory.
   *
   * @tparam n The number of vectors to load
   * @param ptr The pointer to the location in memory to load from
   * @return std::array An array of NEON vectors.
   */
  template <size_t n>
  ace static std::array<argon_type, n> LoadMulti(scalar_type const* ptr) {
    std::array<argon_type, n> out;
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

  ace argon_type PairwiseAdd(argon_type b) const { return simd::pairwise_add(vec_, b); }
  ace argon_type PairwiseMax(argon_type b) const { return simd::pairwise_max(vec_, b); }
  ace argon_type PairwiseMin(argon_type b) const { return simd::pairwise_min(vec_, b); }

  /// Bitwise ops

  ace argon_type BitwiseNot() const { return simd::bitwise_not(vec_); }
  ace argon_type BitwiseAnd(argon_type b) const { return simd::bitwise_and(vec_, b); }
  ace argon_type BitwiseOr(argon_type b) const { return simd::bitwise_or(vec_, b); }
  ace argon_type BitwiseXor(argon_type b) const { return simd::bitwise_xor(vec_, b); }
  ace argon_type BitwiseOrNot(argon_type b) const { return simd::bitwise_or_not(vec_, b); }
  ace argon_type BitwiseClear(argon_type b) const { return simd::bitwise_clear(vec_, b); }
  ace argon_type BitwiseSelect(argon_type b, argon_type c) const { return simd::bitwise_select(vec_, b, c); }

  /// Ands the current vector with the given vector, then checks if nonzero.
  /// If so, fills the lane with all ones
  ace argon_type CompareTestNonzero(argon_type b) const { return simd::compare_test_nonzero(vec_, b); }
  ace argon_type TestNonzero() const { return simd::compare_test_nonzero(vec_, argon_type{1}); }

  template <typename signed_vector>
    requires(std::is_integral_v<scalar_type> &&
             std::is_same_v<signed_vector, typename ArgonFor<simd::make_signed_t<vector_type>>::type>)
  ace signed_vector CountLeadingSignBits() const {
    return simd::count_leading_sign_bits(vec_);
  }

  ace argon_type CountLeadingZeroBits() const { return simd::count_leading_zero_bits(vec_); }
  ace argon_type CountActiveBits() const { return simd::count_active_bits(vec_); }

  /// Extract n elements from the lower end of the operand, and the remaining elements from the top end of this vector,
  /// combining them into the result vector.
  template <int n>
  ace argon_type Extract(argon_type b) const {
    return simd::extract<n>(vec_, b);
  }

  ace argon_type Reverse64bit() const { return simd::reverse_64bit(vec_); }
  ace argon_type Reverse32bit() const { return simd::reverse_32bit(vec_); }
  ace argon_type Reverse16bit() const { return simd::reverse_16bit(vec_); }

  ace std::array<argon_type, 2> ZipWith(argon_type b) const {
    using multivec_type = MultiVec<vector_type, 2>::type;
    using array_type = std::array<argon_type, 2>;

    // Since we're using a dirty ugly hack of reinterpreting a C array as a std::array,
    // the validity and POD-ness of std::array needs to be verified
    static_assert(std::is_standard_layout_v<array_type>);
    static_assert(std::is_trivial_v<array_type>);
    static_assert(sizeof(multivec_type) == sizeof(array_type),
                  "std::array isn't layout-compatible with this NEON multi-vector.");

    return *(array_type*)&simd::zip(vec_, b).val;
  }

  std::array<argon_type, 2> UnzipWith(argon_type b) {
    using multivec_type = MultiVec<vector_type, 2>::type;
    using array_type = std::array<argon_type, 2>;

    // Since we're using a dirty ugly hack of reinterpreting a C array as a std::array,
    // the validity and POD-ness of std::array needs to be verified
    static_assert(std::is_standard_layout_v<array_type>);
    static_assert(std::is_trivial_v<array_type>);
    static_assert(sizeof(multivec_type) == sizeof(array_type),
                  "std::array isn't layout-compatible with this NEON multi-vector.");

    return *(array_type*)&simd::unzip(vec_, b).val;
  }

  std::array<argon_type, 2> TransposeWith(argon_type b) const {
    using multivec_type = MultiVec<vector_type, 2>::type;
    using array_type = std::array<argon_type, 2>;

    // Since we're using a dirty ugly hack of reinterpreting a C array as a std::array,
    // the validity and POD-ness of std::array needs to be verified
    static_assert(std::is_standard_layout_v<array_type>);
    static_assert(std::is_trivial_v<array_type>);
    static_assert(sizeof(multivec_type) == sizeof(array_type),
                  "std::array isn't layout-compatible with this NEON multi-vector.");

    return *(array_type*)&simd::transpose(vec_, b).val;
  }

  ace static int size() { return lanes; }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<scalar_type(scalar_type)>>
  ace argon_type map(FuncType body) const {
    std::array<scalar_type, lanes> arr = this->as_array();
    std::array<scalar_type, lanes> out;
    for (size_t i = 0; i < lanes; ++i) {
      out[i] = body(arr[i]);
    }
    return argon_type::Load(out);
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<scalar_type(scalar_type, scalar_type)>>
  ace argon_type map2(argon_type other, FuncType body) const {
    std::array<scalar_type, lanes> arr0 = this->as_array();
    std::array<scalar_type, lanes> arr1 = other.as_array();
    std::array<scalar_type, lanes> out;
    for (size_t i = 0; i < lanes; ++i) {
      out[i] = body(arr0[i], arr1[i]);
    }
    return argon_type::Load(out);
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
  std::tuple_element_t<Index, argon_type> get() {
    return Lane{vec_, Index};
  }

 protected:
  vector_type vec_;
};

template <typename vector_type>
class Lane {
  using scalar_type = simd::NonVec_t<vector_type>;
  using type = Lane<vector_type>;
  using argon_type = ArgonFor_t<vector_type>;

 public:
  ace Lane(vector_type vec, const int lane) : vec_(vec), lane_(lane) {}
  ace operator scalar_type() { return simd::get_lane(vec_, lane_); }
  ace argon_type operator=(scalar_type b) { return simd::set_lane(vec_, lane_, b); }
  ace argon_type Load(scalar_type* ptr) { return simd::load1_lane(ptr, vec_); }

#if __ARM_ARCH >= 8
  ace vector_type vec() { return vec_; }
  ace const int lane() { return lane_; }
#else
  ace vector_type vec() {
    if constexpr (simd::is_doubleword_v<vector_type>) {
      return vec_;
    } else if constexpr (simd::is_quadword_v<vector_type>) {
      if (lane_ >= ArgonHalf<scalar_type>::lanes) {
        return simd::get_high(vec);
      } else {
        return simd::get_low(vec);
      }
    }
  }
  ace const int lane() {
    if constexpr (simd::is_doubleword_v<vector_type>) {
      return lane_;
    } else if constexpr (simd::is_quadword_v<vector_type>) {
      if (lane >= ArgonHalf<scalar_type>::lanes) {
        return (lane_ - ArgonHalf<scalar_type>::lanes);
      } else {
        return lane_;
      }
    }
  }
#endif

 private:
  vector_type vec_;
  int lane_;
};

}  // namespace argon::impl

/**
 * Lane deconstruction feature
 */
namespace std {
template <typename T>
struct tuple_size<argon::impl::Common<T>> {
  static constexpr size_t value = argon::impl::Common<T>::lanes;
};

template <size_t Index, typename T>
struct tuple_element<Index, argon::impl::Common<T>> {
  static_assert(Index < argon::impl::Common<T>::lanes);
  using type = argon::impl::Common<T>::lane_type;
};
}  // namespace std

#undef ace
#undef simd
