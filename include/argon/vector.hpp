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
#include "helpers/float_fixups.hpp"
#include "helpers/mve_compare.hpp"
#include "helpers/to_array.hpp"
#include "lane.hpp"
#include "predicate.hpp"

#ifdef __ARM_FEATURE_MVE
#define simd mve
#else
#define simd neon
#endif

#ifdef ARGON_PLATFORM_SIMDE
#define ace [[gnu::always_inline]] inline
#elifdef __clang__
#define ace [[gnu::always_inline]] constexpr
#else
#define ace [[gnu::always_inline]] inline
#endif

namespace argon {
template <typename T>
concept arithmetic = lane_scalar<T>;

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

  /// Whether arithmetic may use the compiler's generic vector extensions (see ARGON_GCC_AARCH32_FLOAT).
  static constexpr bool extension_arithmetic =
      ARGON_USE_COMPILER_EXTENSIONS && !(ARGON_GCC_AARCH32_FLOAT && std::is_floating_point_v<scalar_type>);
#ifdef ARGON_PLATFORM_MVE
  static constexpr bool mve_platform = true;  ///< Whether this is the MVE (Helium) platform.
#else
  static constexpr bool mve_platform = false;  ///< Whether this is the MVE (Helium) platform.
#endif
  /// Float lanes on Helium, which go through MVE intrinsics where GCC mishandles the vector extensions.
  static constexpr bool mve_float = mve_platform && lane_floating_point<scalar_type>;
  /// Whether MaxNumber/MinNumber are single instructions (vmaxnm/vminnm) for these lanes: every float lane on
  /// Helium and Armv8 NEON, half lanes on NEON only with FP16 vector arithmetic. False on Armv7 NEON and on x86
  /// (SIMDe), where they are emulated with compares and selects, and Max/Min are the cheap ones (x86's maxps is
  /// exactly Max). For inputs that are never NaN, pick with `if constexpr (native_maxnm)`; see MaxNumber.
  static constexpr bool native_maxnm = ARGON_HAS_MAXNM && lane_floating_point<scalar_type> &&
                                       (mve_platform || !is_half_float_v<scalar_type> || ARGON_NEON_FP16_VECTOR);
  /// Whether float comparisons need the inline vcgt/vcge (see ARGON_GCC_AARCH32_FLOAT).
  static constexpr bool fixup_float_compare = ARGON_GCC_AARCH32_FLOAT && std::is_same_v<scalar_type, float>;
  using vector_type = VectorType;                               ///< The SIMD vector type.
  using argon_type = helpers::ArgonFor_t<VectorType>;           ///< The Argon type for the SIMD vector.
  using mask_type = Bool_t<VectorType>;  ///< The mask vector type (all ones / all zeros per lane), see Predicate::ToMask.
  using predicate_type [[deprecated("predicate_type is the mask vector type; use mask_type, or argon_bool_type for "
                                    "the Predicate comparisons return")]] = mask_type;
  using argon_bool_type = Predicate<VectorType>;                ///< The type comparisons return.
  using offset_type = helpers::ArgonFor_t<simd::make_unsigned_t<Bool_t<VectorType>>>;  ///< Per-lane gather/scatter offsets.

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

  /// @brief Constructs a Vector from one value per lane.
  /// @details Arithmetic arguments are converted to the lane type, so `Argon<uint16_t>{1, 2, ...}` does not narrow
  /// (an error in braced initialisation under Clang).
  template <typename... ArgTypes>
    requires(sizeof...(ArgTypes) > 1)
  ace Vector(ArgTypes... args) : vec_{LaneValue(std::forward<ArgTypes>(args))...} {}

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
    return simd::duplicate_lane<vector_type>(lane.vec(), lane.lane());
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
#if __ARM_ARCH >= 8
      return simd::duplicate_lane_quad<LaneIndex>(lane.vec());
#else
      // On A32, vec() returns the 64-bit half-register (low or high).
      // The template arg must be the lane index within that half-vector.
      constexpr size_t local_lane = LaneIndex >= (lanes / 2) ? LaneIndex - (lanes / 2) : LaneIndex;
      return simd::duplicate_lane_quad<local_lane>(lane.vec());
#endif
    } else {
      return simd::duplicate_lane<LaneIndex>(lane.vec());
    }
#endif
  }

  /// @brief Constructs a Vector from an incrementing sequence.
  /// @param start The starting value of the sequence.
  /// @param step The step size of the sequence.
  /// @return The constructed SIMD vector.
  /// @details This constructor creates a SIMD vector with lanes containing values from start to start + (lanes - 1) *
  /// step.
  ace static argon_type Iota(scalar_type start) {
    // TODO: Remove this once MSVC 19.44 is released.
#if __cpp_if_consteval >= 202106L
    return IotaHelper(start, std::make_index_sequence<lanes>{});
#else
    return Argon{start}.Add(VectorType{0, 1, 2, 3});
#endif
  }

  /// @brief Constructs a Vector from a function that generates values.
  /// @param body The function that generates the values.
  /// @details This constructor creates a SIMD vector with lanes containing values generated by the function.
  /// @return The constructed SIMD vector.
  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<scalar_type()>>
  ace static argon_type Generate(FuncType body) {
    // Build via a scalar array + Load rather than subscripting the raw vector:
    // MSVC's SIMDe vector types are structs with no operator[].
    std::array<scalar_type, lanes> out;
    utility::constexpr_for<0, lanes, 1>([&]<size_t i>() {  //
      out[i] = body();
    });
    return Load(out.data());
  }

  /// @brief Constructs a Vector from a function that generates values with an index.
  /// @param body The function that generates the values.
  /// @details This constructor creates a SIMD vector with lanes containing values generated by the function using the
  /// index.
  /// @return The constructed SIMD vector.
  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<scalar_type(scalar_type)>>
  ace static argon_type GenerateWithIndex(FuncType body) {
    // Build via a scalar array + Load rather than subscripting the raw vector:
    // MSVC's SIMDe vector types are structs with no operator[].
    std::array<scalar_type, lanes> out;
    utility::constexpr_for<0, lanes, 1>([&]<size_t i>() {  //
      out[i] = body(i);
    });
    return Load(out.data());
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
  ace argon_type operator>>(const int i) const {
#if ARGON_USE_COMPILER_EXTENSIONS
    return vec_ >> i;
#else
    return ShiftRight(i);
#endif
  }

  /// Shift the elements of the vector to the left by a specified number of bits.
  ace argon_type operator<<(const int i) const {
#if ARGON_USE_COMPILER_EXTENSIONS
    return vec_ << i;
#else
    return ShiftLeft(i);
#endif
  }

  /// Get the underlying SIMD vector.
  [[gnu::always_inline]] constexpr VectorType vec() const { return vec_; }

  /// Convert the vector to the underlying SIMD vector type.
  [[gnu::always_inline]] constexpr operator VectorType() const { return vec_; }

  /// @brief Convert the vector to an array of scalar values.
  /// @return An array of scalar values representing the vector.
  ace std::array<scalar_type, lanes> to_array() const {
    std::array<scalar_type, lanes> out;
    simd::store1(out.data(), vec_);
    return out;
  }

  /// @brief Get a single lane of the vector by index.
  /// @param i The index of the lane to get.
  /// @return The value of the specified lane in the SIMD vector.
  /// @note If you know the index of the lane at compile time, you should use GetLane<LaneIndex>() instead.
  ace const lane_type GetLane(const size_t i) const {
    return {vec_, static_cast<int>(i)};
  }
  ace lane_type GetLane(const size_t i) {
    return {vec_, static_cast<int>(i)};
  }

  /// @brief Get a single lane of the vector by index.
  /// @param i The index of the lane to get.
  /// @return The value of the specified lane in the SIMD vector.
  ace const lane_type GetLane(const int i) const {
    return {vec_, i};
  }

  ace lane_type GetLane(const int i) {
    return {vec_, i};
  }

  /// @brief Get a single lane of the vector by index.
  /// @tparam LaneIndex The index of the lane to get.
  /// @return The value of the specified lane in the SIMD vector.
  template <size_t LaneIndex>
  ace const const_lane_type<LaneIndex> GetLane() const {
    return vec_;
  }

  template <size_t LaneIndex>
  ace const_lane_type<LaneIndex> GetLane() {
    return vec_;
  }

  /// Get the last lane of the vector.
  ace const_lane_type<lanes - 1> LastLane() { return vec_; }

  /// Shift the elements of the vector to the right by a specified number of bits.
  /// @details Arithmetic for signed lanes, logical for unsigned ones, as a >> i. Without the compiler's vector
  /// extensions (MSVC) it is vshl by -i: NEON's shift-by-immediate needs a constant.
  ace argon_type ShiftRight(const int i) const {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ >> i;
    } else {
      return ShiftByVector(-i);
    }
  }

  /// Shift the elements of the vector to the left by a specified number of bits.
  ace argon_type ShiftLeft(const int i) const {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ << i;
    } else {
      return ShiftByVector(i);
    }
  }

  /// Bitwise negate the vector and return the result.
  ace argon_type Negate() const {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return -vec_;
    } else if constexpr (std::is_unsigned_v<scalar_type>) {
      return argon_type{scalar_type{0}}.Subtract(argon_type{vec_});  // NEON has no unsigned vneg: 0 - a wraps
    } else {
      return simd::negate(vec_);
    }
  }

  /// Add two vectors
  ace argon_type Add(argon_type b) const {
    if constexpr (extension_arithmetic) {
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
    if constexpr (extension_arithmetic) {
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
    if constexpr (extension_arithmetic) {
      return vec_ * b.vec_;
    } else if constexpr (std::is_integral_v<scalar_type> && sizeof(scalar_type) == 8) {
      // NEON has no 64-bit lane multiply: lane by lane.
      auto x = argon_type{vec_}.to_array();
      const auto y = b.to_array();
      for (size_t i = 0; i < x.size(); ++i) x[i] *= y[i];
      return argon_type::Load(x.data());
    } else {
      return simd::multiply(vec_, b);
    }
  }

  /// Multiply a vector by a scalar value
  ace argon_type Multiply(scalar_type b) const {
    if constexpr (extension_arithmetic) {
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
  /// @details Equivalent to a + (b * c). Fused (one rounding) for floats on Helium, whose only float
  /// multiply-accumulate is vfma; GCC never contracts the vector-extension form into it.
  ace argon_type MultiplyAdd(argon_type b, argon_type c) const {
#ifdef ARGON_PLATFORM_MVE
    if constexpr (mve_float) {
      return simd::multiply_add_fused(vec_, b.vec_, c.vec_);
    } else
#endif
    if constexpr (extension_arithmetic) {
      return vec_ + b.vec_ * c.vec_;
    } else {
      return simd::multiply_add(vec_, b, c);
    }
  }

  /// Multiply a vector by a scalar value and add a third vector
  /// @details Equivalent to a + (b * c). Fused for floats on Helium (vfma).
  ace argon_type MultiplyAdd(argon_type b, scalar_type c) const {
#ifdef ARGON_PLATFORM_MVE
    if constexpr (mve_float) {
      return simd::multiply_add_fused(vec_, b.vec_, c);
    } else
#endif
    if constexpr (extension_arithmetic) {
      if constexpr (is_half_float_v<scalar_type>) {
        return vec_ + b.vec_ * argon_type{c}.vec_;  // a half scalar promotes to float against the vector
      } else {
        return vec_ + b.vec_ * c;
      }
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
  /// @details Equivalent to a - (b * c). Fused for floats on Helium (vfms).
  ace argon_type MultiplySubtract(argon_type b, argon_type c) const {
#ifdef ARGON_PLATFORM_MVE
    if constexpr (mve_float) {
      return simd::multiply_subtract_fused(vec_, b.vec_, c.vec_);
    } else {
      return vec_ - b.vec_ * c.vec_;  // MVE has no integer vector multiply-subtract
    }
#else
    if constexpr (extension_arithmetic) {
      return vec_ - b.vec_ * c.vec_;
    } else {
      return simd::multiply_subtract(vec_, b, c);
    }
#endif
  }

  /// Multiply a vector by a scalar value and subtract from a third vector
  /// @details Equivalent to a - (b * c). Fused for floats on Helium (vfms).
  ace argon_type MultiplySubtract(argon_type b, scalar_type c) const {
#ifdef ARGON_PLATFORM_MVE
    if constexpr (mve_float) {
      return simd::multiply_subtract_fused(vec_, b.vec_, simd::duplicate(c));  // MVE has no vfms by a scalar
    } else {
      return vec_ - b.vec_ * c;  // MVE has no integer vector multiply-subtract
    }
#else
    if constexpr (extension_arithmetic) {
      if constexpr (is_half_float_v<scalar_type>) {
        return vec_ - b.vec_ * argon_type{c}.vec_;  // a half scalar promotes to float against the vector
      } else {
        return vec_ - b.vec_ * c;
      }
    } else {
      return simd::multiply_subtract(vec_, b, c);
    }
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

  /// Multiply two QMax fixed-point vectors, returning a fixed-point product
  /// @details This is equivalent to ((uint64_t)a * b) >> 31
  ace argon_type MultiplyFixedQMax(argon_type v) const { return simd::multiply_double_saturate_high(vec_, v); }

  /// Multiply a QMax fixed-point vector by a scalar value, returning a fixed-point product
  /// @details This is equivalent to ((uint64_t)a * b) >> 31
  ace argon_type MultiplyFixedQMax(scalar_type s) const { return simd::multiply_double_saturate_high(vec_, s); }

#ifndef ARGON_PLATFORM_MVE
  /// Multiply a QMax fixed-point vector by a lane value, returning a fixed-point product
  /// @details This is equivalent to ((uint64_t)a * b) >> 31
  ace argon_type MultiplyFixedQMax(lane_type l) const {
    return simd::multiply_double_saturate_high_lane(vec_, l.vec(), l.lane());
  }
#endif

  /// Multiply two fixed-point vectors, returning a fixed-point product
  /// @details This is equivalent to round(a * b) >> 31
  ace argon_type MultiplyRoundFixedQMax(argon_type v) const {
    return simd::multiply_double_round_saturate_high(vec_, v);
  }

  /// Multiply a fixed-point vector by a scalar value, returning a fixed-point product
  /// @details This is equivalent to round(a * b) >> 31
  ace argon_type MultiplyRoundFixedQMax(scalar_type s) const {
    return simd::multiply_double_round_saturate_high(vec_, s);
  }

#ifndef ARGON_PLATFORM_MVE
  /// Multiply a fixed-point vector by a lane value, returning a fixed-point product
  /// @details This is equivalent to round(a * b) >> 31
  ace argon_type MultiplyRoundFixedQMax(lane_type l) const {
    return simd::multiply_double_round_saturate_high_lane(vec_, l.vec(), l.lane());
  }
#endif

  /// Get the absolute value of the vector.
  ace argon_type Absolute() const { return simd::abs(vec_); }

  /// @brief 1 / value, using an estimate for speed
  /// @note This is not a precise reciprocal, but it is fast and useful for many applications
  /// @note The unsigned fixed-point form is NEON-only.
  ace argon_type ReciprocalEstimate() const
    requires lane_floating_point<scalar_type> || (std::is_same_v<scalar_type, uint32_t> && !mve_platform)
  {
#ifdef ARGON_PLATFORM_MVE
    return 1.f / vec_;
#else
    return simd::reciprocal_estimate(vec_);
#endif
  }

  /// @brief 1 / sqrt(value), using an estimate for speed
  /// @note For greater precision, follow with ReciprocalSqrtStep iterations (Newton-Raphson).
  /// @note The unsigned fixed-point form is NEON-only.
  ace argon_type ReciprocalSqrtEstimate() const
    requires lane_floating_point<scalar_type> || (std::is_same_v<scalar_type, uint32_t> && !mve_platform)
  {
#ifdef ARGON_PLATFORM_MVE
    // MVE has no vrsqrte: take the bit-level initial guess, then one Newton-Raphson step, which lands within NEON's
    // estimate precision (~1/256).
    const auto bits = std::bit_cast<Bool_t<VectorType>>(vec_);
    const VectorType guess = std::bit_cast<VectorType>(0x5f3759dfu - (bits >> 1));
    return guess * (1.5f - 0.5f * vec_ * guess * guess);
#else
    return simd::reciprocal_sqrt_estimate(vec_);
#endif
  }

  /// @brief Newton-Raphson step for reciprocal refinement: (2 - a * b) / 2
  /// @details Feeds into the standard NR iteration: est = est * ReciprocalStep(value * est)
  /// @note Only defined for floating-point types.
  ace argon_type ReciprocalStep(argon_type b) const
    requires lane_floating_point<scalar_type>
  {
#ifdef ARGON_PLATFORM_MVE
    return 2.f - vec_ * b.vec_;
#else
    return simd::reciprocal_step(vec_, b.vec_);
#endif
  }

  /// @brief Newton-Raphson step for reciprocal-sqrt refinement: (3 - a * b) / 2
  /// @details Use after ReciprocalSqrtEstimate to increase precision.
  /// @note Only defined for floating-point types.
  ace argon_type ReciprocalSqrtStep(argon_type b) const
    requires lane_floating_point<scalar_type>
  {
#ifdef ARGON_PLATFORM_MVE
    return (3.f - vec_ * b.vec_) * 0.5f;
#else
    return simd::reciprocal_sqrt_step(vec_, b.vec_);
#endif
  }

  /// @brief Compute a refined reciprocal estimate using Newton-Raphson iterations.
  /// @param n_iters Number of refinement iterations (1 gives ~23-bit precision for float32).
  /// @details Each iteration approximately doubles the number of correct mantissa bits.
  ace argon_type ReciprocalEstimateRefine(int n_iters = 1) const
    requires lane_floating_point<scalar_type>
  {
    argon_type est = ReciprocalEstimate();
    for (int i = 0; i < n_iters; ++i) {
      est = est * ReciprocalStep(est);
    }
    return est;
  }

  /// @brief Compute a refined reciprocal-sqrt estimate using Newton-Raphson iterations.
  /// @param n_iters Number of refinement iterations (1 gives ~23-bit precision for float32).
  /// @details Each iteration approximately doubles the number of correct mantissa bits.
  ace argon_type ReciprocalSqrtEstimateRefine(int n_iters = 1) const
    requires lane_floating_point<scalar_type>
  {
    argon_type est = ReciprocalSqrtEstimate();
    for (int i = 0; i < n_iters; ++i) {
      est = est * (*this * est).ReciprocalSqrtStep(est);
    }
    return est;
  }

  /// Multiply-add three fixed-point vectors, returning a fixed-point sum
  /// @details This is equivalent to a + ((b * c) >> 31)
  template <typename arg_type>
    requires(is_one_of<arg_type, argon_type, scalar_type, lane_type> || std::is_convertible_v<arg_type, argon_type> ||
             std::is_convertible_v<arg_type, scalar_type>)
  ace argon_type MultiplyAddFixedQMax(argon_type b, arg_type c) const {
    return Add(b.MultiplyFixedQMax(c));
  }

  /// Multiply-round-add three fixed-point vectors, returning a fixed-point sum
  /// @details This is equivalent to a + (rnd(b * c) >> 31)
  template <typename arg_type>
    requires(is_one_of<arg_type, argon_type, scalar_type, lane_type> || std::is_convertible_v<arg_type, argon_type> ||
             std::is_convertible_v<arg_type, scalar_type>)
  ace argon_type MultiplyRoundAddFixedQMax(argon_type b, arg_type c) const {
    return Add(b.MultiplyRoundFixedQMax(c));
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
    } else if constexpr (lane_floating_point<scalar_type>) {
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
  /// @details Equivalent to a > b ? a : b: a NaN in either lane gives b. One instruction on NEON and x86 (maxps);
  /// on Helium a compare and a select. For floats that are never NaN, MaxNumber gives the same results and is one
  /// instruction (vmaxnm) where `native_maxnm` is true, so a clamp can pick the cheaper per platform:
  /// @code
  /// if constexpr (Argon<float>::native_maxnm) x = x.MaxNumber(lo).MinNumber(hi);
  /// else x = x.Max(lo).Min(hi);
  /// @endcode
  ace argon_type Max(argon_type b) const {
#ifdef ARGON_PLATFORM_MVE
    if constexpr (mve_float) {
      // GCC scalarises vector-extension float ?: on MVE; vcmp + vpsel keeps a > b ? a : b (vmaxnm would not).
      return simd::predicate_select(vec_, b.vec_,
                                    helpers::mve_compare<helpers::MveComparison::GreaterThan>(vec_, b.vec_));
    } else
#endif
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ > b.vec_ ? vec_ : b.vec_;
    } else if constexpr (lane_floating_point<scalar_type>) {
      // vmax/vmin return NaN for a NaN in either lane; keep a > b ? a : b.
      return (argon_type{vec_} > b).Select(argon_type{vec_}, b);
    } else {
      return simd::max(vec_, b);
    }
  }
  /// Compare the lanes of two vectors, copying the smaller of each lane to the result
  /// @details Equivalent to a < b ? a : b: a NaN in either lane gives b. One instruction on NEON and x86 (minps);
  /// on Helium a compare and a select. For floats that are never NaN, MinNumber gives the same results and is one
  /// instruction (vminnm) where `native_maxnm` is true; see Max for the clamp idiom.
  ace argon_type Min(argon_type b) const {
#ifdef ARGON_PLATFORM_MVE
    if constexpr (mve_float) {
      return simd::predicate_select(vec_, b.vec_,
                                    helpers::mve_compare<helpers::MveComparison::GreaterThan>(b.vec_, vec_));
    } else
#endif
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ < b.vec_ ? vec_ : b.vec_;
    } else if constexpr (lane_floating_point<scalar_type>) {
      // vmax/vmin return NaN for a NaN in either lane; keep a < b ? a : b.
      return (argon_type{vec_} < b).Select(argon_type{vec_}, b);
    } else {
      return simd::min(vec_, b);
    }
  }

  /// The larger of each lane by IEEE 754 maxNum, as Arm's vmaxnm: a quiet NaN in one operand gives the other
  /// (NaN only where both are), and +0 is larger than -0. Max is a > b ? a : b, which passes a NaN in b through.
  /// @details One instruction (vmaxnm) where `native_maxnm` is true: Helium and Armv8 NEON. Elsewhere (Armv7
  /// NEON, x86 via SIMDe) it is emulated with several compares and selects, so use it there only when NaNs must
  /// be ignored. For floats that are never NaN, Max and MaxNumber agree; choose the cheaper per platform:
  /// @code
  /// if constexpr (Argon<float>::native_maxnm) x = x.MaxNumber(lo).MinNumber(hi);
  /// else x = x.Max(lo).Min(hi);
  /// @endcode
  ace argon_type MaxNumber(argon_type b) const
    requires lane_floating_point<scalar_type>
  {
#if ARGON_HAS_MAXNM
    if constexpr (native_maxnm) {
      return simd::max_strict(vec_, b.vec_);
    } else
#endif
    {
      return NumberMinMax<true>(b);
    }
  }

  /// The smaller of each lane by IEEE 754 minNum, as Arm's vminnm: a quiet NaN in one operand gives the other
  /// (NaN only where both are), and -0 is smaller than +0. Min is a < b ? a : b, which passes a NaN in b through.
  /// @details One instruction (vminnm) where `native_maxnm` is true, emulated elsewhere; see MaxNumber for when
  /// to use it and the clamp idiom.
  ace argon_type MinNumber(argon_type b) const
    requires lane_floating_point<scalar_type>
  {
#if ARGON_HAS_MAXNM
    if constexpr (native_maxnm) {
      return simd::min_strict(vec_, b.vec_);
    } else
#endif
    {
      return NumberMinMax<false>(b);
    }
  }

  /// MaxNumber/MinNumber from compares and selects, where there is no vmaxnm/vminnm.
  template <bool max>
  ace argon_type NumberMinMax(argon_type b) const {
    using bits_type = std::conditional_t<sizeof(scalar_type) == 2, uint16_t,
                                         std::conditional_t<sizeof(scalar_type) == 4, uint32_t, uint64_t>>;
    const argon_type a{vec_};
    argon_type r = max ? (a > b).Select(a, b) : (a < b).Select(a, b);  // NaN in a: b
    const auto a_bits = a.template As<bits_type>(), b_bits = b.template As<bits_type>();
    const argon_type zeros = (max ? (a_bits & b_bits) : (a_bits | b_bits)).template As<scalar_type>();
    r = (a == b).Select(zeros, r);  // equal lanes: the same value, or zeros of either sign (+0 & -0 is +0)
    return (b == b).Select(r, a);   // NaN in b: a (NaN only if a is too)
  }

  /// Compare the lanes of two vectors, returning a predicate active where a == b.
  ace argon_bool_type Equal(argon_type b) const {
#ifdef ARGON_PLATFORM_MVE
    return argon_bool_type{helpers::mve_compare<helpers::MveComparison::Equal>(vec_, b.vec_)};
#else
    return argon_bool_type{simd::equal(vec_, b.vec_)};
#endif
  }

  /// Compare the lanes of two vectors, returning a predicate active where a is greater than or equal to b.
  ace argon_bool_type GreaterThanOrEqual(argon_type b) const {
#ifdef ARGON_PLATFORM_MVE
    return argon_bool_type{helpers::mve_compare<helpers::MveComparison::GreaterThanOrEqual>(vec_, b.vec_)};
#else
#if ARGON_GCC_AARCH32_FLOAT
    if constexpr (fixup_float_compare) return argon_bool_type{helpers::greater_than_or_equal(vec_, b.vec_)};
#endif
    return argon_bool_type{simd::greater_than_or_equal(vec_, b.vec_)};
#endif
  }

  /// Compare the lanes of two vectors, returning a predicate active where a is less than or equal to b.
  ace argon_bool_type LessThanOrEqual(argon_type b) const {
#ifdef ARGON_PLATFORM_MVE
    return argon_bool_type{helpers::mve_compare<helpers::MveComparison::GreaterThanOrEqual>(b.vec_, vec_)};
#else
#if ARGON_GCC_AARCH32_FLOAT
    if constexpr (fixup_float_compare) return argon_bool_type{helpers::greater_than_or_equal(b.vec_, vec_)};
#endif
    return argon_bool_type{simd::less_than_or_equal(vec_, b.vec_)};
#endif
  }

  /// Compare the lanes of two vectors, returning a predicate active where a is greater than b.
  ace argon_bool_type GreaterThan(argon_type b) const {
#ifdef ARGON_PLATFORM_MVE
    return argon_bool_type{helpers::mve_compare<helpers::MveComparison::GreaterThan>(vec_, b.vec_)};
#else
#if ARGON_GCC_AARCH32_FLOAT
    if constexpr (fixup_float_compare) return argon_bool_type{helpers::greater_than(vec_, b.vec_)};
#endif
    return argon_bool_type{simd::greater_than(vec_, b.vec_)};
#endif
  }

  /// Compare the lanes of two vectors, returning a predicate active where a is less than b.
  ace argon_bool_type LessThan(argon_type b) const {
#ifdef ARGON_PLATFORM_MVE
    return argon_bool_type{helpers::mve_compare<helpers::MveComparison::GreaterThan>(b.vec_, vec_)};
#else
#if ARGON_GCC_AARCH32_FLOAT
    if constexpr (fixup_float_compare) return argon_bool_type{helpers::greater_than(b.vec_, vec_)};
#endif
    return argon_bool_type{simd::less_than(vec_, b.vec_)};
#endif
  }

  /// Shift the elemnets of the vector to the left by a specified number of bits.
  /// @details Equivalent to a << b.
  ace argon_type ShiftLeft(helpers::ArgonFor_t<simd::make_signed_t<Bool_t<VectorType>>> b) const
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
  ace argon_type ShiftLeft(std::make_signed_t<simd::Scalar_t<Bool_t<VectorType>>> n) const
    requires std::is_integral_v<scalar_type>
  {
    if constexpr (ARGON_USE_COMPILER_EXTENSIONS) {
      return vec_ << n;
    } else {
      helpers::ArgonFor_t<simd::make_signed_t<VectorType>> b{n};
      return simd::shift_left(vec_, b.vec_);
    }
  }

  /// vshl by `count` in every lane: left for positive counts, right (arithmetic or logical) for negative ones.
  ace argon_type ShiftByVector(int count) const
    requires std::is_integral_v<scalar_type>
  {
    using signed_scalar = std::make_signed_t<scalar_type>;
    const helpers::ArgonFor_t<simd::make_signed_t<VectorType>> b{static_cast<signed_scalar>(count)};
    return simd::shift_left(vec_, b.vec());
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
  ace argon_type ShiftLeftSaturate(helpers::ArgonFor_t<simd::make_signed_t<Bool_t<VectorType>>> b) const
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
    return vec_ + (b >> n).vec();
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
    return vec_ + mve::shift_right_round<n>(b.vec());
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
    return simd::duplicate(*ptr);
#else
    return simd::load1_duplicate<VectorType>(ptr);
#endif
  }

  /// @brief Load the active lanes of a vector from a pointer; inactive lanes are zero and their memory is not read.
  /// @details MVE: vld1q_z, so a tail past the end of a buffer cannot fault. NEON: loads the active lanes one by one.
  /// @param ptr The address of lane 0.
  /// @param active The lanes to load.
  ace static argon_type Load(const scalar_type* ptr, argon_bool_type active) {
#ifdef ARGON_PLATFORM_MVE
    return mve::load1(ptr, active.native());
#else
    argon_type destination{scalar_type{0}};
    utility::constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      if (active.Active(i)) {
        destination = destination.template LoadToLane<i>(ptr + i);
      }
    });
    return destination;
#endif
  }

  /// @brief Gather a vector from `base` plus a byte offset per lane.
  /// @note On NEON this loads lane by lane.
  /// @param base The address the offsets are relative to.
  /// @param offsets The byte offset of each lane.
  /// @return A new vector constructed from the addressed elements.
  ace static argon_type LoadGatherOffsetBytes(const scalar_type* base, offset_type offsets) {
    return Gather<true>(base, offsets);
  }

  /// @brief Gather the active lanes from `base` plus a byte offset per lane; inactive lanes are zero and not read.
  /// @param base The address the offsets are relative to.
  /// @param offsets The byte offset of each lane.
  /// @param active The lanes to load.
  ace static argon_type LoadGatherOffsetBytes(const scalar_type* base, offset_type offsets, argon_bool_type active) {
    return Gather<true>(base, offsets, active);
  }

  /// @brief Gather a vector from `base[offsets[i]]`.
  /// @note On NEON this loads lane by lane. On MVE the index is scaled by the lane size in hardware.
  /// @param base The array to index.
  /// @param offsets The element index of each lane.
  /// @return A new vector constructed from the indexed elements.
  ace static argon_type LoadGatherOffsetIndex(const scalar_type* base, offset_type offsets) {
    return Gather<false>(base, offsets);
  }

  /// @brief Gather the active lanes from `base[offsets[i]]`; inactive lanes are zero and not read.
  /// @param base The array to index.
  /// @param offsets The element index of each lane.
  /// @param active The lanes to load.
  ace static argon_type LoadGatherOffsetIndex(const scalar_type* base, offset_type offsets, argon_bool_type active) {
    return Gather<false>(base, offsets, active);
  }

  /// @brief Load a lane from a pointer
  /// @param ptr The pointer to load from
  /// @return The new vector
  template <size_t lane>
  ace argon_type LoadToLane(const scalar_type* ptr) {
    return ConstLane<lane, VectorType>{vec_}.Load(ptr);
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
    static_assert(stride > 1 && stride < 5, "De-interleaving Loads can only be performed with a stride of 2, 3, or 4");
    if constexpr (stride == 2) {
      return argon::to_array(mve::load2(ptr).val);
    } else if constexpr (stride == 3) {
      // MVE has no vld3; gather each channel at indices {0, 3, 6, ...} instead.
      const offset_type offsets = offset_type::Iota(0) * 3;
      return {LoadGatherOffsetIndex(ptr, offsets), LoadGatherOffsetIndex(ptr + 1, offsets),
              LoadGatherOffsetIndex(ptr + 2, offsets)};
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
      multi[i] = Load(ptr);
      ptr += lanes;
    });
    return multi;
#else
#if defined(__clang__) || (__GNUC__ > 13)
    using multi_type = simd::MultiVector_t<VectorType, n>;
    if constexpr (n == 2) {
      return argon::to_array(simd::load1_x2<multi_type>(ptr).val);
    } else if constexpr (n == 3) {
      return argon::to_array(simd::load1_x3<multi_type>(ptr).val);
    } else if constexpr (n == 4) {
      return argon::to_array(simd::load1_x4<multi_type>(ptr).val);
    }
#else
    // load1 is a return-type-only template, so the element type must be named
    // explicitly — `simd::load1(ptr)` cannot deduce it (fails to compile on MSVC).
    if constexpr (n == 2) {
      auto a = simd::load1<VectorType>(ptr);
      auto b = simd::load1<VectorType>(ptr + lanes);
      return {a, b};
    } else if constexpr (n == 3) {
      auto a = simd::load1<VectorType>(ptr);
      auto b = simd::load1<VectorType>(ptr + lanes);
      auto c = simd::load1<VectorType>(ptr + 2 * lanes);
      return {a, b, c};
    } else if constexpr (n == 4) {
      auto a = simd::load1<VectorType>(ptr);
      auto b = simd::load1<VectorType>(ptr + lanes);
      auto c = simd::load1<VectorType>(ptr + 2 * lanes);
      auto d = simd::load1<VectorType>(ptr + 3 * lanes);
      return {a, b, c, d};
    }
#endif
#endif
  }

  /// @brief Store the vector to a pointer
  /// @param ptr The pointer to store to
  ace void StoreTo(scalar_type* ptr) const { simd::store1(ptr, vec_); }

  /// @brief Store the active lanes of the vector to a pointer; memory for inactive lanes is not written.
  /// @details MVE: vst1q_p. NEON: stores the active lanes one by one.
  /// @param ptr The address of lane 0.
  /// @param active The lanes to store.
  ace void StoreTo(scalar_type* ptr, argon_bool_type active) const {
#ifdef ARGON_PLATFORM_MVE
    mve::store1(ptr, vec_, active.native());
#else
    utility::constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      if (active.Active(i)) {
        ptr[i] = simd::get_lane<i>(vec_);
      }
    });
#endif
  }

  /// @brief Scatter the lanes to `base` plus a byte offset per lane.
  /// @note On NEON this stores lane by lane. Lanes addressing the same element are stored in lane order.
  /// @param base The address the offsets are relative to.
  /// @param offsets The byte offset of each lane.
  ace void StoreScatterOffsetBytes(scalar_type* base, offset_type offsets) const { Scatter<true>(base, offsets); }

  /// @brief Scatter the active lanes to `base` plus a byte offset per lane; inactive lanes are not written.
  /// @param base The address the offsets are relative to.
  /// @param offsets The byte offset of each lane.
  /// @param active The lanes to store.
  ace void StoreScatterOffsetBytes(scalar_type* base, offset_type offsets, argon_bool_type active) const {
    Scatter<true>(base, offsets, active);
  }

  /// @brief Scatter the lanes to `base[offsets[i]]`.
  /// @note On NEON this stores lane by lane. On MVE the index is scaled by the lane size in hardware.
  /// @param base The array to index.
  /// @param offsets The element index of each lane.
  ace void StoreScatterOffsetIndex(scalar_type* base, offset_type offsets) const { Scatter<false>(base, offsets); }

  /// @brief Scatter the active lanes to `base[offsets[i]]`; inactive lanes are not written.
  /// @param base The array to index.
  /// @param offsets The element index of each lane.
  /// @param active The lanes to store.
  ace void StoreScatterOffsetIndex(scalar_type* base, offset_type offsets, argon_bool_type active) const {
    Scatter<false>(base, offsets, active);
  }

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
  ace argon_type BitwiseClear(argon_type b) const { return BitwiseAndNot(b); }

  /// Bitwise select between two vectors, using the current vector as a mask.
  /// @details Equivalent to (mask & b) | (~mask & c).
  /// @return A vector of the operands' type (not the mask's).
  template <typename ArgType>
    requires std::is_unsigned_v<scalar_type>
  ace ArgType BitwiseSelect(ArgType true_value, ArgType false_value) const {
#ifdef ARGON_PLATFORM_MVE
    // MVE has no vbsl; blend the bits of the operands through the mask's type.
    const auto t = std::bit_cast<VectorType>(true_value.vec());
    const auto f = std::bit_cast<VectorType>(false_value.vec());
    return ArgType{std::bit_cast<typename ArgType::vector_type>((vec_ & t) | (f & ~vec_))};
#else
    return ArgType{simd::bitwise_select(vec_, true_value, false_value)};
#endif
  }

  /// @copydoc BitwiseSelect
  template <typename ArgType>
    requires std::is_unsigned_v<scalar_type>
  ace ArgType Select(ArgType true_value, ArgType false_value) const {
    return BitwiseSelect(true_value, false_value);
  }

  /// Compare the lanes of `(a & b)` with zero, returning a predicate active where they share a set bit.
  /// @details NEON: vtst.
  ace argon_bool_type CompareTestNonzero(argon_type b) const
    requires std::is_integral_v<scalar_type>
  {
#ifdef ARGON_PLATFORM_MVE
    return ~(argon_type{vec_ & b.vec_} == argon_type{scalar_type{0}});
#else
    return argon_bool_type{simd::compare_test_nonzero(vec_, b.vec_)};
#endif
  }

  /// Return a predicate active where the lane is nonzero.
  ace argon_bool_type TestNonzero() const
    requires std::is_integral_v<scalar_type>
  {
    return CompareTestNonzero(*this);
  }

  // ── Predicated operations ──────────────────────────────────────────────────────────────────────────────────
  // Each operation has two predicated forms, after ACLE's:
  //   Op(b, active)            "_x": lanes outside `active` are unspecified (on NEON, simply Op(b)).
  //   Op(b, active, inactive)  "_m": lanes outside `active` are taken from `inactive` (pass zero for "_z").
  // On MVE these are the VPT-predicated instructions; on NEON, the operation followed by vbsl. They are worth using
  // on MVE with GCC, which doesn't fold Select(op, ...) into a predicated instruction the way clang does.

#ifdef ARGON_PLATFORM_MVE
#define ARGON_PREDICATED_BINARY(Name, mve_name, mve_has_it)                                                  \
  ace argon_type Name(argon_type b, argon_bool_type active) const {                                      \
    if constexpr (mve_has_it) {                                                                               \
      return mve::mve_name(vec_, b.vec_, active.native());                                                \
    } else {                                                                                              \
      return Name(b);                                                                                     \
    }                                                                                                     \
  }                                                                                                       \
  ace argon_type Name(argon_type b, argon_bool_type active, argon_type inactive) const {                 \
    if constexpr (mve_has_it) {                                                                               \
      return mve::mve_name(inactive.vec_, vec_, b.vec_, active.native());                                 \
    } else {                                                                                              \
      return active.Select(Name(b), inactive);                                                            \
    }                                                                                                     \
  }
#define ARGON_PREDICATED_UNARY(Name, mve_name, mve_has_it)                                                   \
  ace argon_type Name(argon_bool_type active) const {                                                    \
    if constexpr (mve_has_it) {                                                                               \
      return mve::mve_name(vec_, active.native());                                                        \
    } else {                                                                                              \
      return Name();                                                                                      \
    }                                                                                                     \
  }                                                                                                       \
  ace argon_type Name(argon_bool_type active, argon_type inactive) const {                               \
    if constexpr (mve_has_it) {                                                                               \
      return mve::mve_name(inactive.vec_, vec_, active.native());                                         \
    } else {                                                                                              \
      return active.Select(Name(), inactive);                                                             \
    }                                                                                                     \
  }
#else
#define ARGON_PREDICATED_BINARY(Name, mve_name, mve_has_it)                                                  \
  ace argon_type Name(argon_type b, argon_bool_type /*active*/) const { return Name(b); }                 \
  ace argon_type Name(argon_type b, argon_bool_type active, argon_type inactive) const {                 \
    return active.Select(Name(b), inactive);                                                              \
  }
#define ARGON_PREDICATED_UNARY(Name, mve_name, mve_has_it)                                                   \
  ace argon_type Name(argon_bool_type /*active*/) const { return Name(); }                               \
  ace argon_type Name(argon_bool_type active, argon_type inactive) const { return active.Select(Name(), inactive); }
#endif

  ARGON_PREDICATED_BINARY(Add, add, true)
  ARGON_PREDICATED_BINARY(Subtract, subtract, true)
  ARGON_PREDICATED_BINARY(Multiply, multiply, true)
  // Float Max/Min would be vmaxnm/vminnm, whose NaN handling differs from the unpredicated a > b ? a : b.
  ARGON_PREDICATED_BINARY(Max, max, std::is_integral_v<scalar_type>)
  ARGON_PREDICATED_BINARY(Min, min, std::is_integral_v<scalar_type>)
  ARGON_PREDICATED_BINARY(SubtractAbs, subtract_absolute, true)
  ARGON_PREDICATED_BINARY(BitwiseAnd, bitwise_and, true)
  ARGON_PREDICATED_BINARY(BitwiseOr, bitwise_or, true)
  ARGON_PREDICATED_BINARY(BitwiseXor, bitwise_xor, true)
  ARGON_PREDICATED_BINARY(BitwiseAndNot, bitwise_clear, true)
  // MVE has no unsigned vneg/vabs.
  ARGON_PREDICATED_UNARY(Negate, negate, !std::is_unsigned_v<scalar_type>)
  ARGON_PREDICATED_UNARY(Absolute, abs, !std::is_unsigned_v<scalar_type>)

#undef ARGON_PREDICATED_BINARY
#undef ARGON_PREDICATED_UNARY

  /// MultiplyAdd under a predicate: lanes outside `active` keep this vector's value, the accumulator (as ACLE's
  /// vfmaq_m). On MVE, floats are one predicated vfma, which lets GCC tail-predicate a vectorize::for_each
  /// accumulation; elsewhere it is MultiplyAdd and a Select.
  ace argon_type MultiplyAdd(argon_type b, argon_type c, argon_bool_type active) const {
#ifdef ARGON_PLATFORM_MVE
    if constexpr (mve_float) {
      return simd::multiply_add_fused(vec_, b.vec_, c.vec_, active.native());
    } else
#endif
    {
      return active.Select(MultiplyAdd(b, c), argon_type{vec_});
    }
  }

  /// @copydoc MultiplyAdd(argon_type, argon_type, argon_bool_type) const
  ace argon_type MultiplyAdd(argon_type b, scalar_type c, argon_bool_type active) const {
#ifdef ARGON_PLATFORM_MVE
    if constexpr (mve_float) {
      return simd::multiply_add_fused(vec_, b.vec_, c, active.native());
    } else
#endif
    {
      return active.Select(MultiplyAdd(b, c), argon_type{vec_});
    }
  }

  /// MultiplySubtract under a predicate: lanes outside `active` keep this vector's value (as ACLE's vfmsq_m).
  ace argon_type MultiplySubtract(argon_type b, argon_type c, argon_bool_type active) const {
#ifdef ARGON_PLATFORM_MVE
    if constexpr (mve_float) {
      return simd::multiply_subtract_fused(vec_, b.vec_, c.vec_, active.native());
    } else
#endif
    {
      return active.Select(MultiplySubtract(b, c), argon_type{vec_});
    }
  }

  /// Compare only the lanes of `active`: a predicate active where `active` holds and a == b.
  /// @details MVE: one predicated compare (vcmpq_m), rather than a compare and a predicate AND through core registers.
  ace argon_bool_type Equal(argon_type b, argon_bool_type active) const {
#ifdef ARGON_PLATFORM_MVE
    return argon_bool_type{
        helpers::mve_compare<helpers::MveComparison::Equal>(vec_, b.vec_, active.native())};
#else
    return active & Equal(b);
#endif
  }

  /// Compare only the lanes of `active`: a predicate active where `active` holds and a > b.
  /// @copydetails Equal(argon_type, argon_bool_type) const
  ace argon_bool_type GreaterThan(argon_type b, argon_bool_type active) const {
#ifdef ARGON_PLATFORM_MVE
    return argon_bool_type{
        helpers::mve_compare<helpers::MveComparison::GreaterThan>(vec_, b.vec_, active.native())};
#else
    return active & GreaterThan(b);
#endif
  }

  /// Compare only the lanes of `active`: a predicate active where `active` holds and a >= b.
  /// @copydetails Equal(argon_type, argon_bool_type) const
  ace argon_bool_type GreaterThanOrEqual(argon_type b, argon_bool_type active) const {
#ifdef ARGON_PLATFORM_MVE
    return argon_bool_type{
        helpers::mve_compare<helpers::MveComparison::GreaterThanOrEqual>(vec_, b.vec_, active.native())};
#else
    return active & GreaterThanOrEqual(b);
#endif
  }

  /// Compare only the lanes of `active`: a predicate active where `active` holds and a < b.
  /// @copydetails Equal(argon_type, argon_bool_type) const
  ace argon_bool_type LessThan(argon_type b, argon_bool_type active) const { return b.GreaterThan(*this, active); }

  /// Compare only the lanes of `active`: a predicate active where `active` holds and a <= b.
  /// @copydetails Equal(argon_type, argon_bool_type) const
  ace argon_bool_type LessThanOrEqual(argon_type b, argon_bool_type active) const {
    return b.GreaterThanOrEqual(*this, active);
  }

  /// Count the number of consecutive bits following the sign bit that are set to the same value as the sign bit.
  /// @details Equivalent to std::countl_one(a).
  ace helpers::ArgonFor_t<simd::make_signed_t<Bool_t<VectorType>>> CountLeadingSignBits() const
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
    return ShuffleConcat<[](size_t i) { return i + n; }>(vec_, b.vec_);
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
    // Lanes of {a, b}: even result lanes come from a, odd ones from b (offset by `lanes`).
    return {ShuffleConcat<[](size_t i) { return i / 2 + (i % 2) * lanes; }>(vec_, b.vec_),
            ShuffleConcat<[](size_t i) { return (i + lanes) / 2 + (i % 2) * lanes; }>(vec_, b.vec_)};
#else
    return argon::to_array(neon::zip(vec_, b.vec()).val);
#endif
  }

  /// @brief Unzip two vectors, returning two vectors of pairs
  /// @details Given a pair of vector {a0, b0, a1, b1} and {a2, b2, a3, b3},
  /// the result is {{a0, a1, a2, a3}, {b0, b1, b2, b3}}
  std::array<argon_type, 2> UnzipWith(argon_type b) {
#ifdef ARGON_PLATFORM_MVE
    return {ShuffleConcat<[](size_t i) { return i * 2; }>(vec_, b.vec_),
            ShuffleConcat<[](size_t i) { return i * 2 + 1; }>(vec_, b.vec_)};
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
    return {ShuffleConcat<[](size_t i) { return i % 2 ? lanes + i - 1 : i; }>(vec_, b.vec_),
            ShuffleConcat<[](size_t i) { return i % 2 ? lanes + i : i + 1; }>(vec_, b.vec_)};
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
      // A vector subscript (out[i]) is not an lvalue a non-const reference can bind to under
      // Clang (GCC accepts it as an extension). Round-trip through a scalar so the callback's
      // scalar_type& binds to a real object, then write the mutated value back.
      scalar_type lane = out[i];
      body(lane);
      out[i] = lane;
    });
    return out;
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void(scalar_type&, int)>>
  ace argon_type each_lane_with_index(FuncType body) {
    VectorType out = vec_;
    utility::constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      // See each_lane: a non-const reference cannot bind to a vector subscript under Clang.
      scalar_type lane = out[i];
      body(lane, i);
      out[i] = lane;
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

  /// @brief Whether any lane is nonzero.
  ace bool any() const { return !Equal(argon_type{scalar_type{0}}).All(); }

  /// @brief Whether every lane is nonzero.
  ace bool all() const { return Equal(argon_type{scalar_type{0}}).None(); }

  template <std::size_t Index>
  std::tuple_element_t<Index, argon_type> get() {
#ifdef ARGON_PLATFORM_MVE
    return vec_[Index];
#else
    return GetLane<Index>();
#endif
  }

 protected:
  /// @brief The address of one gathered / scattered lane: base plus a byte offset, or base indexed by an element offset.
  template <bool byte_offsets, typename PointerType, typename OffsetType>
  ace static PointerType* LaneAddress(PointerType* base, OffsetType offset) {
    if constexpr (byte_offsets) {
      using byte_type = std::conditional_t<std::is_const_v<PointerType>, const char, char>;
      return reinterpret_cast<PointerType*>(reinterpret_cast<byte_type*>(base) + offset);
    } else {
      return base + offset;
    }
  }

  /// @brief Gather by byte or element offsets, optionally only the lanes of one predicate (inactive lanes are zero).
  template <bool byte_offsets, typename... PredicateType>
  ace static argon_type Gather(const scalar_type* base, offset_type offsets, PredicateType... active) {
    static_assert(sizeof...(PredicateType) <= 1);
#ifdef ARGON_PLATFORM_MVE
    const auto off = offsets.vec();
    if constexpr (sizeof(scalar_type) == 1) {
      return mve::load_byte_gather_offset(base, off, active.native()...);
    } else if constexpr (sizeof(scalar_type) == 2) {
      if constexpr (byte_offsets) {
        return mve::load_halfword_gather_offset(base, off, active.native()...);
      } else {
        return mve::load_halfword_gather_shifted_offset(base, off, active.native()...);
      }
    } else if constexpr (sizeof(scalar_type) == 4) {
      if constexpr (byte_offsets) {
        return mve::load_word_gather_offset(base, off, active.native()...);
      } else {
        return mve::load_word_gather_shifted_offset(base, off, active.native()...);
      }
    } else {
      if constexpr (byte_offsets) {
        return mve::load_doubleword_gather_offset(base, off, active.native()...);
      } else {
        return mve::load_doubleword_gather_shifted_offset(base, off, active.native()...);
      }
    }
#else
    argon_type destination{scalar_type{0}};  // inactive lanes stay zero
    utility::constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      if ((active.Active(i) && ...)) {
        const auto offset = simd::get_lane<i>(offsets.vec());
        destination = destination.template LoadToLane<i>(LaneAddress<byte_offsets>(base, offset));
      }
    });
    return destination;
#endif
  }

  /// @brief Scatter by byte or element offsets, optionally only the lanes of one predicate.
  template <bool byte_offsets, typename... PredicateType>
  ace void Scatter(scalar_type* base, offset_type offsets, PredicateType... active) const {
    static_assert(sizeof...(PredicateType) <= 1);
#ifdef ARGON_PLATFORM_MVE
    const auto off = offsets.vec();
    if constexpr (sizeof(scalar_type) == 1) {
      mve::store_byte_scatter_offset(base, off, vec_, active.native()...);
    } else if constexpr (sizeof(scalar_type) == 2) {
      if constexpr (byte_offsets) {
        mve::store_halfword_scatter_offset(base, off, vec_, active.native()...);
      } else {
        mve::store_halfword_scatter_shifted_offset(base, off, vec_, active.native()...);
      }
    } else if constexpr (sizeof(scalar_type) == 4) {
      if constexpr (byte_offsets) {
        mve::store_word_scatter_offset(base, off, vec_, active.native()...);
      } else {
        mve::store_word_scatter_shifted_offset(base, off, vec_, active.native()...);
      }
    } else {
      if constexpr (byte_offsets) {
        mve::store_doubleword_scatter_offset(base, off, vec_, active.native()...);
      } else {
        mve::store_doubleword_scatter_shifted_offset(base, off, vec_, active.native()...);
      }
    }
#else
    utility::constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      if ((active.Active(i) && ...)) {
        *LaneAddress<byte_offsets>(base, simd::get_lane<i>(offsets.vec())) = simd::get_lane<i>(vec_);
      }
    });
#endif
  }

  /// @brief Convert an arithmetic constructor argument to the lane type, passing anything else through.
  template <typename ArgType>
  ace static decltype(auto) LaneValue(ArgType&& arg) {
    if constexpr (lane_scalar<std::remove_cvref_t<ArgType>>) {
      return static_cast<scalar_type>(arg);
    } else {
      return std::forward<ArgType>(arg);
    }
  }

#ifdef ARGON_PLATFORM_MVE
  /// @brief Select lanes from the concatenation {a, b} by compile-time index (MVE has no vext/zip/uzp/trn).
  /// @tparam index A constexpr callable mapping each result lane to a lane of {a, b}.
  template <auto index>
  ace static VectorType ShuffleConcat(VectorType a, VectorType b) {
    return [&]<std::size_t... Is>(std::index_sequence<Is...>) {
      return VectorType(__builtin_shufflevector(a, b, index(Is)...));
    }(std::make_index_sequence<lanes>{});
  }
#endif

  template <std::size_t... Ints>
  ace static argon_type IotaHelper(scalar_type start, std::index_sequence<Ints...>) {
    return VectorType{static_cast<scalar_type>(start + Ints)...};
  }

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
