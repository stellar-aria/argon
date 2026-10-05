#pragma once
#include <array>
#include <limits>
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

/// @brief A 128-bit SIMD vector wrapping a scalar type, providing arithmetic, logical, and data-movement operations.
/// @tparam ScalarType The element type (e.g., `int32_t`, `float`, `uint8_t`).
/// @details Inherits all lane-wise operations from `argon::Vector` and adds 128-bit-specific operations such as
/// narrowing, widening multiplies, cross-half operations, reductions, and (optionally) AES acceleration.
/// Use `ArgonHalf<ScalarType>` for the 64-bit sibling.
template <typename ScalarType>
  requires argon::lane_scalar<ScalarType>
class Argon : public argon::Vector<simd::Vec128_t<ScalarType>> {
  using T = argon::Vector<simd::Vec128_t<ScalarType>>;

 public:
  using vector_type = simd::Vec128_t<ScalarType>;
  using lane_type = const argon::Lane<vector_type>;

  static_assert(simd::is_quadword_v<vector_type>);

  static constexpr size_t bytes = 16;
  static constexpr size_t lanes = bytes / sizeof(ScalarType);

  using argon::Vector<vector_type>::Vector;
  /// @brief Construct from an underlying `argon::Vector`.
  ace Argon(argon::Vector<vector_type> vec) : T{std::move(vec)} {};
  /// @brief Construct from a four-element array (loaded as a 128-bit vector).
  ace Argon(std::array<ScalarType, 4> value_list) : T{T::Load(value_list.data())} {};
  /// @brief Construct by combining a low and high 64-bit half-vector.
  ace Argon(ArgonHalf<ScalarType> low, ArgonHalf<ScalarType> high) : T{Combine(low, high)} {};

  ace Argon(argon::Lane<vector_type> b) : T{b} {};
  ace Argon(argon::ConstLane<0, vector_type> b) : T{b} {};

  template <simd::is_vector_type intrinsic_type>
  ace Argon(argon::Lane<intrinsic_type> b) : T{b} {};

  /// @brief Reinterpret the vector bits as a vector of a different element type.
  /// @tparam new_scalar_type The target element type.
  /// @return The same 128 bits viewed as `Argon<new_scalar_type>`.
  template <typename new_scalar_type>
  ace Argon<new_scalar_type> As() const {
    return simd::reinterpret<simd::Vec128_t<new_scalar_type>>(this->vec_);
  }

#ifndef ARGON_PLATFORM_MVE
  /// @brief Combine two 64-bit half-vectors into a single 128-bit vector.
  /// @param low  The lower 64 bits.
  /// @param high The upper 64 bits.
  ace static Argon<ScalarType> Combine(ArgonHalf<ScalarType> low, ArgonHalf<ScalarType> high) {
    return simd::combine(low, high);
  }

  /// @brief Reverse the order of all elements across the full 128-bit vector.
  /// @details Reverses within each 64-bit half, then swaps the two halves.
  ace Argon<ScalarType> Reverse() {
    auto rev_half = this->Reverse64bit();
    return Combine(rev_half.GetHigh(), rev_half.GetLow());
  }

  /// @brief Multiply two narrower half-vectors and add the widened result to this vector (vector × vector).
  /// @tparam U The narrower element type (must be the next-smaller type of `ScalarType`).
  template <typename U>
    requires argon::helpers::has_smaller_v<ScalarType> &&
             std::is_same_v<U, typename argon::helpers::NextSmaller<ScalarType>::type>
  ace Argon<ScalarType> MultiplyAddLong(ArgonHalf<U> b, ArgonHalf<U> c) {
    return simd::multiply_add_long(this->vec_, b, c);
  }
  /// @brief Multiply two narrower vectors and add the widened result (vector × raw intrinsic).
  template <typename U, typename C>
    requires argon::helpers::has_smaller_v<ScalarType> &&
             std::is_same_v<C, simd::Vec64_t<argon::helpers::NextSmaller_t<ScalarType>>>
  ace Argon<ScalarType> MultiplyAddLong(ArgonHalf<U> b, C c) {
    return simd::multiply_add_long(this->vec_, b, c);
  }

  /// @brief Multiply a half-vector by a scalar and add the widened result (vector × scalar).
  template <typename U>
    requires argon::helpers::has_smaller_v<ScalarType> &&
             std::is_same_v<U, typename argon::helpers::NextSmaller<ScalarType>::type>
  ace Argon<ScalarType> MultiplyAddLong(ArgonHalf<U> b, U c) {
    return simd::multiply_add_long(this->vec_, b, c);
  }

  /// @brief Multiply a half-vector by a lane and add the widened result (vector × lane).
  template <typename U>
    requires argon::helpers::has_smaller_v<ScalarType> &&
             std::is_same_v<U, typename argon::helpers::NextSmaller<ScalarType>::type>
  ace Argon<ScalarType> MultiplyAddLong(ArgonHalf<U> b, typename ArgonHalf<U>::lane_type c) {
    return simd::multiply_add_long(this->vec_, b, c.vec(), c.lane());
  }

  /// @brief Multiply two narrower half-vectors and subtract the widened result from this vector (vector × vector).
  template <typename U>
    requires argon::helpers::has_smaller_v<ScalarType> &&
             std::is_same_v<U, typename argon::helpers::NextSmaller<ScalarType>::type>
  ace Argon<ScalarType> MultiplySubtractLong(ArgonHalf<U> b, ArgonHalf<U> c) {
    return simd::multiply_subtract_long(this->vec_, b, c);
  }

  /// @brief Multiply a half-vector by a scalar and subtract the widened result (vector × scalar).
  template <typename U>
    requires argon::helpers::has_smaller_v<ScalarType> &&
             std::is_same_v<U, typename argon::helpers::NextSmaller<ScalarType>::type>
  ace Argon<ScalarType> MultiplySubtractLong(ArgonHalf<U> b, U c) {
    return simd::multiply_subtract_long(this->vec_, b, c);
  }

  /// @brief Multiply a half-vector by a lane and subtract the widened result (vector × lane).
  template <typename U>
    requires argon::helpers::has_smaller_v<ScalarType> &&
             std::is_same_v<U, typename argon::helpers::NextSmaller<ScalarType>::type>
  ace Argon<ScalarType> MultiplySubtractLong(ArgonHalf<U> b, typename ArgonHalf<U>::lane_type c) {
    return simd::multiply_subtract_long(this->vec_, b, c.vec(), c.lane());
  }

  /// @brief Add and narrow: add `b` to this vector and truncate each lane to the next-smaller type.
  /// @return An `ArgonHalf`-width vector of the next-smaller element type.
  ace auto AddNarrow(Argon<ScalarType> b) const
    requires argon::helpers::has_smaller_v<ScalarType>
  {
    auto result = simd::add_narrow(this->vec_, b);
    return argon::helpers::ArgonFor_t<decltype(result)>{result};
  }

  /// @brief Add, round, and narrow: add `b`, round the result, and truncate to the next-smaller type.
  ace auto AddRoundNarrow(Argon<ScalarType> b) const
    requires argon::helpers::has_smaller_v<ScalarType>
  {
    auto result = simd::add_round_narrow(this->vec_, b);
    return argon::helpers::ArgonFor_t<decltype(result)>{result};
  }

  /// @brief Subtract and narrow: subtract `b` and truncate each lane to the next-smaller type.
  ace auto SubtractNarrow(Argon<ScalarType> b) const
    requires argon::helpers::has_smaller_v<ScalarType>
  {
    auto result = simd::subtract_narrow(this->vec_, b);
    return argon::helpers::ArgonFor_t<decltype(result)>{result};
  }

  /// @brief Subtract, round, and narrow: subtract `b`, round the result, and truncate to the next-smaller type.
  ace auto SubtractRoundNarrow(Argon<ScalarType> b) const
    requires argon::helpers::has_smaller_v<ScalarType>
  {
    auto result = simd::subtract_round_narrow(this->vec_, b);
    return argon::helpers::ArgonFor_t<decltype(result)>{result};
  }

  /// @brief Shift each lane right by `n` bits and narrow the result to the next-smaller type.
  /// @tparam n Shift amount (must be in range [1, sizeof(ScalarType)*8]).
  template <size_t n>
    requires argon::helpers::has_smaller_v<ScalarType>
  ace auto ShiftRightNarrow() const {
    auto result = simd::shift_right_narrow<n>(this->vec_);
    return argon::helpers::ArgonFor_t<decltype(result)>{result};
  }

  /// @brief Shift right, saturate, and narrow: shift each lane right by `n` bits with unsigned saturation.
  /// @tparam n Shift amount.
  template <size_t n>
    requires argon::helpers::has_smaller_v<ScalarType>
  ace auto ShiftRightSaturateNarrow() const {
    auto result = simd::shift_right_saturate_narrow<n>(this->vec_);
    return argon::helpers::ArgonFor_t<decltype(result)>{result};
  }

  /// @brief Shift right, round, saturate, and narrow.
  /// @tparam n Shift amount.
  template <size_t n>
    requires argon::helpers::has_smaller_v<ScalarType>
  ace auto ShiftRightRoundSaturateNarrow() const {
    auto result = simd::shift_right_round_saturate_narrow<n>(this->vec_);
    return argon::helpers::ArgonFor_t<decltype(result)>{result};
  }

  /// @brief Shift right, round, and narrow.
  /// @tparam n Shift amount.
  template <size_t n>
    requires argon::helpers::has_smaller_v<ScalarType>
  ace auto ShiftRightRoundNarrow() const {
    auto result = simd::shift_right_round_narrow<n>(this->vec_);
    return argon::helpers::ArgonFor_t<decltype(result)>{result};
  }

  /// @brief Truncate each lane to the next-smaller element type (no saturation).
  ace auto Narrow() const
    requires argon::helpers::has_smaller_v<ScalarType>
  {
    auto result = simd::move_narrow(this->vec_);
    return argon::helpers::ArgonFor_t<decltype(result)>{result};
  }

  /// @brief Saturate and narrow each lane to the next-smaller element type.
  ace auto SaturateNarrow() const
    requires argon::helpers::has_smaller_v<ScalarType>
  {
    auto result = simd::move_saturate_narrow(this->vec_);
    return argon::helpers::ArgonFor_t<decltype(result)>{result};
  }

  /// @brief Multiply, double, add, and saturate long: `this + saturate(2 * b * c)` widening to `ScalarType`.
  template <typename NextSmallerType>
    requires argon::helpers::has_smaller_v<ScalarType> &&
             std::is_same_v<NextSmallerType, argon::helpers::NextSmaller_t<ScalarType>>
  ace Argon<ScalarType> MultiplyDoubleAddSaturateLong(ArgonHalf<NextSmallerType> b, ArgonHalf<NextSmallerType> c) {
    return neon::multiply_double_add_saturate_long(this->vec_, b, c);
  }

  /// @brief Return the upper 64 bits as an `ArgonHalf`.
  ace ArgonHalf<ScalarType> GetHigh() const { return simd::get_high(this->vec_); }
  /// @brief Return the lower 64 bits as an `ArgonHalf`.
  ace ArgonHalf<ScalarType> GetLow() const { return simd::get_low(this->vec_); }
#endif

  // ── Bottom / top widening and narrowing ─────────────────────────────────────────────────────────────────────
  // Helium widens and narrows by lane parity rather than by vector half: the "bottom" lanes are the even ones
  // (0, 2, 4, ...) and the "top" lanes the odd ones. Each pair of narrow lanes shares the bits of one wide lane, so
  // a narrow vector splits into WidenBottom() and WidenTop(), and NarrowBottom()/NarrowTop() write a wide vector
  // back into those lanes: hi.NarrowTop(lo.NarrowBottom(dest)) reassembles what WidenBottom/WidenTop took apart.
  // MVE has an instruction for each; NEON views the narrow vector as the wide type, where the bottom lane is the
  // low half of each wide lane, and widens with shifts and narrows with a bit select.

  /// @brief Widen the even (bottom) lanes to the next larger type. MVE: vmovlb.
  template <typename S = ScalarType>
    requires(std::is_integral_v<S> && sizeof(S) <= 2)
  ace Argon<argon::helpers::NextLarger_t<S>> WidenBottom() const {
#ifdef ARGON_PLATFORM_MVE
    return mve::move_long_bottom(this->vec_);
#else
    constexpr int half = 8 * sizeof(S);
    return this->template As<argon::helpers::NextLarger_t<S>>().template ShiftLeft<half>().template ShiftRight<half>();
#endif
  }

  /// @brief Widen the odd (top) lanes to the next larger type. MVE: vmovlt.
  template <typename S = ScalarType>
    requires(std::is_integral_v<S> && sizeof(S) <= 2)
  ace Argon<argon::helpers::NextLarger_t<S>> WidenTop() const {
#ifdef ARGON_PLATFORM_MVE
    return mve::move_long_top(this->vec_);
#else
    constexpr int half = 8 * sizeof(S);
    return this->template As<argon::helpers::NextLarger_t<S>>().template ShiftRight<half>();
#endif
  }

  /// @brief Widen the even (bottom) lanes and shift them left by `n`. MVE: vshllb.
  template <int n, typename S = ScalarType>
    requires(std::is_integral_v<S> && sizeof(S) <= 2 && n >= 1 && n <= 8 * int{sizeof(S)})
  ace Argon<argon::helpers::NextLarger_t<S>> ShiftLeftLongBottom() const {
#ifdef ARGON_PLATFORM_MVE
    return mve::shift_left_long_bottom<n>(this->vec_);
#else
    return WidenBottom().template ShiftLeft<n>();
#endif
  }

  /// @brief Widen the odd (top) lanes and shift them left by `n`. MVE: vshllt.
  template <int n, typename S = ScalarType>
    requires(std::is_integral_v<S> && sizeof(S) <= 2 && n >= 1 && n <= 8 * int{sizeof(S)})
  ace Argon<argon::helpers::NextLarger_t<S>> ShiftLeftLongTop() const {
#ifdef ARGON_PLATFORM_MVE
    return mve::shift_left_long_top<n>(this->vec_);
#else
    return WidenTop().template ShiftLeft<n>();
#endif
  }

  /// @brief Multiply the even (bottom) lanes, producing full-width products. MVE: vmullb.
  template <typename S = ScalarType>
    requires(std::is_integral_v<S> && sizeof(S) <= 4)
  ace Argon<argon::helpers::NextLarger_t<S>> MultiplyLongBottom(Argon<S> b) const {
#ifdef ARGON_PLATFORM_MVE
    return mve::multiply_long_bottom(this->vec_, b.vec());
#else
    return BottomLanes(*this) * BottomLanes(b);
#endif
  }

  /// @brief Multiply the odd (top) lanes, producing full-width products. MVE: vmullt.
  template <typename S = ScalarType>
    requires(std::is_integral_v<S> && sizeof(S) <= 4)
  ace Argon<argon::helpers::NextLarger_t<S>> MultiplyLongTop(Argon<S> b) const {
#ifdef ARGON_PLATFORM_MVE
    return mve::multiply_long_top(this->vec_, b.vec());
#else
    return TopLanes(*this) * TopLanes(b);
#endif
  }

  /// @brief Narrow each lane (keeping its low half) into the even (bottom) lanes of `dest`. MVE: vmovnb.
  /// @param dest The narrow vector whose odd (top) lanes are kept.
  template <typename S = ScalarType>
    requires(std::is_integral_v<S> && (sizeof(S) == 2 || sizeof(S) == 4))
  ace Argon<argon::helpers::NextSmaller_t<S>> NarrowBottom(Argon<argon::helpers::NextSmaller_t<S>> dest) const {
#ifdef ARGON_PLATFORM_MVE
    return mve::move_narrow_bottom(dest.vec(), this->vec_);
#else
    return InsertBottom(dest, *this);
#endif
  }

  /// @brief Narrow each lane (keeping its low half) into the odd (top) lanes of `dest`. MVE: vmovnt.
  /// @param dest The narrow vector whose even (bottom) lanes are kept.
  template <typename S = ScalarType>
    requires(std::is_integral_v<S> && (sizeof(S) == 2 || sizeof(S) == 4))
  ace Argon<argon::helpers::NextSmaller_t<S>> NarrowTop(Argon<argon::helpers::NextSmaller_t<S>> dest) const {
#ifdef ARGON_PLATFORM_MVE
    return mve::move_narrow_top(dest.vec(), this->vec_);
#else
    return InsertTop(dest, *this);
#endif
  }

  /// @brief Narrow each lane with saturation into the even (bottom) lanes of `dest`. MVE: vqmovnb.
  template <typename S = ScalarType>
    requires(std::is_integral_v<S> && (sizeof(S) == 2 || sizeof(S) == 4))
  ace Argon<argon::helpers::NextSmaller_t<S>> SaturateNarrowBottom(
      Argon<argon::helpers::NextSmaller_t<S>> dest) const {
#ifdef ARGON_PLATFORM_MVE
    return mve::move_narrow_saturate_bottom(dest.vec(), this->vec_);
#else
    return InsertBottom(dest, SaturateToNarrow(*this));
#endif
  }

  /// @brief Narrow each lane with saturation into the odd (top) lanes of `dest`. MVE: vqmovnt.
  template <typename S = ScalarType>
    requires(std::is_integral_v<S> && (sizeof(S) == 2 || sizeof(S) == 4))
  ace Argon<argon::helpers::NextSmaller_t<S>> SaturateNarrowTop(Argon<argon::helpers::NextSmaller_t<S>> dest) const {
#ifdef ARGON_PLATFORM_MVE
    return mve::move_narrow_saturate_top(dest.vec(), this->vec_);
#else
    return InsertTop(dest, SaturateToNarrow(*this));
#endif
  }

#ifdef ARGON_PLATFORM_MVE
#define ARGON_SHIFT_NARROW_BODY(mve_name, Insert, neon_value) return mve::mve_name<n>(dest.vec(), this->vec_);
#else
#define ARGON_SHIFT_NARROW_BODY(mve_name, Insert, neon_value) return Insert(dest, neon_value);
#endif
  // Shift right by n, optionally rounding and/or saturating, then narrow into the bottom or top lanes of dest.
#define ARGON_SHIFT_NARROW(Name, mve_name, Insert, neon_value)                                                  \
  template <int n, typename S = ScalarType>                                                                     \
    requires(std::is_integral_v<S> && (sizeof(S) == 2 || sizeof(S) == 4) && n >= 1 && n <= 4 * int{sizeof(S)}) \
  ace Argon<argon::helpers::NextSmaller_t<S>> Name(Argon<argon::helpers::NextSmaller_t<S>> dest) const {         \
    ARGON_SHIFT_NARROW_BODY(mve_name, Insert, neon_value)                                                       \
  }

  /// @brief Shift each lane right by `n` and narrow it into the even (bottom) lanes of `dest`. MVE: vshrnb.
  ARGON_SHIFT_NARROW(ShiftRightNarrowBottom, shift_right_narrow_bottom, InsertBottom,
                     this->template ShiftRight<n>())
  /// @brief Shift each lane right by `n` and narrow it into the odd (top) lanes of `dest`. MVE: vshrnt.
  ARGON_SHIFT_NARROW(ShiftRightNarrowTop, shift_right_narrow_top, InsertTop, this->template ShiftRight<n>())
  /// @brief Shift each lane right by `n` with rounding and narrow it into the bottom lanes of `dest`. MVE: vrshrnb.
  ARGON_SHIFT_NARROW(ShiftRightRoundNarrowBottom, shift_right_narrow_round_bottom, InsertBottom,
                     this->template ShiftRightRound<n>())
  /// @brief Shift each lane right by `n` with rounding and narrow it into the top lanes of `dest`. MVE: vrshrnt.
  ARGON_SHIFT_NARROW(ShiftRightRoundNarrowTop, shift_right_narrow_round_top, InsertTop,
                     this->template ShiftRightRound<n>())
  /// @brief Shift each lane right by `n` and narrow it with saturation into the bottom lanes of `dest`.
  /// MVE: vqshrnb.
  ARGON_SHIFT_NARROW(ShiftRightSaturateNarrowBottom, shift_right_narrow_saturate_bottom, InsertBottom,
                     SaturateToNarrow(this->template ShiftRight<n>()))
  /// @brief Shift each lane right by `n` and narrow it with saturation into the top lanes of `dest`. MVE: vqshrnt.
  ARGON_SHIFT_NARROW(ShiftRightSaturateNarrowTop, shift_right_narrow_saturate_top, InsertTop,
                     SaturateToNarrow(this->template ShiftRight<n>()))
  /// @brief Shift each lane right by `n` with rounding and narrow it with saturation into the bottom lanes of
  /// `dest`. MVE: vqrshrnb.
  ARGON_SHIFT_NARROW(ShiftRightRoundSaturateNarrowBottom, shift_right_narrow_round_saturate_bottom, InsertBottom,
                     SaturateToNarrow(this->template ShiftRightRound<n>()))
  /// @brief Shift each lane right by `n` with rounding and narrow it with saturation into the top lanes of `dest`.
  /// MVE: vqrshrnt.
  ARGON_SHIFT_NARROW(ShiftRightRoundSaturateNarrowTop, shift_right_narrow_round_saturate_top, InsertTop,
                     SaturateToNarrow(this->template ShiftRightRound<n>()))
#undef ARGON_SHIFT_NARROW
#undef ARGON_SHIFT_NARROW_BODY

  /// @brief Convert each lane to a different element type.
  /// @tparam U The destination element type.
  template <typename U>
  ace Argon<U> ConvertTo() const {
#ifndef __ARM_FEATURE_MVE
    // vcvt semantics (truncate, saturate, NaN -> 0) on every compiler: see helpers/float_fixups.hpp
    if constexpr (std::is_same_v<ScalarType, float> && std::is_same_v<U, int32_t>) {
      return argon::helpers::convert_to_int32(this->vec_);
    } else if constexpr (std::is_same_v<ScalarType, float> && std::is_same_v<U, uint32_t>) {
      return argon::helpers::convert_to_uint32(this->vec_);
    }
#endif
    return simd::convert<typename simd::Vec128<U>::type>(this->vec_);
  }

  /// @brief Convert each lane to a different type using a fixed-point fractional bit count.
  /// @tparam U         The destination element type (`float`, `int32_t`, or `uint32_t`).
  /// @tparam fracbits  The number of fractional bits in the fixed-point representation.
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

  /// @brief Reverse the order of all elements in the 128-bit vector.
  /// @details Reverses elements within each 64-bit doubleword, then swaps the two doublewords.
  ace Argon<ScalarType> Reverse() const {
    return Argon<ScalarType>{this->Reverse64bit()}.SwapDoublewords();  // rev within dword, then swap dwords
  }

#ifdef ARGON_PLATFORM_MVE
  /// Whether MVE's across-vector add (vaddv) handles these lanes: integers up to 32 bits.
  static constexpr bool mve_across_add = std::is_integral_v<ScalarType> && sizeof(ScalarType) < 8;
#endif

  /// @brief Fold all lanes into a single scalar using a commutative binary operation.
  /// @tparam CommutableOpType A callable `(Argon, Argon) -> Argon` (e.g., addition, max).
  /// @param op The commutative binary operation.
  /// @return The scalar result after all lanes have been folded.
  template <typename CommutableOpType>
  ScalarType Reduce(CommutableOpType op) const {
    auto rev = this->SwapDoublewords();
    auto sum = op(*this, rev);
    if constexpr (lanes == 16) {
      sum = op(sum, sum.Reverse16bit());
    }
    if constexpr (lanes == 8 || lanes == 16) {
      sum = op(sum, sum.Reverse32bit());
    }
    if constexpr (lanes == 4 || lanes == 8 || lanes == 16) {
      sum = op(sum, sum.Reverse64bit());
    }
    return sum[0];
  }

  /// @brief Sum all lanes and return the scalar result.
  ScalarType ReduceAdd() const {
#if defined(__aarch64__)
    if constexpr (!argon::is_half_float_v<ScalarType>) {  // A64 has no across-vector f16 add
      return simd::reduce_add(this->vec_);
    }
#elifdef ARGON_PLATFORM_MVE
    if constexpr (mve_across_add) {
      return static_cast<ScalarType>(mve::reduce_add(this->vec_));  // vaddv
    }
#endif
    return this->Reduce([](auto a, auto b) { return a + b; });
  }

  /// @brief Sum the active lanes and return the scalar result.
  /// @details MVE (integer lanes up to 32 bits): vaddv with the predicate. Otherwise the inactive lanes are zeroed
  /// and the vector summed.
  /// @param active The lanes to sum.
  ScalarType ReduceAdd(typename T::argon_bool_type active) const {
#ifdef ARGON_PLATFORM_MVE
    if constexpr (mve_across_add) {
      return static_cast<ScalarType>(mve::reduce_add(this->vec_, active.native()));
    }
#endif
    return active.Select(*this, Argon<ScalarType>{ScalarType{0}}).ReduceAdd();
  }

  /// @brief Return the maximum value across all lanes.
  ScalarType ReduceMax() const {
#ifdef __aarch64__
    return simd::reduce_max(this->vec_);
#else
    return this->Reduce([](auto a, auto b) { return a.Max(b); });
#endif
  }

  /// @brief Return the minimum value across all lanes.
  ScalarType ReduceMin() const {
#ifdef __aarch64__
    return simd::reduce_min(this->vec_);
#else
    auto arr = this->to_array();
    return std::reduce(arr.begin(), arr.end(), arr[0], [](auto a, auto b) { return std::min(a, b); });
#endif
  }

  /// @brief Swap the upper and lower 64-bit halves of the vector.
  ace Argon<ScalarType> SwapDoublewords() const {
#ifdef ARGON_PLATFORM_MVE
    // MVE has no half-vector registers or vext; swap the two 64-bit lanes instead.
    uint64x2_t dwords = simd::reinterpret<uint64x2_t>(this->vec_);
    return simd::reinterpret<vector_type>(uint64x2_t{dwords[1], dwords[0]});
#else
    return Combine(GetHigh(), GetLow());
#endif
  }

#if ARGON_HAS_CRYPTO && !defined(ARGON_PLATFORM_MVE)
  /// @brief AES single-round encryption
  /// @param key  Round key vector (uint8x16_t)
  /// @return     Result after AddRoundKey + SubBytes + ShiftRows
  /// @note Requires __ARM_FEATURE_CRYPTO. Use with AesMixColumns for a full AES round.
  ace Argon<ScalarType> AesEncrypt(Argon<ScalarType> key) const
    requires std::is_same_v<ScalarType, uint8_t>
  {
    return neon::aes_encrypt(this->vec_, key.vec_);
  }

  /// @brief AES single-round decryption
  /// @param key  Round key vector (uint8x16_t)
  /// @return     Result after inverse AddRoundKey + InvSubBytes + InvShiftRows
  /// @note Requires __ARM_FEATURE_CRYPTO. Use with AesInverseMixColumns for a full inverse AES round.
  ace Argon<ScalarType> AesDecrypt(Argon<ScalarType> key) const
    requires std::is_same_v<ScalarType, uint8_t>
  {
    return neon::aes_decrypt(this->vec_, key.vec_);
  }

  /// @brief AES MixColumns transformation
  /// @return Result after the MixColumns step of the AES cipher
  /// @note Requires __ARM_FEATURE_CRYPTO.
  ace Argon<ScalarType> AesMixColumns() const
    requires std::is_same_v<ScalarType, uint8_t>
  {
    return neon::aes_mix_columns(this->vec_);
  }

  /// @brief AES inverse MixColumns transformation
  /// @return Result after the InvMixColumns step of the AES decipher
  /// @note Requires __ARM_FEATURE_CRYPTO.
  ace Argon<ScalarType> AesInverseMixColumns() const
    requires std::is_same_v<ScalarType, uint8_t>
  {
    return neon::aes_inverse_mix_columns(this->vec_);
  }
#endif

 private:
#ifndef ARGON_PLATFORM_MVE
  // NEON helpers for the bottom/top operations. A narrow vector viewed as the next larger type has its bottom
  // (even) lane in the low half of each wide lane and its top (odd) lane in the high half.

  /// The even lanes of `v`, sign- or zero-extended to the next larger type.
  template <typename S>
  ace static Argon<argon::helpers::NextLarger_t<S>> BottomLanes(Argon<S> v) {
    constexpr int half = 8 * sizeof(S);
    return v.template As<argon::helpers::NextLarger_t<S>>().template ShiftLeft<half>().template ShiftRight<half>();
  }

  /// The odd lanes of `v`, sign- or zero-extended to the next larger type.
  template <typename S>
  ace static Argon<argon::helpers::NextLarger_t<S>> TopLanes(Argon<S> v) {
    return v.template As<argon::helpers::NextLarger_t<S>>().template ShiftRight<8 * sizeof(S)>();
  }

  /// A mask of the low (bottom) half of each lane of the wide type W.
  template <typename W>
  ace static Argon<std::make_unsigned_t<W>> LowHalfMask() {
    using U = std::make_unsigned_t<W>;
    return Argon<U>{static_cast<U>((U{1} << (4 * sizeof(W))) - 1)};
  }

  /// `dest` with its bottom lanes replaced by the low half of each lane of `wide`.
  template <typename W>
  ace static Argon<argon::helpers::NextSmaller_t<W>> InsertBottom(Argon<argon::helpers::NextSmaller_t<W>> dest,
                                                                  Argon<W> wide) {
    using N = argon::helpers::NextSmaller_t<W>;
    return LowHalfMask<W>().Select(wide, dest.template As<W>()).template As<N>();
  }

  /// `dest` with its top lanes replaced by the low half of each lane of `wide`.
  template <typename W>
  ace static Argon<argon::helpers::NextSmaller_t<W>> InsertTop(Argon<argon::helpers::NextSmaller_t<W>> dest,
                                                               Argon<W> wide) {
    using N = argon::helpers::NextSmaller_t<W>;
    return LowHalfMask<W>().Select(dest.template As<W>(), wide.template ShiftLeft<4 * sizeof(W)>()).template As<N>();
  }

  /// `wide` clamped to the range of the next smaller type.
  template <typename W>
  ace static Argon<W> SaturateToNarrow(Argon<W> wide) {
    using N = argon::helpers::NextSmaller_t<W>;
    const Argon<W> high{static_cast<W>(std::numeric_limits<N>::max())};
    if constexpr (std::is_signed_v<W>) {
      return wide.Min(high).Max(Argon<W>{static_cast<W>(std::numeric_limits<N>::min())});
    } else {
      return wide.Min(high);
    }
  }
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
