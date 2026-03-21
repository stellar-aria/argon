#pragma once
#include "arm_simd.hpp"
#include "arm_simd/helpers/scalar.hpp"
#include "arm_simd/helpers/vec64.hpp"
#include "features.h"
#include "helpers/argon_for.hpp"

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
class Vector;

#ifdef ARGON_PLATFORM_MVE

// MVE does not support lane manipulators, so we use the scalar type directly
// for the lane type.

template <size_t, typename VectorType>
using ConstLane = simd::Scalar_t<VectorType>;

template <typename VectorType>
using Lane = simd::Scalar_t<VectorType>;

#else

/// @brief Represents a single lane of a SIMD vector with the lane index known at compile time.
/// @tparam LaneIndex Compile-time lane index within the vector.
/// @tparam VectorType The intrinsic SIMD vector type (e.g., `int32x4_t`).
/// @details Provides type-safe read/write access to one element of a SIMD register.
/// On ARM32 (`__ARM_ARCH < 8`) quadword vectors, `vec()` returns the 64-bit half-register
/// that contains the lane, and `lane()` returns the local index within that half.
template <size_t LaneIndex, typename VectorType>
class ConstLane {
  using scalar_type = simd::Scalar_t<VectorType>;
  using type = ConstLane<LaneIndex, VectorType>;
  using argon_type = helpers::ArgonFor_t<VectorType>;

 public:
  /// @brief Construct a lane accessor bound to `vec`.
  ace ConstLane(VectorType& vec) : vec_{vec} {}
  /// @brief Read the lane value (implicit conversion to scalar).
  ace operator scalar_type() const { return Get(); }
  /// @brief Write a scalar value into this lane and return the updated vector.
  ace argon_type operator=(const scalar_type b) { return vec_ = Set(b); }
  /// @brief Load a scalar from `ptr` into this lane.
  ace argon_type Load(const scalar_type* ptr) {
#ifdef ARGON_PLATFORM_MVE
    Set(*ptr);
#else
    if constexpr (simd::is_quadword_v<VectorType>) {
      return simd::load1_lane_quad<LaneIndex>(ptr, vec_);
    } else {
      return simd::load1_lane<LaneIndex>(ptr, vec_);
    }
#endif
  }
  /// @brief Set this lane to `b` and return the updated vector.
  ace argon_type Set(const scalar_type b) { return simd::set_lane<LaneIndex>(b, vec_); }
  /// @brief Get the scalar value of this lane.
  ace scalar_type Get() const { return simd::get_lane<LaneIndex>(vec_); }

#if __ARM_ARCH >= 8
  /// @brief Return the full vector held by this lane accessor.
  ace VectorType vec() { return vec_; }
  /// @brief Return the lane index.
  ace const int lane() { return LaneIndex; }
#else
  /// @brief On ARM32, return the 64-bit half-register that contains this lane.
  ace neon::Vec64_t<scalar_type> vec() {
    if constexpr (simd::is_doubleword_v<VectorType>) {
      return vec_;
    } else if constexpr (simd::is_quadword_v<VectorType>) {
      if constexpr (LaneIndex >= ArgonHalf<scalar_type>::lanes) {
        return simd::get_high(vec_);
      } else {
        return simd::get_low(vec_);
      }
    }
  }
  /// @brief On ARM32, return the local lane index within the 64-bit half-register returned by `vec()`.
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

/// @brief Represents a single lane of a SIMD vector with a runtime-determined index.
/// @tparam VectorType The intrinsic SIMD vector type (e.g., `int32x4_t`).
/// @details Provides type-safe read/write access to one element of a SIMD register when the lane
/// index is not known until runtime. On ARM32 (`__ARM_ARCH < 8`) quadword vectors, `vec()` returns
/// the 64-bit half-register containing the lane, and `lane()` returns the local index within that half.
template <typename VectorType>
class Lane {
  using scalar_type = simd::Scalar_t<VectorType>;
  using type = Lane<VectorType>;
  using argon_type = helpers::ArgonFor_t<VectorType>;

 public:
  /// @brief Construct a lane accessor bound to `vec` at runtime index `lane`.
  ace Lane(VectorType& vec, const int lane) : vec_{vec}, lane_{lane} {}
  /// @brief Write a scalar value into this lane and return the updated vector.
  ace argon_type operator=(const scalar_type b) { return vec_ = Set(b); }
  /// @brief Load a scalar from `ptr` into this lane and return the updated vector.
  [[nodiscard]] ace argon_type Load(const scalar_type* ptr) {
#ifdef ARGON_PLATFORM_MVE
    return Set(*ptr);
#else
    return simd::load1_lane(vec_, lane_, ptr);
#endif
  }
  /// @brief Set this lane to `b` and return the updated vector.
  ace argon_type Set(const scalar_type b) { return simd::set_lane(vec_, lane_, b); }
  /// @brief Get the scalar value of this lane.
  ace scalar_type Get() const { return simd::get_lane(vec_, lane_); }
  /// @brief Read the lane value (implicit conversion to scalar).
  ace operator scalar_type() const { return Get(); }

#if __ARM_ARCH >= 8
  /// @brief Return the full vector held by this lane accessor.
  ace VectorType vec() { return vec_; }
  /// @brief Return the runtime lane index.
  ace const int lane() { return lane_; }
#else
  /// @brief On ARM32, return the 64-bit half-register that contains this lane.
  ace neon::Vec64_t<scalar_type> vec() {
    if constexpr (simd::is_doubleword_v<VectorType>) {
      return vec_;
    } else if constexpr (simd::is_quadword_v<VectorType>) {
      if (lane_ >= ArgonHalf<scalar_type>::lanes) {
        return simd::get_high(vec_);
      } else {
        return simd::get_low(vec_);
      }
    }
  }
  /// @brief On ARM32, return the local lane index within the 64-bit half-register returned by `vec()`.
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

  // friend class Vector<VectorType>;
};
#endif
}  // namespace argon
