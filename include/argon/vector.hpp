#pragma once
#include <array>
#include <bit>
#include <functional>
#include <tuple>
#include <type_traits>
#include <utility>
#include "arm_simd/helpers.hpp"
#include "arm_simd/helpers/scalar.hpp"
#include "arm_simd/helpers/vec64.hpp"
#include "features.h"
#include "helpers.hpp"
#include "helpers/bool.hpp"
#include "helpers/multivector.hpp"
#include "helpers/to_array.hpp"

#ifdef __ARM_FEATURE_MVE
#define simd helium
#else
#define simd neon
#endif

#ifdef ARGON_PLATFORM_SIMDE
#define ace
#elifdef __clang__
#define ace [[gnu::always_inline]] constexpr
#else
#define ace [[gnu::always_inline]] inline
#endif

namespace argon {
template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

/// @brief Helper template to check if a type is one of the specified types.
/// @tparam T The type to check.
/// @tparam Ts The types to check against.
/// @details This template uses a variadic template to check if T is one of the types in Ts.
template <typename T, typename... Ts>
inline constexpr bool is_one_of = std::disjunction_v<std::is_same<T, Ts>...>;

/// @brief Represents a single lane of a SIMD vector.
/// @tparam VectorType The type of the SIMD vector.
/// @details This class provides access to a single lane of a SIMD vector, allowing for operations on that lane.
template <typename VectorType>
class Lane;

/// @brief Represents a single lane of a SIMD vector, where the lane's index is known at compile time.
/// @tparam VectorType The type of the SIMD vector.
/// @tparam LaneIndex The index of the lane in the SIMD vector.
/// @details This class provides access to a single lane of a SIMD vector, allowing for operations on that lane.
template <size_t LaneIndex, typename VectorType>
class ConstLane;

/// @brief Represents a SIMD vector with various operations.
/// @tparam VectorType The type of the SIMD vector. (e.g. int32x4_t, float32x4_t)
/// @details This class provides a wrapper around SIMD vector types, allowing for object-oriented operations on the
/// vector.
template <typename VectorType>
class Vector {
 public:
  using scalar_type = simd::Scalar_t<VectorType>;                 ///< The scalar type of the SIMD vector.
  using lane_type = Lane<VectorType>;                             ///< The type of a single lane of the SIMD vector.
  using vector_type = VectorType;                                 ///< The SIMD vector type.
  using argon_type = helpers::ArgonFor_t<VectorType>;             ///< The Argon type for the SIMD vector.
  using vector_bool_type = Bool_t<VectorType>;                    ///< The type of a boolean SIMD vector.
  using argon_bool_type = helpers::ArgonFor_t<vector_bool_type>;  ///< The Argon type for the boolean vector.

  /// @brief The number of lanes in the SIMD vector.
  static constexpr size_t lanes = (simd::is_quadword_v<VectorType> ? 16 : 8) / sizeof(scalar_type);

  /// @brief The default constructor for the Vector class.
  constexpr Vector() = default;

  /// @brief Constructs a Vector from a SIMD vector type.
  /// @param vector The SIMD vector to construct from.
  constexpr Vector(VectorType vector) : vec_{std::move(vector)} {};

  /// @brief Constructs a Vector from a scalar value.
  /// @param scalar The scalar value to construct from.
  /// @details This constructor duplicates the scalar value across all lanes of the SIMD vector.
  ace Vector(scalar_type scalar) : vec_(FromScalar(scalar)) {};

  /// @brief Constructs a Vector from a Lane object.
  /// @param lane The Lane object to construct from.
  /// @details This constructor duplicates the lane value across all lanes of the SIMD vector.
  ace Vector(argon::Lane<VectorType> lane) : vec_(FromLane(lane)) {};

  /// @brief Constructs a Vector from a ConstLane object.
  /// @param lane The ConstLane object to construct from.
  /// @details This constructor duplicates the lane value across all lanes of the SIMD vector.
  /// @param lane The ConstLane object to construct from.
  template <size_t LaneIndex>
  ace Vector(argon::ConstLane<LaneIndex, VectorType> lane) : vec_(FromLane(lane)) {};

  /// @brief Constructs a Vector from a scalar pointer.
  /// @param ptr The pointer to the scalar value to construct from.
  /// @details This constructor loads the scalar value from the pointer and duplicates it
  /// across all lanes of the SIMD vector.
  /// @return The constructed SIMD vector.
  ace static argon_type LoadScalar(scalar_type* ptr) { return simd::load1_duplicate(ptr); }

  /// @brief Constructs a Vector from a scalar value.
  /// @param scalar The scalar value to construct from.
  /// @details This constructor duplicates the scalar value across all lanes of the SIMD vector.
  /// @return The constructed SIMD vector.
  ace static argon_type FromScalar(scalar_type scalar) { return simd::duplicate<VectorType>(scalar); }

  /// @brief Constructs a Vector from a Lane object.
  /// @param lane The Lane object to construct from.
  /// @details This constructor duplicates the lane value across all lanes of the SIMD vector.
  /// @return The constructed SIMD vector.
  template <simd::is_vector_type IntrinsicType>
  ace static argon_type FromLane(argon::Lane<IntrinsicType> lane) {
    return simd::duplicate_lane(lane.vec(), lane.lane());
  }

  /// @brief Constructs a Vector from a ConstLane object.
  /// @param lane The ConstLane object to construct from.
  /// @details This constructor duplicates the lane value across all lanes of the SIMD vector.
  /// @return The constructed SIMD vector.
  template <size_t LaneIndex>
  ace static argon_type FromLane(argon::ConstLane<LaneIndex, VectorType> lane) {
    if constexpr (simd::is_quadword_v<VectorType>) {
      return simd::duplicate_lane_quad<Lane>(lane.vec());
    } else {
      return simd::duplicate_lane<Lane>(lane.vec());
    }
  }

  /// @brief Constructs a Vector from an incrementing sequence.
  /// @param start The starting value of the sequence.
  /// @param step The step size of the sequence.
  /// @return The constructed SIMD vector.
  /// @details This constructor creates a SIMD vector with lanes containing values from start to start + (lanes - 1) *
  /// step.
  ace static argon_type Iota(scalar_type start, scalar_type step = 1) {
    if consteval {
      VectorType out;
      helpers::consteval_for<0, lanes, 1>([&](size_t i) {  //
        out[i] = start + i * step;
      });
      return out;
    } else {
      return Argon{start}.MultiplyAdd(step, VectorType{0, 1, 2, 3});
    }
  }

  /// @brief Constructs a Vector from a function that generates values.
  /// @param body The function that generates the values.
  /// @details This constructor creates a SIMD vector with lanes containing values generated by the function.
  /// @return The constructed SIMD vector.
  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<scalar_type()>>
  ace static argon_type Generate(FuncType body) {
    VectorType out;
    helpers::consteval_for<0, lanes, 1>([&](size_t i) {  //
      out[i] = body();
    });
    return out;
  }

  /// @brief Constructs a Vector from a function that generates values with an index.
  /// @param body The function that generates the values.
  /// @details This constructor creates a SIMD vector with lanes containing values generated by the function using the
  /// index.
  /// @return The constructed SIMD vector.
  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<scalar_type(scalar_type)>>
  ace static argon_type GenerateWithIndex(FuncType body) {
    VectorType out;
    helpers::consteval_for<0, lanes, 1>([&](size_t i) {  //
      out[i] = body(i);
    });
    return out;
  }

  /// @brief Negate the SIMD vector and return the result.
  /// @return The negated SIMD vector.
  ace argon_type operator-() const { return Negate(); }

  /// @brief Add a vector and return the result.
  ace argon_type operator+(argon_type b) const { return Add(b); }

  /// @brief Subtract a vector and return the result.
  ace argon_type operator-(argon_type b) const { return Subtract(b); }

  /// @brief Multiply a vector and return the result.
  ace argon_type operator*(argon_type b) const { return Multiply(b); }

  /// @brief Divide a vector and return the result.
  ace argon_type operator/(argon_type b) const { return Divide(b); }

  /// @brief Compare two vectors for equality.
  /// @param b The vector to compare against.
  ace argon_bool_type operator==(argon_type b) const { return Equal(b); }

  /// @brief Compare two vectors for inequality.
  /// @param b The vector to compare against.
  ace argon_bool_type operator!=(argon_type b) const { return ~Equal(b); }

  /// @brief Compare two vectors, checking if this vector is less than the other.
  ace argon_bool_type operator<(argon_type b) const { return LessThan(b); }

  /// @brief Compare two vectors, checking if this vector is greater than the other.
  ace argon_bool_type operator>(argon_type b) const { return GreaterThan(b); }

  /// @brief Compare two vectors, checking if this vector is less than or equal to the other.
  ace argon_bool_type operator<=(argon_type b) const { return LessThanOrEqual(b); }

  /// @brief Compare two vectors, checking if this vector is greater than or equal to the other.
  ace argon_bool_type operator>=(argon_type b) const { return GreaterThanOrEqual(b); }

  /// @brief Increment the vector by 1 and return the result.
  ace argon_type operator++() const { return Add(1); }

  /// @brief Decrement the vector by 1 and return the result.
  ace argon_type operator--() const { return Subtract(1); }

  /// @brief Bitwise AND two vectors and return the result.
  ace argon_type operator&(argon_type b) const { return BitwiseAnd(b); }

  /// @brief Bitwise OR two vectors and return the result.
  ace argon_type operator|(argon_type b) const { return BitwiseOr(b); }

  /// @brief Bitwise XOR two vectors and return the result.
  ace argon_type operator^(argon_type b) const { return BitwiseXor(b); }

  /// @brief Bitwise NOT the vector and return the result.
  ace argon_type operator~() const { return BitwiseNot(); }

  /// @brief Access a lane of the vector by index.
  ace Lane<const VectorType> operator[](const size_t i) const { return {vec_, static_cast<int>(i)}; }

  /// @brief Access a lane of the vector by index.
  ace lane_type operator[](const size_t i) { return {vec_, static_cast<int>(i)}; }

  /// @brief Shift the elements of the vector to the right by a specified number of bits.
  ace argon_type operator>>(const int i) const { return ShiftRight(i); }

  /// @brief Shift the elements of the vector to the left by a specified number of bits.
  ace argon_type operator<<(const int i) const { return ShiftLeft(i); }

  /// @brief Get the underlying SIMD vector.
  [[gnu::always_inline]] constexpr VectorType vec() const { return vec_; }

  /// @brief Convert the vector to the underlying SIMD vector type.
  [[gnu::always_inline]] constexpr operator VectorType() const { return vec_; }

  /// @brief Convert the vector to an array of scalar values.
  /// @return An array of scalar values representing the vector.
  ace std::array<scalar_type, lanes> to_array() {
    std::array<scalar_type, lanes> out;
    simd::store1(&out[0], vec_);
    return out;
  }

  /// @brief Get a single lane of the vector by index.
  /// @param i The index of the lane to get.
  /// @return The value of the specified lane in the SIMD vector.
  /// @note If you know the index of the lane at compile time, you should use GetLane<LaneIndex>() instead.
  ace scalar_type GetLane(const size_t i) const { return GetLane(static_cast<int>(i)); }

  /// @brief Get a single lane of the vector by index.
  /// @param i The index of the lane to get.
  /// @return The value of the specified lane in the SIMD vector.
  ace scalar_type GetLane(const int i) const { return simd::get_lane(vec_, i); }

  /// @brief Get a single lane of the vector by index.
  /// @tparam LaneIndex The index of the lane to get.
  /// @return The value of the specified lane in the SIMD vector.
  template <size_t LaneIndex>
  ace scalar_type GetLane() const {
    if constexpr (LaneIndex < lanes) {
      return simd::get_lane<LaneIndex>(vec_, LaneIndex);
    } else {
      return 0;
    }
  }

  /// @brief Get the last lane of the vector.
  /// @return The last lane of the vector.
  ace lane_type LastLane() { return lane_type{vec_, lanes - 1}; }

  /// @brief Shift the elements of the vector to the right by a specified number of bits.
  ace argon_type ShiftRight(const int i) const { return simd::shift_right(vec_, i); }

  /// @brief Shift the elements of the vector to the left by a specified number of bits.
  ace argon_type ShiftLeft(const int i) const { return simd::shift_left(vec_, i); }

  /// @brief Bitwise negate the vector and return the result.
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
  ace argon_type MultiplyAdd(scalar_type b, argon_type c) const { return simd::multiply_add(vec_, c, b); }
  ace argon_type MultiplyAdd(argon_type b, lane_type c) const {
    return simd::multiply_add_lane(vec_, b.vec(), c.vec(), c.lane());
  }

  /** a - (b * c) */
  ace argon_type MultiplySubtract(argon_type b, argon_type c) const { return simd::multiply_subtract(vec_, b, c); }
  ace argon_type MultiplySubtract(argon_type b, scalar_type c) const { return simd::multiply_subtract(vec_, b, c); }
  ace argon_type MultiplySubtract(scalar_type b, argon_type c) const { return simd::multiply_subtract(vec_, c, b); }
  ace argon_type MultiplySubtract(argon_type b, lane_type c) const {
    return simd::multiply_subtract_lane(vec_, b.vec(), c.vec(), c.lane());
  }

  /**
   * Multiply two fixed-point vectors, returning a fixed-point product
   * This is equivalent to (a * b) >> 31
   */
  ace argon_type MultiplyQ31(argon_type v) const { return simd::multiply_double_saturate_high(vec_, v); }
  ace argon_type MultiplyQ31(scalar_type s) const { return simd::multiply_double_saturate_high(vec_, s); }
  ace argon_type MultiplyQ31(lane_type l) const {
    return simd::multiply_double_saturate_high_lane(vec_, l.vec(), l.lane());
  }

  /**
   * Multiply two fixed-point vectors, returning a fixed-point product
   * This is equivalent to round(a * b) >> 31
   */
  ace argon_type MultiplyRoundQ31(argon_type v) const { return simd::multiply_double_round_saturate_high(vec_, v); }
  ace argon_type MultiplyRoundQ31(scalar_type s) const { return simd::multiply_double_round_saturate_high(vec_, s); }
  ace argon_type MultiplyRoundQ31(lane_type l) const {
    return simd::multiply_double_round_saturate_high_lane(vec_, l.vec(), l.lane());
  }

  ace argon_type Absolute() const { return simd::abs(vec_); }

  /// @brief 1 / value, using an estimate for speed
  /// @note This is not a precise reciprocal, but it is fast and useful for many applications
  ace argon_type ReciprocalEstimate() const
    requires std::floating_point<scalar_type> || std::is_same_v<scalar_type, uint32_t>
  {
    return simd::reciprocal_estimate(vec_);
  }

  /**
   * Multiply-add three fixed-point vectors, returning a fixed-point sum
   * This is equivalent to a + ((b * c) >> 31)
   */
  template <typename arg_type>
    requires(is_one_of<arg_type, argon_type, scalar_type, lane_type> || std::is_convertible_v<arg_type, argon_type> ||
             std::is_convertible_v<arg_type, scalar_type>)
  ace argon_type MultiplyAddQ31(argon_type b, arg_type c) const {
    return Add(b.MultiplyQ31(c));
  }

  /**
   * Multiply-round-add three fixed-point vectors, returning a fixed-point sum
   * This is equivalent to a + (rnd(b * c) >> 31)
   */
  template <typename arg_type>
    requires(is_one_of<arg_type, argon_type, scalar_type, lane_type> || std::is_convertible_v<arg_type, argon_type> ||
             std::is_convertible_v<arg_type, scalar_type>)
  ace argon_type MultiplyRoundAddQ31(argon_type b, arg_type c) const {
    return Add(b.MultiplyRoundQ31(c));
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

  ace argon_bool_type Equal(argon_type b) const { return simd::equal(vec_, b); }
  ace argon_bool_type GreaterThanOrEqual(argon_type b) const { return simd::greater_than_or_equal(vec_, b); }
  ace argon_bool_type LessThanOrEqual(argon_type b) const { return simd::less_than_or_equal(vec_, b); }
  ace argon_bool_type GreaterThan(argon_type b) const { return simd::greater_than(vec_, b); }
  ace argon_bool_type LessThan(argon_type b) const { return simd::less_than(vec_, b); }

  template <typename signed_vector>
    requires(std::is_integral_v<scalar_type> &&
             std::is_same_v<signed_vector, typename helpers::ArgonFor<simd::make_signed_t<VectorType>>::type>)
  ace argon_type ShiftLeft(signed_vector b) const
    requires std::is_integral_v<scalar_type>
  {
    return simd::shift_left(vec_, b);
  }

  template <int n>
  ace argon_type ShiftLeft() const {
    return simd::shift_left<n>(vec_);
  }

  template <typename signed_vector>
    requires(std::is_integral_v<scalar_type> &&
             std::is_same_v<signed_vector, typename helpers::ArgonFor<simd::make_signed_t<VectorType>>::type>)
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

  ace static argon_type Load(const scalar_type* ptr) { return simd::load1<VectorType>(ptr); }
  ace static argon_type LoadCopy(const scalar_type* ptr) { return simd::load1_duplicate<VectorType>(ptr); }

  /**
   * @brief Using a base address and a vector of offset indices and a base pointer, create a new vector
   *
   * @note On NEON this incurs a writeback + load penalty
   *
   * @param base The address to index from
   * @param offset_vector A vector of offset indices
   * @return A new vector constructed from the various indices
   */
  template <simd::is_vector_type IntrinsicType>
  ace static argon_type LoadGather(const scalar_type* base, IntrinsicType offset_vector) {
    using offset_type = simd::Scalar_t<IntrinsicType>;
    static_assert(std::is_unsigned_v<offset_type>, "Offset elements must be unsigned values");
    static_assert((sizeof(IntrinsicType) / sizeof(offset_type)) == lanes,
                  "Number of elements in offset vector must match number of elements in destination vector");
    argon_type destination;
    helpers::consteval_for<0, lanes, 1>([&]<int i>() {  //<
      offset_type lane_val = simd::get_lane<i>(offset_vector);
      destination = destination.template LoadToLane<i>(base + lane_val);
    });
    return destination;
  }

  template <typename T>
  ace static argon_type LoadGather(const scalar_type* base, T offset_vector) {
    return argon_type::template LoadGather<typename T::VectorType>(base, offset_vector);
  }

  template <size_t lane>
  ace argon_type LoadToLane(const scalar_type* ptr) {
    if constexpr (simd::is_quadword_v<VectorType>) {
      return simd::load1_lane_quad<lane>(ptr, vec_);
    } else {
      return simd::load1_lane<lane>(ptr, vec_);
    }
  }

  template <size_t stride>
  ace static std::array<argon_type, stride> LoadCopyInterleaved(const scalar_type* ptr) {
    static_assert(stride > 1 && stride < 5,
                  "De-interleaving LoadCopy can only be performed with a stride of 2, 3, or 4");
    using multivec_type = helpers::MultiVector<VectorType, stride>::type;

    if constexpr (stride == 2) {
      return argon::to_array(simd::load2_duplicate<multivec_type>(ptr).val);
    } else if constexpr (stride == 3) {
      return argon::to_array(simd::load3_duplicate<multivec_type>(ptr).val);
    } else if constexpr (stride == 4) {
      return argon::to_array(simd::load4_duplicate<multivec_type>(ptr).val);
    }
  }

  template <size_t stride>
  ace static std::array<argon_type, stride> LoadInterleaved(const scalar_type* ptr) {
    static_assert(stride > 1 && stride < 5, "De-interleaving Loads can only be performed with a stride of 2, 3, or 4");
    using multivec_type = helpers::MultiVector_t<VectorType, stride>;

    if constexpr (stride == 2) {
      return argon::to_array(simd::load2<multivec_type>(ptr).val);
    } else if constexpr (stride == 3) {
      return argon::to_array(simd::load3<multivec_type>(ptr).val);
    } else if constexpr (stride == 4) {
      return argon::to_array(simd::load4<multivec_type>(ptr).val);
    }
  }

  template <size_t lane, size_t stride>
  ace static std::array<argon_type, stride> LoadToLaneInterleaved(helpers::MultiVector_t<VectorType, stride> multi,
                                                                  const scalar_type* ptr) {
    if constexpr (stride == 2) {
      if constexpr (simd::is_quadword_v<VectorType>) {
        return argon::to_array(simd::load2_lane_quad<lane>(ptr, multi).val);
      } else {
        return argon::to_array(simd::load2_lane<lane>(ptr, multi).val);
      }
    } else if constexpr (stride == 3) {
      if constexpr (simd::is_quadword_v<VectorType>) {
        return argon::to_array(simd::load3_lane_quad<lane>(ptr, multi).val);
      } else {
        return argon::to_array(simd::load3_lane<lane>(ptr, multi).val);
      }
    } else if constexpr (stride == 4) {
      if constexpr (simd::is_quadword_v<VectorType>) {
        return argon::to_array(simd::load4_lane_quad<lane>(ptr, multi).val);
      } else {
        return argon::to_array(simd::load4_lane<lane>(ptr, multi).val);
      }
    }
  }

  template <size_t lane, size_t stride>
  ace static std::array<argon_type, stride> LoadToLaneInterleaved(std::array<argon_type, stride> multi,
                                                                  const scalar_type* ptr) {
    using multivec_type = helpers::MultiVector_t<VectorType, stride>;
    return LoadToLaneInterleaved<lane, stride>(*(multivec_type*)multi.data(), ptr);
  }

  /**
   * @brief Perform a Load-Gather of interleaved elements
   *
   * @note On NEON this incurs a writeback + load penalty
   *
   * @tparam stride the distance between similar elements
   * @param base_ptr the address to use as a base for the gather operation
   * @param offset_vector a vector of offset values that are added to base_ptr to get the address to load
   * @return std::array<argon_type, stride> An array of vectors from the resulting interleaved loads
   */
  template <size_t stride, simd::is_vector_type IntrinsicType>
  ace static std::array<argon_type, stride> LoadGatherInterleaved(const scalar_type* base_ptr,
                                                                  IntrinsicType offset_vector) {
    using offset_type = simd::Scalar_t<IntrinsicType>;
    static_assert(stride > 1 && stride < 5, "De-interleaving Loads can only be performed with a stride of 2, 3, or 4");
    static_assert(std::is_unsigned_v<offset_type>, "Offset elements must be unsigned values");
    static_assert((sizeof(IntrinsicType) / sizeof(offset_type)) == lanes,
                  "Number of elements in offset vector must match number of elements in destination vector");
    std::array<argon_type, stride> multi{};
    helpers::consteval_for<0, lanes, 1>([&]<int i>() {  //<
      offset_type lane_val = simd::get_lane<i>(offset_vector);
      multi = LoadToLaneInterleaved<i, stride>(multi, base_ptr + lane_val);
    });
    return multi;
  }

  template <size_t stride, typename T>
  ace static std::array<argon_type, stride> LoadGatherInterleaved(const scalar_type* base_ptr, T offset_vector) {
    return argon_type::template LoadGatherInterleaved<stride, typename T::VectorType>(base_ptr, offset_vector);
  }

  /**
   * @brief Load n vectors from a single contiguous set of memory.
   *
   * @tparam n The number of vectors to load
   * @param ptr The pointer to the location in memory to load from
   * @return std::array An array of NEON vectors.
   */
  template <size_t n>
  ace static std::array<argon_type, n> LoadMulti(const scalar_type* ptr) {
    static_assert(n > 1 && n < 5, "LoadMulti can only be performed with a size of 2, 3, or 4");
#if defined(__clang__) || (__GNUC__ > 13)
    if constexpr (n == 2) {
      return argon::to_array(simd::load1_x2(ptr).val);
    } else if constexpr (n == 3) {
      return argon::to_array(simd::load1_x3(ptr).val);
    } else if constexpr (n == 4) {
      return argon::to_array(simd::load1_x4(ptr).val);
    }
#else
    if constexpr (n == 2) {
      auto a = simd::load1(ptr);
      auto b = simd::load1(ptr + lanes);
      return {a, b};
    } else if constexpr (n == 3) {
      auto a = simd::load1(ptr);
      auto b = simd::load1(ptr + lanes);
      auto c = simd::load1(ptr + 2 * lanes);
      return {a, b, c};
    } else if constexpr (n == 4) {
      auto a = simd::load1(ptr);
      auto b = simd::load1(ptr + lanes);
      auto c = simd::load1(ptr + 2 * lanes);
      auto d = simd::load1(ptr + 3 * lanes);
      return {a, b, c, d};
    }
#endif
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
             std::is_same_v<signed_vector, helpers::ArgonFor_t<simd::make_signed_t<VectorType>>>)
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
    return std::bit_cast<std::array<argon_type, 2>>(std::to_array(simd::transpose(vec_, b.vec()).val));
  }

  std::array<argon_type, 2> UnzipWith(argon_type b) {
    return std::bit_cast<std::array<argon_type, 2>>(std::to_array(simd::transpose(vec_, b.vec()).val));
  }

  std::tuple<argon_type, argon_type> TransposeWith(argon_type b) const {
    auto result = simd::transpose(vec_, b.vec());
    return std::tuple<argon_type, argon_type>(result.val[0], result.val[1]);
  }

  ace static int size() { return lanes; }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<scalar_type(scalar_type)>>
  ace argon_type map(FuncType body) const {
    VectorType out;
    for (size_t i = 0; i < lanes; ++i) {
      out[i] = body(vec_[i]);
    }
    return out;
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<scalar_type(scalar_type, int)>>
  ace argon_type map_with_index(FuncType body) const {
    VectorType out;
    for (size_t i = 0; i < lanes; ++i) {
      out[i] = body(vec_[i], i);
    }
    return out;
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<scalar_type(scalar_type, scalar_type)>>
  ace argon_type map2(argon_type other, FuncType body) const {
    VectorType out;
    for (size_t i = 0; i < lanes; ++i) {
      out[i] = body(vec_[i], other.vec_[i]);
    }
    return out;
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void(scalar_type&)>>
  ace argon_type each_lane(FuncType body) {
    VectorType out = vec_;
    for (size_t i = 0; i < lanes; ++i) {
      body(out[i]);
    }
    return out;
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void(scalar_type&, int)>>
  ace argon_type each_lane_with_index(FuncType body) {
    VectorType out = vec_;
    for (size_t i = 0; i < lanes; ++i) {
      body(out[i], i);
    }
    return out;
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void()>>
  ace void if_lane(FuncType true_branch) {
    for (size_t i = 0; i < lanes; ++i) {
      if (vec_[i] != 0) {
        true_branch();
      }
    }
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void()>>
  ace void if_else_lane(FuncType true_branch, FuncType false_branch) {
    for (size_t i = 0; i < lanes; ++i) {
      if (vec_[i] != 0) {
        true_branch();
      } else {
        false_branch();
      }
    }
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void(int)>>
  ace void if_lane_with_index(FuncType true_branch) {
    for (size_t i = 0; i < lanes; ++i) {
      if (vec_[i] != 0) {
        true_branch(i);
      }
    }
  }

  template <typename FuncType1, typename FuncType2>
    requires std::convertible_to<FuncType1, std::function<void(int)>> &&
             std::convertible_to<FuncType2, std::function<void(int)>>
  ace void if_else_lane_with_index(FuncType1 true_branch, FuncType2 false_branch) {
    for (size_t i = 0; i < lanes; ++i) {
      if (vec_[i] != 0) {
        true_branch(i);
      } else {
        false_branch(i);
      }
    }
  }

  ace bool any() {
    for (size_t i = 0; i < lanes; ++i) {
      if (vec_[i]) {
        return true;
      }
    }
    return false;
  }

  ace bool all() {
    auto nonzero = TestNonzero();
    for (size_t i = 0; i < lanes; ++i) {
      if (nonzero[i] == 0) {
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
  VectorType vec_;
};

template <size_t LaneIndex, typename VectorType>
class ConstLane {
  using scalar_type = simd::Scalar_t<VectorType>;
  using type = ConstLane<LaneIndex, VectorType>;
  using argon_type = helpers::ArgonFor_t<VectorType>;

 public:
  ace ConstLane(VectorType& vec) : vec_{vec} {}
  ace operator scalar_type() const { return simd::get_lane<LaneIndex>(vec_); }
  ace argon_type operator=(const scalar_type b) { return Set(b); }
  ace argon_type Load(scalar_type* ptr) {
    if constexpr (simd::is_quadword_v<VectorType>) {
      return vec_ = simd::load1_lane_quad<LaneIndex>(vec_, ptr);
    } else {
      return vec_ = simd::load1_lane<LaneIndex>(vec_, ptr);
    }
  }
  ace argon_type Set(const scalar_type b) { return vec_ = simd::set_lane<LaneIndex>(vec_, b); }

#if __ARM_ARCH >= 8
  ace VectorType& vec() { return vec_; }
  ace const int lane() { return LaneIndex; }
#else
  ace VectorType& vec() {
    if constexpr (simd::is_doubleword_v<VectorType>) {
      return vec_;
    } else if constexpr (simd::is_quadword_v<VectorType>) {
      if (LaneIndex >= ArgonHalf<scalar_type>::lanes) {
        return simd::get_high(vec());
      } else {
        return simd::get_low(vec());
      }
    }
  }
  ace int lane() {
    if constexpr (simd::is_doubleword_v<VectorType>) {
      return LaneIndex;
    } else if constexpr (simd::is_quadword_v<VectorType>) {
      if (LaneIndex >= ArgonHalf<scalar_type>::lanes) {
        return (LaneIndex - ArgonHalf<scalar_type>::lanes);
      } else {
        return LaneIndex;
      }
    }
  }
#endif
 private:
  VectorType& vec_;
};

template <typename VectorType>
class Lane {
  using scalar_type = simd::Scalar_t<VectorType>;
  using type = Lane<VectorType>;
  using argon_type = helpers::ArgonFor_t<VectorType>;

 public:
  ace Lane(VectorType& vec, const int lane) : vec_{vec}, lane_{lane} {}
  ace operator scalar_type() const { return simd::get_lane(vec_, lane_); }
  ace argon_type operator=(const scalar_type b) { return Set(b); }
  ace argon_type Load(scalar_type* ptr) { return vec_ = simd::load1_lane(vec_, lane_, ptr); }
  ace argon_type Set(const scalar_type b) { return vec_ = simd::set_lane(vec_, lane_, b); }

#if __ARM_ARCH >= 8
  ace VectorType& vec() { return vec_; }
  ace const int lane() { return lane_; }
#else
  ace VectorType& vec() {
    if constexpr (simd::is_doubleword_v<VectorType>) {
      return vec_;
    } else if constexpr (simd::is_quadword_v<VectorType>) {
      if (lane_ >= ArgonHalf<scalar_type>::lanes) {
        return simd::get_high(vec());
      } else {
        return simd::get_low(vec());
      }
    }
  }
  ace int lane() {
    if constexpr (simd::is_doubleword_v<VectorType>) {
      return lane_;
    } else if constexpr (simd::is_quadword_v<VectorType>) {
      if (lane_ >= ArgonHalf<scalar_type>::lanes) {
        return (lane_ - ArgonHalf<scalar_type>::lanes);
      } else {
        return lane_;
      }
    }
  }
#endif

 private:
  VectorType& vec_;
  int lane_;
};

}  // namespace argon

/**
 * Lane deconstruction feature
 */
namespace std {
template <typename T>
struct tuple_size<argon::Vector<T>> {
  static constexpr size_t value = argon::Vector<T>::lanes;
};

template <size_t Index, typename T>
struct tuple_element<Index, argon::Vector<T>> {
  static_assert(Index < argon::Vector<T>::lanes);
  using type = argon::Vector<T>::lane_type;
};
}  // namespace std

#undef ace
#undef simd
