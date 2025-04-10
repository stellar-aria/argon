#pragma once
#include <array>
#include <bit>
#include <cmath>
#include <functional>
#include <tuple>
#include <type_traits>
#include <utility>
#include "arm_simd.hpp"
#include "arm_simd/helpers.hpp"
#include "arm_simd/helpers/multivector.hpp"
#include "arm_simd/helpers/scalar.hpp"
#include "arm_simd/helpers/vec64.hpp"
#include "features.h"
#include "helpers.hpp"
#include "helpers/bool.hpp"
#include "helpers/to_array.hpp"
#include "lane.hpp"

#ifdef __ARM_FEATURE_MVE
#define simd mve
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

/// @brief Represents a SIMD vector with various operations.
/// @tparam VectorType The type of the SIMD vector. (e.g. int32x4_t, float32x4_t)
/// @details This class provides a wrapper around SIMD vector types, allowing for object-oriented operations on the
/// vector.
template <typename VectorType>
class Vector {
 public:
  template <size_t LaneIndex>
  using const_lane_type = ConstLane<LaneIndex, VectorType>;     ///< The type of a single lane of the SIMD vector.
  using lane_type = Lane<VectorType>;                           ///< The type of a single lane of the SIMD vector.
  using scalar_type = simd::Scalar_t<VectorType>;               ///< The scalar type of the SIMD vector.
  using vector_type = VectorType;                               ///< The SIMD vector type.
  using argon_type = helpers::ArgonFor_t<VectorType>;           ///< The Argon type for the SIMD vector.
  using predicate_type = Bool_t<VectorType>;                    ///< The type of a boolean SIMD vector.
  using argon_bool_type = helpers::ArgonFor_t<predicate_type>;  ///< The Argon type for the boolean vector.

  /// @brief The number of lanes in the SIMD vector.
  static constexpr size_t lanes = (simd::is_quadword_v<VectorType> ? 16 : 8) / sizeof(scalar_type);

  /// @brief The default constructor for the Vector class.
  constexpr Vector() = default;

  constexpr Vector(Vector&& other) = default;                  ///< Move constructor for the Vector class.
  constexpr Vector(const Vector& other) = default;             ///< Copy constructor for the Vector class.
  constexpr Vector& operator=(Vector&& other) = default;       ///< Move assignment operator for the Vector class.
  constexpr Vector& operator=(const Vector& other) = default;  ///< Copy assignment operator for the Vector class.

  /// @brief Constructs a Vector from a SIMD vector type.
  /// @param vector The SIMD vector to construct from.
  ace Vector(VectorType vector) : vec_{std::move(vector)} {};

  /// @brief Constructs a Vector from a scalar value.
  /// @param scalar The scalar value to construct from.
  /// @details This constructor duplicates the scalar value across all lanes of the SIMD vector.
  ace Vector(scalar_type scalar) : vec_(FromScalar(scalar)) {};

#ifndef ARGON_PLATFORM_MVE
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
#endif

  template <typename... ArgTypes>
    requires(sizeof...(ArgTypes) > 1)
  ace Vector(ArgTypes... args) : vec_{std::forward<ArgTypes>(args)...} {}

  /// @brief Constructs a Vector from a scalar pointer.
  /// @param ptr The pointer to the scalar value to construct from.
  /// @details This constructor loads the scalar value from the pointer and duplicates it
  /// across all lanes of the SIMD vector.
  /// @return The constructed SIMD vector.
  ace static argon_type LoadScalar(const scalar_type* ptr) { return LoadCopy(ptr); }

  /// @brief Constructs a Vector from a scalar value.
  /// @param scalar The scalar value to construct from.
  /// @details This constructor duplicates the scalar value across all lanes of the SIMD vector.
  /// @return The constructed SIMD vector.
  ace static argon_type FromScalar(scalar_type scalar) {
#ifdef ARGON_PLATFORM_MVE
    return simd::duplicate(scalar);
#else
    return simd::duplicate<VectorType>(scalar);
#endif
  }

  /// @brief Constructs a Vector from a Lane object.
  /// @param lane The Lane object to construct from.
  /// @details This constructor duplicates the lane value across all lanes of the SIMD vector.
  /// @return The constructed SIMD vector.
  template <simd::is_vector_type IntrinsicType>
  ace static argon_type FromLane(argon::Lane<IntrinsicType> lane) {
#ifdef ARGON_PLATFORM_MVE
    return simd::duplicate(lane.Get());
#else
    return simd::duplicate_lane(lane.vec(), lane.lane());
#endif
  }

  /// @brief Constructs a Vector from a ConstLane object.
  /// @param lane The ConstLane object to construct from.
  /// @details This constructor duplicates the lane value across all lanes of the SIMD vector.
  /// @return The constructed SIMD vector.
  template <size_t LaneIndex>
  ace static argon_type FromLane(argon::ConstLane<LaneIndex, VectorType> lane) {
#ifdef ARGON_PLATFORM_MVE
    return simd::duplicate(lane.Get());
#else
    if constexpr (simd::is_quadword_v<VectorType>) {
      return simd::duplicate_lane_quad<Lane>(lane.vec());
    } else {
      return simd::duplicate_lane<Lane>(lane.vec());
    }
#endif
  }

  /// @brief Constructs a Vector from an incrementing sequence.
  /// @param start The starting value of the sequence.
  /// @param step The step size of the sequence.
  /// @return The constructed SIMD vector.
  /// @details This constructor creates a SIMD vector with lanes containing values from start to start + (lanes - 1) *
  /// step.
  ace static argon_type Iota(scalar_type start, scalar_type step = 1) {
    // TODO: Remove this once MSVC 19.44 is released.
#if __cpp_if_consteval >= 202106L
    if consteval {
      VectorType out;
      utility::constexpr_for<0, lanes, 1>([&](size_t i) {  //
        out[i] = start + i * step;
      });
      return out;
    } else {
      return Argon{start}.MultiplyAdd(step, VectorType{0, 1, 2, 3});
    }
#else
    return Argon{start}.MultiplyAdd(step, VectorType{0, 1, 2, 3});
#endif
  }

  /// @brief Constructs a Vector from a function that generates values.
  /// @param body The function that generates the values.
  /// @details This constructor creates a SIMD vector with lanes containing values generated by the function.
  /// @return The constructed SIMD vector.
  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<scalar_type()>>
  ace static argon_type Generate(FuncType body) {
    VectorType out;
    utility::constexpr_for<0, lanes, 1>([&](size_t i) {  //
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
    utility::constexpr_for<0, lanes, 1>([&](size_t i) {  //
      out[i] = body(i);
    });
    return out;
  }

  /// Negate the SIMD vector and return the result.
  ace argon_type operator-() const { return Negate(); }

  /// Add a vector and return the result.
  ace argon_type operator+(argon_type b) const { return Add(b); }

  /// Subtract a vector and return the result.
  ace argon_type operator-(argon_type b) const { return Subtract(b); }

  /// Multiply a vector and return the result.
  ace argon_type operator*(argon_type b) const { return Multiply(b); }

  /// Divide a vector and return the result.
  ace argon_type operator/(argon_type b) const { return Divide(b); }

  /// Compare two vectors for equality.
  ace argon_bool_type operator==(argon_type b) const { return Equal(b); }

  /// Compare two vectors for inequality.
  ace argon_bool_type operator!=(argon_type b) const { return ~Equal(b); }

  /// Compare two vectors, checking if this vector is less than the other.
  ace argon_bool_type operator<(argon_type b) const { return LessThan(b); }

  /// Compare two vectors, checking if this vector is greater than the other.
  ace argon_bool_type operator>(argon_type b) const { return GreaterThan(b); }

  /// Compare two vectors, checking if this vector is less than or equal to the other.
  ace argon_bool_type operator<=(argon_type b) const { return LessThanOrEqual(b); }

  /// Compare two vectors, checking if this vector is greater than or equal to the other.
  ace argon_bool_type operator>=(argon_type b) const { return GreaterThanOrEqual(b); }

  /// Increment the vector by 1 and return the result.
  ace argon_type operator++() const { return Add(1); }

  /// Decrement the vector by 1 and return the result.
  ace argon_type operator--() const { return Subtract(1); }

  /// Bitwise AND two vectors and return the result.
  ace argon_type operator&(argon_type b) const { return BitwiseAnd(b); }

  /// Bitwise OR two vectors and return the result.
  ace argon_type operator|(argon_type b) const { return BitwiseOr(b); }

  /// Bitwise XOR two vectors and return the result.
  ace argon_type operator^(argon_type b) const { return BitwiseXor(b); }

  /// Bitwise NOT the vector and return the result.
  ace argon_type operator~() const { return BitwiseNot(); }

  /// Access a lane of the vector by index.
  ace Lane<const VectorType> operator[](const size_t i) const { return GetLane(i); }

  /// Access a lane of the vector by index.
  ace lane_type operator[](const size_t i) { return GetLane(i); }

  /// Shift the elements of the vector to the right by a specified number of bits.
  ace argon_type operator>>(const int i) const { return ShiftRight(i); }

  /// Shift the elements of the vector to the left by a specified number of bits.
  ace argon_type operator<<(const int i) const { return ShiftLeft(i); }

  /// Get the underlying SIMD vector.
  [[gnu::always_inline]] constexpr VectorType vec() const { return vec_; }

  /// Convert the vector to the underlying SIMD vector type.
  [[gnu::always_inline]] constexpr operator VectorType() const { return vec_; }

  /// @brief Convert the vector to an array of scalar values.
  /// @return An array of scalar values representing the vector.
  ace std::array<scalar_type, lanes> to_array() {
    std::array<scalar_type, lanes> out;
    simd::store1(out.data(), vec_);
    return out;
  }

  /// @brief Get a single lane of the vector by index.
  /// @param i The index of the lane to get.
  /// @return The value of the specified lane in the SIMD vector.
  /// @note If you know the index of the lane at compile time, you should use GetLane<LaneIndex>() instead.
  ace const lane_type GetLane(const size_t i) const {
#ifdef ARGON_PLATFORM_MVE
    return vec_[i];
#else
    return {vec_, static_cast<int>(i)};
#endif
  }
  ace lane_type GetLane(const size_t i) {
#ifdef ARGON_PLATFORM_MVE
    return vec_[i];
#else
    return {vec_, static_cast<int>(i)};
#endif
  }

  /// @brief Get a single lane of the vector by index.
  /// @param i The index of the lane to get.
  /// @return The value of the specified lane in the SIMD vector.
  ace const lane_type GetLane(const int i) const {
#ifdef ARGON_PLATFORM_MVE
    return vec_[i];
#else
    return {vec_, i};
#endif
  }

  ace lane_type GetLane(const int i) {
#ifdef ARGON_PLATFORM_MVE
    return vec_[i];
#else
    return {vec_, i};
#endif
  }

  /// @brief Get a single lane of the vector by index.
  /// @tparam LaneIndex The index of the lane to get.
  /// @return The value of the specified lane in the SIMD vector.
  template <size_t LaneIndex>
  ace const const_lane_type<LaneIndex> GetLane() const {
#ifdef ARGON_PLATFORM_MVE
    return vec_[LaneIndex];
#else
    return vec_;
#endif
  }

  template <size_t LaneIndex>
  ace const_lane_type<LaneIndex> GetLane() {
#ifdef ARGON_PLATFORM_MVE
    return vec_[LaneIndex];
#else
    return vec_;
#endif
  }

  /// Get the last lane of the vector.
  ace const_lane_type<lanes - 1> LastLane() { return {vec_, lanes - 1}; }

  /// Shift the elements of the vector to the right by a specified number of bits.
  ace argon_type ShiftRight(const int i) const { return simd::shift_right(vec_, i); }

  /// Shift the elements of the vector to the left by a specified number of bits.
  ace argon_type ShiftLeft(const int i) const { return simd::shift_left(vec_, i); }

  /// Bitwise negate the vector and return the result.
  ace argon_type Negate() const {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return -vec_;
    } else {
      return simd::negate(vec_);
    }
  }

  /// Add two vectors
  ace argon_type Add(argon_type b) const {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ + b.vec_;
    } else {
      return simd::add(vec_, b);
    }
  }

  /// Adds two vectors, halving the result.
  /// @details Equivalent to (a + b) / 2.
  ace argon_type AddHalve(argon_type b) const { return simd::add_halve(vec_, b); }

  /// Adds two vectors, halving and rounding the result.
  /// @details Equivalent to round((a + b) / 2).
  ace argon_type AddHalveRound(argon_type b) const { return simd::add_halve_round(vec_, b); }

  /// Adds two vectors, saturating the result.
  /// @details Equivalent to a + b, but saturates to the maximum value if the result exceeds the maximum representable
  /// value.
  ace argon_type AddSaturate(argon_type b) const { return simd::add_saturate(vec_, b); }

  /// Subtract two vectors
  ace argon_type Subtract(argon_type b) const {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ - b.vec_;
    } else {
      return simd::subtract(vec_, b);
    }
  }

  /// Subtract two vectors, halving the result.
  /// @details Equivalent to (a - b) / 2.
  ace argon_type SubtractHalve(argon_type b) const { return simd::subtract_halve(vec_, b); }

  /// Subtract two vectors, saturating the result.
  ace argon_type SubtractSaturate(argon_type b) const { return simd::subtract_saturate(vec_, b); }

  /// Subtract two vectors, taking the absolute value of the result.
  /// @details Equivalent to |a - b|.
  ace argon_type SubtractAbs(argon_type b) const { return simd::subtract_absolute(vec_, b); }

  /// Subtract two vectors, taking the absolute value of the result and adding a third vector.
  /// @details Equivalent to a + |b - c|
  ace argon_type SubtractAbsAdd(argon_type b, argon_type c) const {
#ifdef ARGON_PLATFORM_MVE
    return mve::add(vec_, mve::subtract_absolute(b, c));
#else
    return neon::subtract_absolute_add(vec_, b, c);
#endif
  }

  /// Multiply two vectors
  ace argon_type Multiply(argon_type b) const {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ * b.vec_;
    } else {
      return simd::multiply(vec_, b);
    }
  }

  /// Multiply a vector by a scalar value
  ace argon_type Multiply(scalar_type b) const {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ * b;
    } else {
      return simd::multiply(vec_, b);
    }
  }

#ifndef ARGON_PLATFORM_MVE
  /// Multiply a vector by a lane value
  ace argon_type Multiply(lane_type b) const { return neon::multiply_lane(vec_, b.vec(), b.lane()); }

  ///  Multiply a vector by a lane value
  template <size_t LaneIndex>
  ace argon_type Multiply(const_lane_type<LaneIndex> b) const {
    return neon::multiply_lane(vec_, b.vec(), b.lane());
  }
#endif

  /// Multiply two vectors and add a third vector
  /// @details Equivalent to a + (b * c).
  ace argon_type MultiplyAdd(argon_type b, argon_type c) const {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ + b.vec_ * c.vec_;
    } else {
      return simd::multiply_add(vec_, b, c);
    }
  }

  /// Multiply a vector by a scalar value and add a third vector
  /// @details Equivalent to a + (b * c).
  ace argon_type MultiplyAdd(argon_type b, scalar_type c) const {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ + b.vec_ * c;
    } else {
      return simd::multiply_add(vec_, b, c);
    }
  }

  /// Multiply a vector by a scalar value and add a third vector
  /// @details Equivalent to a + (b * c).
  ace argon_type MultiplyAdd(scalar_type b, argon_type c) const { return MultiplyAdd(c, b); }

#ifndef ARGON_PLATFORM_MVE
  /// Multiply a vector by a lane value and add a third vector
  /// @details Equivalent to a + (b * c).
  ace argon_type MultiplyAdd(argon_type b, lane_type c) const {
    return simd::multiply_add_lane(vec_, b.vec(), c.vec(), c.lane());
  }

  /// Multiply a vector by a lane value and add a third vector
  /// @details Equivalent to a + (b * c).
  ace argon_type MultiplyAdd(lane_type b, argon_type c) const { return MultiplyAdd(c, b); }

  /// Multiply a vector by a lane value and add a third vector
  /// @details Equivalent to a + (b * c).
  template <size_t LaneIndex>
  ace argon_type MultiplyAdd(argon_type b, const_lane_type<LaneIndex> c) const {
    return simd::multiply_add_lane(vec_, b.vec(), c.vec(), c.lane());
  }
  /// Multiply a vector by a lane value and add a third vector
  /// @details Equivalent to a + (b * c).
  template <size_t LaneIndex>
  ace argon_type MultiplyAdd(const_lane_type<LaneIndex> b, argon_type c) const {
    return MultiplyAdd(c, b);
  }
#endif

  /// Multiply two vectors and subtract from a third vector
  /// @details Equivalent to a - (b * c).
  ace argon_type MultiplySubtract(argon_type b, argon_type c) const {
#if ARGON_USE_COMPILER_EXTENSIONS
    return vec_ - b.vec_ * c.vec_;
#else
    return simd::multiply_subtract(vec_, b, c);
#endif
  }

  /// Multiply a vector by a scalar value and subtract from a third vector
  /// @details Equivalent to a - (b * c).
  ace argon_type MultiplySubtract(argon_type b, scalar_type c) const {
#if ARGON_USE_COMPILER_EXTENSIONS
    return vec_ - b.vec_ * c;
#else
    return simd::multiply_subtract(vec_, b, c);
#endif
  }

  /// Multiply a vector by a scalar value and subtract from a third vector
  /// @details Equivalent to a - (b * c).
  ace argon_type MultiplySubtract(scalar_type b, argon_type c) const { return MultiplySubtract(c, b); }

#ifndef ARGON_PLATFORM_MVE
  /// Multiply a vector by a lane value and subtract from a third vector
  /// @details Equivalent to a - (b * c).
  ace argon_type MultiplySubtract(argon_type b, lane_type c) const {
    return simd::multiply_subtract_lane(vec_, b.vec(), c.vec(), c.lane());
  }
#endif

  /// Multiply two Q31 fixed-point vectors, returning a fixed-point product
  /// @details This is equivalent to ((uint64_t)a * b) >> 31
  ace argon_type MultiplyQ31(argon_type v) const { return simd::multiply_double_saturate_high(vec_, v); }

  /// Multiply a Q31 fixed-point vector by a scalar value, returning a fixed-point product
  /// @details This is equivalent to ((uint64_t)a * b) >> 31
  ace argon_type MultiplyQ31(scalar_type s) const { return simd::multiply_double_saturate_high(vec_, s); }

#ifndef ARGON_PLATFORM_MVE
  /// Multiply a Q31 fixed-point vector by a lane value, returning a fixed-point product
  /// @details This is equivalent to ((uint64_t)a * b) >> 31
  ace argon_type MultiplyQ31(lane_type l) const {
    return simd::multiply_double_saturate_high_lane(vec_, l.vec(), l.lane());
  }
#endif

  /// Multiply two fixed-point vectors, returning a fixed-point product
  /// @details This is equivalent to round(a * b) >> 31
  ace argon_type MultiplyRoundQ31(argon_type v) const { return simd::multiply_double_round_saturate_high(vec_, v); }

  /// Multiply a fixed-point vector by a scalar value, returning a fixed-point product
  /// @details This is equivalent to round(a * b) >> 31
  ace argon_type MultiplyRoundQ31(scalar_type s) const { return simd::multiply_double_round_saturate_high(vec_, s); }

#ifndef ARGON_PLATFORM_MVE
  /// Multiply a fixed-point vector by a lane value, returning a fixed-point product
  /// @details This is equivalent to round(a * b) >> 31
  ace argon_type MultiplyRoundQ31(lane_type l) const {
    return simd::multiply_double_round_saturate_high_lane(vec_, l.vec(), l.lane());
  }
#endif

  /// Get the absolute value of the vector.
  ace argon_type Absolute() const { return simd::abs(vec_); }

  /// @brief 1 / value, using an estimate for speed
  /// @note This is not a precise reciprocal, but it is fast and useful for many applications
  ace argon_type ReciprocalEstimate() const
    requires std::floating_point<scalar_type> || std::is_same_v<scalar_type, uint32_t>
  {
#ifdef ARGON_PLATFORM_MVE
    if constexpr (std::is_same_v<scalar_type, uint32_t>) {
      std::numeric_limits<uint32_t>::max() / vec_;
    } else {
      return 1.f / vec_;
    }
#else
    return simd::reciprocal_estimate(vec_);
#endif
  }

  /// Multiply-add three fixed-point vectors, returning a fixed-point sum
  /// @details This is equivalent to a + ((b * c) >> 31)
  template <typename arg_type>
    requires(is_one_of<arg_type, argon_type, scalar_type, lane_type> || std::is_convertible_v<arg_type, argon_type> ||
             std::is_convertible_v<arg_type, scalar_type>)
  ace argon_type MultiplyAddQ31(argon_type b, arg_type c) const {
    return Add(b.MultiplyQ31(c));
  }

  /// Multiply-round-add three fixed-point vectors, returning a fixed-point sum
  /// @details This is equivalent to a + (rnd(b * c) >> 31)
  template <typename arg_type>
    requires(is_one_of<arg_type, argon_type, scalar_type, lane_type> || std::is_convertible_v<arg_type, argon_type> ||
             std::is_convertible_v<arg_type, scalar_type>)
  ace argon_type MultiplyRoundAddQ31(argon_type b, arg_type c) const {
    return Add(b.MultiplyRoundQ31(c));
  }

#ifdef __aarch64__
  /// Divide two vectors
  ace argon_type Divide(argon_type b) const {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ / b.vec_;
    } else {
      return simd::divide(vec_, b);
    }
  }
#else
  /// Divide two vectors
  ace argon_type Divide(argon_type b) const {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ / b.vec_;
    } else {
      return this->map2(b, [](scalar_type lane1, scalar_type lane2) { return lane1 / lane2; });
    }
  }
#endif

  /// Get the modulo of two vectors
  /// @details Equivalent to a % b.
  ace argon_type Modulo(argon_type b) const {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ % b.vec_;
    } else if constexpr (std::floating_point<scalar_type>) {
      return this->map2(b, [](scalar_type lane1, scalar_type lane2) { return std::fmod(lane1, lane2); });
    } else {
      return this->map2(b, [](scalar_type lane1, scalar_type lane2) { return lane1 % lane2; });
    }
  }

  /// Get the modulo of a vector and a scalar value
  /// @details Equivalent to a % b.
  ace argon_type Modulo(scalar_type b) const {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ % b;
    } else {
      return this->map([b](scalar_type lane1) { return std::fmod(lane1, b); });
    }
  }

  /// Compare the lanes of two vectors, copying the larger of each lane to the result
  /// @details Equivalent to a > b ? a : b
  ace argon_type Max(argon_type b) const {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ > b.vec_ ? vec_ : b.vec_;
    } else {
      return simd::max(vec_, b);
    }
  }
  /// Compare the lanes of two vectors, copying the smaller of each lane to the result
  /// @details Equivalent to a < b ? a : b
  ace argon_type Min(argon_type b) const {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ < b.vec_ ? vec_ : b.vec_;
    } else {
      return simd::min(vec_, b);
    }
  }

  /// Compare the lanes of two vectors, setting the result lane's bits to ON if are equal
  /// @details Equivalent to a == b ? 0xFFFFFFFF : 0x00000000
  ace argon_bool_type Equal(argon_type b) const { return simd::equal(vec_, b); }

  /// Compare the lanes of two vectors, setting the result lane's bits to ON if a is greater than or equal to b
  /// @details Equivalent to a >= b ? 0xFFFFFFFF : 0x00000000
  ace argon_bool_type GreaterThanOrEqual(argon_type b) const { return simd::greater_than_or_equal(vec_, b); }

  /// Compare the lanes of two vectors, setting the result lane's bits to ON if a is less than or equal to b
  /// @details Equivalent to a <= b ? 0xFFFFFFFF : 0x00000000
  ace argon_bool_type LessThanOrEqual(argon_type b) const { return simd::less_than_or_equal(vec_, b); }

  /// Compare the lanes of two vectors, setting the result lane's bits to ON if a is greater than b
  /// @details Equivalent to a > b ? 0xFFFFFFFF : 0x00000000
  ace argon_bool_type GreaterThan(argon_type b) const { return simd::greater_than(vec_, b); }

  /// Compare the lanes of two vectors, setting the result lane's bits to ON if a is less than b
  /// @details Equivalent to a < b ? 0xFFFFFFFF : 0x00000000
  ace argon_bool_type LessThan(argon_type b) const { return simd::less_than(vec_, b); }

  /// Shift the elemnets of the vector to the left by a specified number of bits.
  /// @details Equivalent to a << b.
  ace argon_type ShiftLeft(helpers::ArgonFor_t<simd::make_signed_t<VectorType>> b) const
    requires std::is_integral_v<scalar_type>
  {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ << b.vec_;
    } else {
      return simd::shift_left(vec_, b.vec_);
    }
  }

  /// Shift the elements of the vector to the left by a specified number of bits.
  /// @details Equivalent to a << b.
  ace argon_type ShiftLeft(std::make_signed_t<scalar_type> n) const
    requires std::is_integral_v<scalar_type>
  {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ << n;
    } else {
      helpers::ArgonFor_t<simd::make_signed_t<VectorType>> b{n};
      return simd::shift_left(vec_, b.vec_);
    }
  }

  /// Shift the elements of the vector to the left by a specified number of bits.
  /// @details Equivalent to a << b.
  template <int n>
  ace argon_type ShiftLeft() const {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ << n;
    } else {
      return simd::shift_left<n>(vec_);
    }
  }

  /// Shift the elements of the vector to the left by a specified number of bits, saturating the result.
  ace argon_type ShiftLeftSaturate(helpers::ArgonFor_t<simd::make_signed_t<VectorType>> b) const
    requires(std::is_integral_v<scalar_type>)
  {
    return simd::shift_left_saturate(vec_, b);
  }

  /// Shift the elements of the vector to the left by a specified number of bits, rounding the result.
  ace argon_type ShiftLeftRound(argon_type b) const { return simd::shift_left_round(vec_, b); }

  /// Shift the elements of the vector to the left by a specified number of bits, rounding and saturating the result.
  ace argon_type ShiftLeftRoundSaturate(argon_type b) const { return simd::shift_left_round_saturate(vec_, b); }

  /// Shift the elements of the vector to the left by a specified number of bits, saturating the result.
  template <int n>
  ace argon_type ShiftLeftSaturate() const {
    return simd::shift_left_saturate<n>(vec_);
  }

  /// Shift the elements of the vector to the left by a specified number of bits, and then OR the result with another
  /// vector masked to the number of shift bits.
  /// @details Equivalent to (a << b) | (c & ((1 << b) - 1)).
  /// @see
  /// https://developer.arm.com/documentation/ddi0596/2021-03/SIMD-FP-Instructions/SLI--Shift-Left-and-Insert--immediate--
  template <int n>
  ace argon_type ShiftLeftInsert(argon_type b) const {
    return simd::shift_left_insert<n>(vec_, b);
  }

  /// Shift the elements of the vector to the right by a specified number of bits.
  template <int n>
  ace argon_type ShiftRight() const {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ >> n;
    } else {
      return simd::shift_right<n>(vec_);
    }
  }

  /// Shift the elements of the vector to the right by a specified number of bits, rounding the result.
  template <int n>
  ace argon_type ShiftRightRound() const {
    return simd::shift_right_round<n>(vec_);
  }

  /// Shift the elements of the `b` vector to the right by a specified number of bits, and then add the result to this
  /// vector
  /// @details Equivalent to a + (b >> n).
  template <int n>
  ace argon_type ShiftRightAccumulate(argon_type b) const {
#ifdef ARGON_PLATFORM_MVE
    return vec_ + (b >> n);
#else
    return simd::shift_right_accumulate<n>(vec_, b);
#endif
  }

  /// Shift the elements of the `b` vector to the right by a specified number of bits, and then add the result to this
  /// vector
  /// @details Equivalent to a + (b >> n).
  template <int n>
  ace argon_type ShiftRightAccumulateRound(argon_type b) const {
#ifdef ARGON_PLATFORM_MVE
    return vec_ + mve::shift_right_round<n>(b);
#else
    return simd::shift_right_accumulate_round<n>(vec_, b);
#endif
  }

  /// Shift the elements of the vector to the right by a specified number of bits, ORing the result with the vector
  /// masked to the number of shift bits.
  /// @details Equivalent to (a >> b) | (c & ~((1 << b) - 1)).
  template <int n>
  ace argon_type ShiftRightInsert(argon_type b) const {
    return simd::shift_right_insert<n>(vec_, b);
  }

  /// Load a vector from a pointer
  ace static argon_type Load(const scalar_type* ptr) {
#ifdef ARGON_PLATFORM_MVE
    return mve::load1(ptr);
#else
    return neon::load1<VectorType>(ptr);
#endif
  }

  /// Load a vector from a pointer, duplicating the value across all lanes
  ace static argon_type LoadCopy(const scalar_type* ptr) {
#ifdef ARGON_PLATFORM_MVE
    scalar_type val = *ptr;
    VectorType vec;
    utility::constexpr_for<0, lanes, 1>([val, &vec]<int i>() { vec[i] = val; });
#else
    return simd::load1_duplicate<VectorType>(ptr);
#endif
  }

  ///@brief Using a base address and a vector of offset bytes and a base pointer, create a new vector
  ///@note On NEON this incurs a writeback + load penalty
  ///@param base The address to index from
  ///@param offset_vector A vector of offset indices
  ///@return A new vector constructed from the various indices
  ace static argon_type LoadGatherOffsetBytes(
      const scalar_type* base,
      helpers::ArgonFor_t<simd::make_unsigned_t<Bool_t<VectorType>>> offset_vector) {
#ifdef ARGON_PLATFORM_MVE
    static_assert(
        sizeof(scalar_type) == 1 || sizeof(scalar_type) == 2 || sizeof(scalar_type) == 4 || sizeof(scalar_type) == 8,
        "Unsupported size for gather load");

    if constexpr (sizeof(scalar_type) == 1) {
      return mve::load_byte_gather_offset(base, offset_vector);
    } else if constexpr (sizeof(scalar_type) == 2) {
      return mve::load_halfword_gather_offset(base, offset_vector);
    } else if constexpr (sizeof(scalar_type) == 4) {
      return mve::load_word_gather_offset(base, offset_vector);
    } else if constexpr (sizeof(scalar_type) == 8) {
      return mve::load_doubleword_gather_offset(base, offset_vector);
    }
#else
    argon_type destination;
    utility::constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      auto lane_val = neon::get_lane<i>(offset_vector);
      destination = destination.template LoadToLane<i>(base + (lane_val * sizeof(scalar_type)));
    });
    return destination;
#endif
  }

  ///@brief Using a base address and a vector of offset indices and a base pointer, create a new vector
  ///@note On NEON this incurs a writeback + load penalty
  ///@param base The address to index from
  ///@param offset_vector A vector of offset indices
  ///@return A new vector constructed from the various indices
  ace static argon_type LoadGatherOffsetIndex(
      const scalar_type* base,
      helpers::ArgonFor_t<simd::make_unsigned_t<Bool_t<VectorType>>> offset_vector) {
#ifdef ARGON_PLATFORM_MVE
    static_assert(
        sizeof(scalar_type) == 1 || sizeof(scalar_type) == 2 || sizeof(scalar_type) == 4 || sizeof(scalar_type) == 8,
        "Unsupported size for gather load");

    if constexpr (sizeof(scalar_type) == 1) {
      return mve::load_byte_gather_offset(base, offset_vector);
    } else if constexpr (sizeof(scalar_type) == 2) {
      return mve::load_halfword_gather_offset(base, offset_vector * sizeof(scalar_type));
    } else if constexpr (sizeof(scalar_type) == 4) {
      return mve::load_word_gather_offset(base, offset_vector * sizeof(scalar_type));
    } else if constexpr (sizeof(scalar_type) == 8) {
      return mve::load_doubleword_gather_offset(base, offset_vector * sizeof(scalar_type));
    }
#else
    argon_type destination;
    utility::constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      auto lane_val = neon::get_lane<i>(offset_vector);
      destination = destination.template LoadToLane<i>(base + lane_val);
    });
    return destination;
#endif
  }

  /// @brief Load a lane from a pointer
  /// @param ptr The pointer to load from
  /// @return The new vector
  template <size_t lane>
  ace argon_type LoadToLane(const scalar_type* ptr) {
    argon_type new_argon = *this;
    return new_argon.template GetLane<lane>().Load(ptr);
  }

  /// @brief Load multiple vectors from a pointer, de-interleaving
  /// @tparam stride The interleave stride
  /// @param ptr The pointer to load from
  /// @return The new multi-vector
  /// This is useful for multi-channel audio or RGB image data.
  /// For example: {r0, g0, b0, r1, g1, b1} will become {{r0, r1}, {g0, g1}, {b0, b1}}
  template <size_t stride>
  ace static std::array<argon_type, stride> LoadInterleaved(const scalar_type* ptr) {
#ifdef ARGON_PLATFORM_MVE
    static_assert(stride == 2 || stride == 4,
                  "De-interleaving Loads can only be performed with a stride of 2, 3, or 4");
    if constexpr (stride == 2) {
      return argon::to_array(mve::load2(ptr).val);
    } else if constexpr (stride == 4) {
      return argon::to_array(mve::load4(ptr).val);
    }
#else
    static_assert(stride > 1 && stride < 5, "De-interleaving Loads can only be performed with a stride of 2, 3, or 4");
    using multivec_type = simd::MultiVector_t<VectorType, stride>;
    if constexpr (stride == 2) {
      return argon::to_array(neon::load2<multivec_type>(ptr).val);
    } else if constexpr (stride == 3) {
      return argon::to_array(neon::load3<multivec_type>(ptr).val);
    } else if constexpr (stride == 4) {
      return argon::to_array(neon::load4<multivec_type>(ptr).val);
    }
#endif
  }

  /// @brief Load multiple vectors from a pointer, duplicating the value across all lanes
  /// @tparam stride The interleave stride
  /// @param ptr The pointer to load from
  /// @return The new multi-vector
  /// Example: {r0, g0, b0, r1, g1, b1} will become {{r0, r0}, {g0, g0}, {b0, b0}}
  template <size_t stride>
  ace static std::array<argon_type, stride> LoadCopyInterleaved(const scalar_type* ptr) {
#ifdef ARGON_PLATFORM_MVE
    static_assert(stride == 2 || stride == 4,
                  "De-interleaving LoadCopy can only be performed with a stride of 2, 3, or 4");
    if constexpr (stride == 2) {
      return {mve::duplicate(*ptr++), mve::duplicate(*ptr++)};
    } else if constexpr (stride == 4) {
      return {mve::duplicate(*ptr++), mve::duplicate(*ptr++), mve::duplicate(*ptr++), mve::duplicate(*ptr)};
    }
#else
    static_assert(stride > 1 && stride < 5,
                  "De-interleaving LoadCopy can only be performed with a stride of 2, 3, or 4");
    using multivec_type = simd::MultiVector<VectorType, stride>::type;
    if constexpr (stride == 2) {
      return argon::to_array(simd::load2_duplicate<multivec_type>(ptr).val);
    } else if constexpr (stride == 3) {
      return argon::to_array(simd::load3_duplicate<multivec_type>(ptr).val);
    } else if constexpr (stride == 4) {
      return argon::to_array(simd::load4_duplicate<multivec_type>(ptr).val);
    }
#endif
  }

  /// @brief Load a value from a pointer into a vector at the lane index `lane`, de-interleaving
  /// @tparam lane The lane to load
  /// @tparam stride The interleave stride
  /// @param multi The multi-vector to load into
  /// @param ptr The pointer to load from
  /// @return The new multi-vector
  template <size_t LaneIndex, size_t Stride>
  ace static std::array<argon_type, Stride> LoadToLaneInterleaved(simd::MultiVector_t<VectorType, Stride> multi,
                                                                  const scalar_type* ptr) {
    static_assert(Stride > 1 && Stride < 5, "De-interleaving Loads can only be performed with a stride of 2, 3, or 4");
#ifdef ARGON_PLATFORM_MVE
    auto out = multi;
    utility::constexpr_for<0, Stride, 1>([&]<int i>() {  //<
      out.val[i][LaneIndex] = ptr[i];
    });
    return argon::to_array(out.val);
#else
    if constexpr (Stride == 2) {
      if constexpr (simd::is_quadword_v<VectorType>) {
        return argon::to_array(simd::load2_lane_quad<LaneIndex>(ptr, multi).val);
      } else {
        return argon::to_array(simd::load2_lane<LaneIndex>(ptr, multi).val);
      }
    } else if constexpr (Stride == 3) {
      if constexpr (simd::is_quadword_v<VectorType>) {
        return argon::to_array(simd::load3_lane_quad<LaneIndex>(ptr, multi).val);
      } else {
        return argon::to_array(simd::load3_lane<LaneIndex>(ptr, multi).val);
      }
    } else if constexpr (Stride == 4) {
      if constexpr (simd::is_quadword_v<VectorType>) {
        return argon::to_array(simd::load4_lane_quad<LaneIndex>(ptr, multi).val);
      } else {
        return argon::to_array(simd::load4_lane<LaneIndex>(ptr, multi).val);
      }
    }
#endif
  }

  /// @copydoc LoadToLaneInterleaved
  template <size_t lane, size_t stride>
  ace static std::array<argon_type, stride> LoadToLaneInterleaved(std::array<argon_type, stride> multi,
                                                                  const scalar_type* ptr) {
    using multivec_type = simd::MultiVector_t<VectorType, stride>;
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
  template <size_t stride>
  ace static std::array<argon_type, stride> LoadGatherOffsetIndexInterleaved(
      const scalar_type* base_ptr,
      helpers::ArgonFor_t<simd::make_unsigned_t<Bool_t<VectorType>>> offset_vector) {
    static_assert(stride > 1 && stride < 5, "De-interleaving Loads can only be performed with a stride of 2, 3, or 4");
    std::array<argon_type, stride> multi{};
    utility::constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      auto lane_val = simd::get_lane<i>(offset_vector);
      multi = LoadToLaneInterleaved<i, stride>(multi, base_ptr + (lane_val * stride));
    });
    return multi;
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
#ifdef ARGON_PLATFORM_MVE
    std::array<argon_type, n> multi{};
    utility::constexpr_for<0, n, 1>([&]<int i>() {  //<
      multi[i] = *ptr;
      ptr += lanes;
    });
    return multi;
#else
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
#endif
  }

  /// @brief Store the vector to a pointer
  /// @param ptr The pointer to store to
  ace void StoreTo(scalar_type* ptr) const { simd::store1(ptr, vec_); }

  /// @brief Store a lane of the vector to a pointer
  /// @param ptr The pointer to store to
  /// @tparam lane The lane to store
  template <int LaneIndex>
  ace void StoreLaneTo(scalar_type* ptr) {
#ifdef ARGON_PLATFORM_MVE
    *ptr = vec_[LaneIndex];
#else
    simd::store1_lane<LaneIndex>(ptr, vec_);
#endif
  }

#ifndef ARGON_PLATFORM_MVE
  /// Pairwise ops

  /// @brief Pairwise add two vectors, returning the sum of each pair of lanes.
  /// @details Given a pair of vector {a0, a1, a2, a3} and {b0, b1, b2, b3},
  /// the result is {a0 + a1, a1 + a2, b0 + b1, b1 + b2}
  ace argon_type PairwiseAdd(argon_type b) const { return simd::pairwise_add(vec_, b); }

  /// Select the maximum of each pair of lanes in the two vectors.
  /// @details Given a pair of vector {a0, a1, a2, a3} and {b0, b1, b2, b3},
  /// the result is {max(a0, a1), max(a2, b2), max(b0, b1), max(b2, b3)}
  ace argon_type PairwiseMax(argon_type b) const { return simd::pairwise_max(vec_, b); }

  /// Select the maximum of each pair of lanes in the two vectors.
  /// @details Given a pair of vector {a0, a1, a2, a3} and {b0, b1, b2, b3},
  /// the result is {max(a0, a1), max(a2, b2), max(b0, b1), max(b2, b3)}
  ace argon_type PairwiseMin(argon_type b) const { return simd::pairwise_min(vec_, b); }
#endif

  /// Bitwise ops

  /// Bitwise NOT of the vector
  ace argon_type BitwiseNot() const {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return ~vec_;
    } else {
      return simd::bitwise_not(vec_);
    }
  }

  /// Bitwise AND of the vector with another vector
  ace argon_type BitwiseAnd(argon_type b) const {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ & b.vec_;
    } else {
      return simd::bitwise_and(vec_, b);
    }
  }

  /// Bitwise OR of the vector with another vector
  ace argon_type BitwiseOr(argon_type b) const {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ | b.vec_;
    } else {
      return simd::bitwise_or(vec_, b);
    }
  }

  /// Bitwise XOR of the vector with another vector
  ace argon_type BitwiseXor(argon_type b) const {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ ^ b.vec_;
    } else {
      return simd::bitwise_xor(vec_, b);
    }
  }

  /// Bitwise OR of the vector with the NOT of another vector
  /// @details Equivalent to a | ~b.
  ace argon_type BitwiseOrNot(argon_type b) const {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ | ~b.vec_;
    } else {
      return simd::bitwise_or_not(vec_, b);
    }
  }

  /// Bitwise AND of the vector with the NOT of another vector
  /// @details Equivalent to a & ~b.
  ace argon_type BitwiseAndNot(argon_type b) const {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ & ~b.vec_;
    } else {
      return simd::bitwise_clear(vec_, b);
    }
  }

  /// @copydoc BitwiseAndNot
  ace argon_type BitwiseClear(argon_type b) const { BitwiseAndNot(b); }

#ifndef ARGON_PLATFORM_MVE
  /// Bitwise select between two vectors, using the current vector as a mask.
  /// @details Equivalent to (mask & b) | (~mask & c).
  template <typename ArgType>
    requires std::is_unsigned_v<scalar_type>
  ace argon_type BitwiseSelect(ArgType true_value, ArgType false_value) const {
    return simd::bitwise_select(vec_, true_value, false_value);
  }

  /// @copydoc BitwiseSelect
  template <typename ArgType>
    requires std::is_unsigned_v<scalar_type>
  ace argon_type Select(ArgType true_value, ArgType false_value) const {
    return simd::bitwise_select(true_value, false_value);
  }

  /// Ands the current vector with the given vector, then checks if nonzero. If so, fills the lane with all ones
  /// @details Equivalent to (a & b) != 0 ? 0xFFFFFFFF : 0x00000000
  ace predicate_type CompareTestNonzero(argon_type b) const { return simd::compare_test_nonzero(vec_, b); }

  /// @copydoc CompareTestNonzero
  ace predicate_type TestNonzero() const { return simd::compare_test_nonzero(vec_, argon_type{1}); }
#endif

  /// Count the number of consecutive bits following the sign bit that are set to the same value as the sign bit.
  /// @details Equivalent to std::countl_one(a).
  ace helpers::ArgonFor_t<simd::make_signed_t<VectorType>> CountLeadingSignBits() const
    requires(std::is_integral_v<scalar_type>)
  {
    return simd::count_leading_sign_bits(vec_);
  }

  /// Count the number of consecutive top bits that are set to zero.
  /// @details Equivalent to std::countl_zero(a)
  ace argon_type CountLeadingZeroBits() const { return simd::count_leading_zero_bits(vec_); }

  /// Count the number of bits that are set to one in the vector.
  /// @details Equivalent to std::popcount(a).
  ace argon_type CountActiveBits() const {
#ifdef ARGON_PLATFORM_MVE
    auto new_vec = vec_;
    utility::constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      new_vec[i] = std::popcount(vec_[i]);
    });
    return new_vec;
#else
    return neon::count_active_bits(vec_);
#endif
  }

  /// @copydoc CountActiveBits
  ace argon_type Popcount() const { return CountActiveBits(); }

  /// @brief Extract n elements from the lower end of the operand, and the remaining elements from the top end of this
  /// vector, combining them into the result vector.
  /// For example:  {a0, a1, a2, a3} and {b0, b1, b2, b3} with n = 1 will result in {b0, a1, a2, a3}
  template <int n>
  ace argon_type Extract(argon_type b) const {
#ifdef ARGON_PLATFORM_MVE
    auto new_vec = vec_;
    utility::constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      if (i < n) {
        new_vec[i] = b.vec_[i];
      }
    });
    return new_vec;
#else
    return simd::extract<n>(vec_, b);
#endif
  }

  ace argon_type Reverse64bit() const { return simd::reverse_64bit(vec_); }
  ace argon_type Reverse32bit() const { return simd::reverse_32bit(vec_); }
  ace argon_type Reverse16bit() const { return simd::reverse_16bit(vec_); }

  /// @brief Zip two vectors together, returning two vectors of pairs
  /// @details Given a pair of vector {a0, a1, a2, a3} and {b0, b1, b2, b3},
  /// the result is {{a0, b0, a1, b1}, {a2, b2, a3, b3}}
  ace std::array<argon_type, 2> ZipWith(argon_type b) const {
#ifdef ARGON_PLATFORM_MVE
    std::array<argon_type, 2> new_vec;
    utility::constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      if (i % 2 == 0) {
        new_vec[0][i] = vec_[i / 2];
        new_vec[1][i] = vec_[(i + lanes) / 2];
      } else {
        new_vec[0][i] = b.vec_[i / 2];
        new_vec[1][i] = b.vec_[(i + lanes) / 2];
      }
    });
    return new_vec;
#else
    return argon::to_array(neon::zip(vec_, b.vec()).val);
#endif
  }

  /// @brief Unzip two vectors, returning two vectors of pairs
  /// @details Given a pair of vector {a0, b0, a1, b1} and {a2, b2, a3, b3},
  /// the result is {{a0, a1, a2, a3}, {b0, b1, b2, b3}}
  std::array<argon_type, 2> UnzipWith(argon_type b) {
#ifdef ARGON_PLATFORM_MVE
    std::array<argon_type, 2> new_vec;
    utility::constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      if ((i * 2) < lanes) {
        new_vec[0][i] = vec_[i * 2];
        new_vec[1][i] = vec_[i * 2 + 1];
      } else {
        new_vec[0][i] = b.vec_[i * 2];
        new_vec[1][i] = b.vec_[i * 2 + 1];
      }
    });
    return new_vec;
#else
    return argon::to_array(neon::unzip(vec_, b.vec()).val);
#endif
  }

  /// @brief Perform a 2x2 matrix transpose on two vectors, returning two vectors of pairs
  /// @details Given a pair of vectors {{a0, a1, a2, a3},
  //                                    {b0, b1, b2, b3}}
  ///                    the result is {{a0, b0, a2, b2},
  //                                    {a1, b1, a3, b3}}
  std::array<argon_type, 2> TransposeWith(argon_type b) const {
#ifdef ARGON_PLATFORM_MVE
    std::array<argon_type, 2> new_vec;
    utility::constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      if (i % 2 == 1) {
        new_vec[0][i] = vec_[i];
        new_vec[1][i] = vec_[i + 1];
      } else {
        new_vec[0][i] = b.vec_[i + 1];
        new_vec[1][i] = b.vec_[i];
      }
    });
    return new_vec;
#else
    return argon::to_array(simd::transpose(vec_, b.vec()).val);
#endif
  }

  /// Get the number of elements
  ace static int size() { return lanes; }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<scalar_type(scalar_type)>>
  ace argon_type map(FuncType body) const {
    VectorType out;
    utility::constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      out[i] = body(vec_[i]);
    });
    return out;
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<scalar_type(scalar_type, int)>>
  ace argon_type map_with_index(FuncType body) const {
    VectorType out;
    utility::constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      out[i] = body(vec_[i], i);
    });
    return out;
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<scalar_type(scalar_type, scalar_type)>>
  ace argon_type map2(argon_type other, FuncType body) const {
    VectorType out;
    utility::constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      out[i] = body(vec_[i], other.vec_[i]);
    });
    return out;
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void(scalar_type&)>>
  ace argon_type each_lane(FuncType body) {
    VectorType out = vec_;
    utility::constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      body(out[i]);
    });
    return out;
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void(scalar_type&, int)>>
  ace argon_type each_lane_with_index(FuncType body) {
    VectorType out = vec_;
    utility::constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      body(out[i], i);
    });
    return out;
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void()>>
  ace void if_lane(FuncType true_branch) {
    utility::constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      if (vec_[i] != 0) {
        true_branch();
      }
    });
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void()>>
  ace void if_else_lane(FuncType true_branch, FuncType false_branch) {
    utility::constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      if (vec_[i] != 0) {
        true_branch();
      } else {
        false_branch();
      }
    });
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void(int)>>
  ace void if_lane_with_index(FuncType true_branch) {
    utility::constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      if (vec_[i] != 0) {
        true_branch(i);
      }
    });
  }

  template <typename FuncType1, typename FuncType2>
    requires std::convertible_to<FuncType1, std::function<void(int)>> &&
             std::convertible_to<FuncType2, std::function<void(int)>>
  ace void if_else_lane_with_index(FuncType1 true_branch, FuncType2 false_branch) {
    utility::constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      if (vec_[i] != 0) {
        true_branch(i);
      } else {
        false_branch(i);
      }
    });
  }

  ace bool any() {
    utility::constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      if (vec_[i]) {
        return true;
      }
    });
    return false;
  }

  ace bool all() {
#ifdef ARGON_PLATFORM_MVE
    return mve::max_reduce_max(vec_, vec_) != 0;
#else
    auto nonzero = TestNonzero();
    utility::constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      if (nonzero[i] == 0) {
        return false;
      }
    });
    return true;
#endif
  }

  template <std::size_t Index>
  std::tuple_element_t<Index, argon_type> get() {
#ifdef ARGON_PLATFORM_MVE
    return vec_[Index];
#else
    return GetLane<Index>();
#endif
  }

 protected:
  VectorType vec_;
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
  using type = argon::Vector<T>::const_lane_type;
};
}  // namespace std

#undef ace
#undef simd
