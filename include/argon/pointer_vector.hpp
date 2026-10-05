#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>
#include "argon/argon_full.hpp"

/// @file pointer_vector.hpp
/// @brief A vector of pointers, one per lane, for gathering from and scattering to several buffers in lockstep.

namespace argon {

/// @brief One pointer per lane, gathered from and scattered to together, and advanced together: walking several
/// buffers (channels, matrix columns, filter states) at once.
/// @tparam T The element type: 32-bit (4 lanes) or 64-bit (2 lanes). A const type allows loads only.
/// @details On MVE the pointers live in a vector register and each access is one gather or scatter (vldrw / vldrd
/// / vstrw / vstrd with a vector of base addresses). Elsewhere they are ordinary pointers, accessed lane by lane.
/// Offsets and steps are in bytes; as the instructions require, they are multiples of sizeof(T), within ±508 bytes
/// for 32-bit elements and ±1016 for 64-bit ones. The limits apply on every platform, so code stays portable.
template <typename T>
  requires(lane_scalar<std::remove_const_t<T>> && (sizeof(T) == 4 || sizeof(T) == 8))
class PointerVector {
  using value_type = std::remove_const_t<T>;

 public:
  using argon_type = Argon<value_type>;                ///< The vector type loaded and stored.
  static constexpr size_t lanes = argon_type::lanes;  ///< The number of pointers.

  /// @brief Whether a byte offset or step is encodable: a multiple of the element size, within range.
  template <int offset>
  static constexpr bool valid_offset = offset % int{sizeof(T)} == 0 && offset >= -127 * int{sizeof(T)} &&
                                       offset <= 127 * int{sizeof(T)};

  /// @brief Point lane i at `pointers[i]`.
  explicit PointerVector(const std::array<T*, lanes>& pointers) {
#ifdef ARGON_PLATFORM_MVE
    std::array<address_scalar, lanes> addresses{};
    for (size_t i = 0; i < lanes; ++i) addresses[i] = static_cast<address_scalar>(reinterpret_cast<uintptr_t>(pointers[i]));
    addresses_ = Argon<address_scalar>::Load(addresses.data()).vec();
#else
    pointers_ = pointers;
#endif
  }

  /// @brief The current pointers.
  std::array<T*, lanes> pointers() const {
#ifdef ARGON_PLATFORM_MVE
    const auto addresses = Argon<address_scalar>{addresses_}.to_array();
    std::array<T*, lanes> out{};
    for (size_t i = 0; i < lanes; ++i) out[i] = reinterpret_cast<T*>(static_cast<uintptr_t>(addresses[i]));
    return out;
#else
    return pointers_;
#endif
  }

  /// @brief Load lane i from `offset` bytes past pointer i.
  template <int offset = 0>
    requires valid_offset<offset>
  argon_type Load() const {
#ifdef ARGON_PLATFORM_MVE
    if constexpr (std::is_same_v<value_type, int32_t>) {
      return vldrwq_gather_base_s32(addresses_, offset);
    } else if constexpr (std::is_same_v<value_type, uint32_t>) {
      return vldrwq_gather_base_u32(addresses_, offset);
    } else if constexpr (std::is_same_v<value_type, float>) {
      return vldrwq_gather_base_f32(addresses_, offset);
    } else if constexpr (std::is_same_v<value_type, int64_t>) {
      return vldrdq_gather_base_s64(addresses_, offset);
    } else {
      return vldrdq_gather_base_u64(addresses_, offset);
    }
#else
    std::array<value_type, lanes> out{};
    for (size_t i = 0; i < lanes; ++i) out[i] = *At<offset>(i);
    return argon_type::Load(out.data());
#endif
  }

  /// @brief Store lane i of `value` to `offset` bytes past pointer i.
  template <int offset = 0>
    requires(valid_offset<offset> && !std::is_const_v<T>)
  void Store(argon_type value) const {
#ifdef ARGON_PLATFORM_MVE
    if constexpr (std::is_same_v<value_type, int32_t>) {
      vstrwq_scatter_base_s32(addresses_, offset, value.vec());
    } else if constexpr (std::is_same_v<value_type, uint32_t>) {
      vstrwq_scatter_base_u32(addresses_, offset, value.vec());
    } else if constexpr (std::is_same_v<value_type, float>) {
      vstrwq_scatter_base_f32(addresses_, offset, value.vec());
    } else if constexpr (std::is_same_v<value_type, int64_t>) {
      vstrdq_scatter_base_s64(addresses_, offset, value.vec());
    } else {
      vstrdq_scatter_base_u64(addresses_, offset, value.vec());
    }
#else
    const auto values = value.to_array();
    for (size_t i = 0; i < lanes; ++i) *At<offset>(i) = values[i];
#endif
  }

  /// @brief Advance every pointer by `step` bytes.
  template <int step>
    requires valid_offset<step>
  void Advance() {
#ifdef ARGON_PLATFORM_MVE
    addresses_ = (Argon<address_scalar>{addresses_} + Argon<address_scalar>{static_cast<address_scalar>(step)}).vec();
#else
    for (auto& p : pointers_) p = reinterpret_cast<T*>(reinterpret_cast<std::conditional_t<std::is_const_v<T>, const char, char>*>(p) + step);
#endif
  }

  /// @brief Advance every pointer by `step` bytes, then load through them: one step of a lockstep walk.
  /// @details MVE with clang: the pre-incrementing write-back gather (vldrw.32 ... [q]!). GCC 16.2 crashes on the
  /// 32-bit write-back intrinsics given anything but the address of a local, so with GCC this is a gather and an
  /// add, with the same result.
  template <int step>
    requires valid_offset<step>
  argon_type AdvanceAndLoad() {
#if defined(ARGON_PLATFORM_MVE) && defined(__clang__)
    if constexpr (std::is_same_v<value_type, int32_t>) {
      return vldrwq_gather_base_wb_s32(&addresses_, step);
    } else if constexpr (std::is_same_v<value_type, uint32_t>) {
      return vldrwq_gather_base_wb_u32(&addresses_, step);
    } else if constexpr (std::is_same_v<value_type, float>) {
      return vldrwq_gather_base_wb_f32(&addresses_, step);
    } else if constexpr (std::is_same_v<value_type, int64_t>) {
      return vldrdq_gather_base_wb_s64(&addresses_, step);
    } else {
      return vldrdq_gather_base_wb_u64(&addresses_, step);
    }
#else
    auto value = Load<step>();
    Advance<step>();
    return value;
#endif
  }

  /// @brief Advance every pointer by `step` bytes, then store `value` through them.
  /// @details MVE with clang: the write-back scatter (vstrw.32 ... [q]!); with GCC a scatter and an add, as for
  /// AdvanceAndLoad.
  template <int step>
    requires(valid_offset<step> && !std::is_const_v<T>)
  void AdvanceAndStore(argon_type value) {
#if defined(ARGON_PLATFORM_MVE) && defined(__clang__)
    if constexpr (std::is_same_v<value_type, int32_t>) {
      vstrwq_scatter_base_wb_s32(&addresses_, step, value.vec());
    } else if constexpr (std::is_same_v<value_type, uint32_t>) {
      vstrwq_scatter_base_wb_u32(&addresses_, step, value.vec());
    } else if constexpr (std::is_same_v<value_type, float>) {
      vstrwq_scatter_base_wb_f32(&addresses_, step, value.vec());
    } else if constexpr (std::is_same_v<value_type, int64_t>) {
      vstrdq_scatter_base_wb_s64(&addresses_, step, value.vec());
    } else {
      vstrdq_scatter_base_wb_u64(&addresses_, step, value.vec());
    }
#else
    Store<step>(value);
    Advance<step>();
#endif
  }

 private:
#ifdef ARGON_PLATFORM_MVE
  // Addresses are 32-bit on M-profile; 64-bit elements gather through a uint64x2_t of addresses.
  using address_scalar = std::conditional_t<sizeof(T) == 4, uint32_t, uint64_t>;
  typename Argon<address_scalar>::vector_type addresses_;
#else
  template <int offset>
  T* At(size_t lane) const {
    using byte = std::conditional_t<std::is_const_v<T>, const char, char>;
    return reinterpret_cast<T*>(reinterpret_cast<byte*>(pointers_[lane]) + offset);
  }

  std::array<T*, lanes> pointers_{};
#endif
};

}  // namespace argon
