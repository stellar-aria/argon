#pragma once
#include "arm_simd.hpp"
#include "helpers/argon_for.hpp"

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
class Vector;

template <size_t LaneIndex, typename VectorType>
class ConstLane {
  using scalar_type = simd::Scalar_t<VectorType>;
  using type = ConstLane<LaneIndex, VectorType>;
  using argon_type = helpers::ArgonFor_t<VectorType>;

 public:
  ace ConstLane(VectorType& vec) : vec_{vec} {}
  ace operator scalar_type() const { return Get(); }
  ace argon_type operator=(const scalar_type b) { return vec_ = Set(b); }
  ace argon_type Load(const scalar_type* ptr) {
    if constexpr (platform == Platform::MVE) {
      Set(*ptr);
    } else {
      if constexpr (simd::is_quadword_v<VectorType>) {
        return simd::load1_lane_quad<LaneIndex>(ptr, vec_);
      } else {
        return simd::load1_lane<LaneIndex>(ptr, vec_);
      }
    }
  }
  ace argon_type Set(const scalar_type b) { return simd::set_lane<LaneIndex>(vec_, b); }
  ace scalar_type Get() const { return simd::get_lane<LaneIndex>(vec_); }

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
  ace argon_type operator=(const scalar_type b) { return vec_ = Set(b); }
  ace argon_type Load(const scalar_type* ptr) {
    if constexpr (platform == Platform::MVE) {
      Set(*ptr);
    } else {
      return simd::load1_lane(vec_, lane_, ptr);
    }
  }
  ace argon_type Set(const scalar_type b) { return simd::set_lane(vec_, lane_, b); }
  ace scalar_type Get() const { return simd::get_lane(vec_, lane_); }
  ace operator scalar_type() const { return Get(); }

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

  // friend class Vector<VectorType>;
};
}  // namespace argon
