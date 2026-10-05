#pragma once
#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>
#include "arm_simd.hpp"
#include "arm_simd/helpers/scalar.hpp"
#include "features.h"
#include "helpers/argon_for.hpp"
#include "helpers/bool.hpp"
#include "helpers/mve_compare.hpp"

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

/// @file predicate.hpp
/// @brief A per-lane boolean for a SIMD vector type, as returned by comparisons.

namespace argon {

/// @brief A per-lane boolean for vectors of type VectorType, as returned by comparisons.
/// @tparam VectorType The vector type the predicate applies to (e.g., int32x4_t, float32x4_t).
/// @details On NEON a predicate is a mask vector, with every bit of a lane set when the lane is active. On MVE it is
/// an mve_pred16_t, with one bit per byte of the vector, so a 32-bit lane owns four bits. The interface is the same on
/// both, so code written against it is portable; use ToMask() where a mask vector is genuinely needed.
template <typename VectorType>
class Predicate {
  using scalar_type = simd::Scalar_t<VectorType>;

 public:
  using vector_type = VectorType;                         ///< The vector type the predicate applies to.
  using mask_type = Bool_t<VectorType>;                   ///< The equivalent mask vector type.
  using mask_scalar = simd::Scalar_t<mask_type>;          ///< The lane type of the mask vector.
  using argon_mask_type = helpers::ArgonFor_t<mask_type>; ///< The Argon type of the mask vector.
#ifdef ARGON_PLATFORM_MVE
  using storage_type = mve_pred16_t;  ///< The native predicate representation.
#else
  using storage_type = mask_type;  ///< The native predicate representation.
#endif

  /// @brief The number of lanes the predicate covers.
  static constexpr size_t lanes = sizeof(VectorType) / sizeof(scalar_type);

  /// @brief Construct from the native predicate representation (see storage_type).
  ace explicit Predicate(storage_type p) : p_{p} {}

  /// @brief A predicate with every lane active.
  ace static Predicate True() {
#ifdef ARGON_PLATFORM_MVE
    return Predicate{static_cast<storage_type>(0xFFFF)};
#else
    return Predicate{argon_mask_type{static_cast<mask_scalar>(~mask_scalar{0})}.vec()};
#endif
  }

  /// @brief A predicate with no lanes active.
  ace static Predicate False() {
#ifdef ARGON_PLATFORM_MVE
    return Predicate{storage_type{0}};
#else
    return Predicate{argon_mask_type{mask_scalar{0}}.vec()};
#endif
  }

  /// @brief A predicate with the first `n` lanes active, and the rest inactive.
  /// @details On MVE this is vctp, the predicate that tail-predicated loops are built from.
  /// @param n The number of active lanes; values of `lanes` or more activate every lane.
  ace static Predicate FirstN(size_t n) {
#ifdef ARGON_PLATFORM_MVE
    if constexpr (sizeof(scalar_type) == 1) {
      return Predicate{mve::create_tail_predicate8(static_cast<uint32_t>(n))};
    } else if constexpr (sizeof(scalar_type) == 2) {
      return Predicate{mve::create_tail_predicate16(static_cast<uint32_t>(n))};
    } else if constexpr (sizeof(scalar_type) == 4) {
      return Predicate{mve::create_tail_predicate32(static_cast<uint32_t>(n))};
    } else {
      return Predicate{mve::create_tail_predicate64(static_cast<uint32_t>(n))};
    }
#else
    if (n >= lanes) {
      return True();
    }
    const auto index = argon_mask_type::Iota(0);
    return Predicate{(index < argon_mask_type{static_cast<mask_scalar>(n)}).native()};
#endif
  }

  /// @brief Construct from a mask vector, treating any nonzero lane as active.
  /// @param mask The mask vector.
  ace static Predicate FromMask(argon_mask_type mask) {
#ifdef ARGON_PLATFORM_MVE
    return Predicate{mve::not_equal(mask.vec(), mask_scalar{0})};
#else
    return Predicate{mask.vec()};
#endif
  }

  /// @brief Expand the predicate into a mask vector: every bit set in active lanes, clear in inactive ones.
  ace argon_mask_type ToMask() const {
#ifdef ARGON_PLATFORM_MVE
    return argon_mask_type{helpers::mve_mask<VectorType>(p_)};
#else
    return argon_mask_type{p_};
#endif
  }

  /// @brief Implicitly convert to the mask vector that comparisons used to return.
  [[deprecated("Comparisons now return argon::Predicate; use ToMask() or the Predicate interface")]]
  ace operator argon_mask_type() const {
    return ToMask();
  }

  /// @brief The native predicate representation: a mask vector on NEON, an mve_pred16_t on MVE.
  ace storage_type native() const { return p_; }

  /// @brief Lanes active in both predicates.
  ace Predicate operator&(Predicate b) const {
#ifdef ARGON_PLATFORM_MVE
    return Predicate{static_cast<storage_type>(p_ & b.p_)};
#else
    return Predicate{(argon_mask_type{p_} & argon_mask_type{b.p_}).vec()};
#endif
  }

  /// @brief Lanes active in either predicate.
  ace Predicate operator|(Predicate b) const {
#ifdef ARGON_PLATFORM_MVE
    return Predicate{static_cast<storage_type>(p_ | b.p_)};
#else
    return Predicate{(argon_mask_type{p_} | argon_mask_type{b.p_}).vec()};
#endif
  }

  /// @brief Lanes active in exactly one of the predicates.
  ace Predicate operator^(Predicate b) const {
#ifdef ARGON_PLATFORM_MVE
    return Predicate{static_cast<storage_type>(p_ ^ b.p_)};
#else
    return Predicate{(argon_mask_type{p_} ^ argon_mask_type{b.p_}).vec()};
#endif
  }

  /// @brief Invert every lane.
  ace Predicate operator~() const {
#ifdef ARGON_PLATFORM_MVE
    return Predicate{mve::predicate_not(p_)};
#else
    return Predicate{(~argon_mask_type{p_}).vec()};
#endif
  }

  /// @brief Lanes active in both predicates; the same as `&`.
  /// @note Both operands are always evaluated: there is no short-circuit for per-lane logic.
  ace Predicate operator&&(Predicate b) const { return *this & b; }

  /// @brief Lanes active in either predicate; the same as `|`.
  /// @note Both operands are always evaluated: there is no short-circuit for per-lane logic.
  ace Predicate operator||(Predicate b) const { return *this | b; }

  /// @brief Invert every lane; the same as `~`.
  ace Predicate operator!() const { return ~*this; }

  /// @brief Choose each lane from `true_value` where the predicate is active, and from `false_value` otherwise.
  /// @details NEON: vbsl. MVE: vpsel.
  /// @param true_value The lanes to take where the predicate is active.
  /// @param false_value The lanes to take where the predicate is inactive.
  /// @return A vector of the operands' type.
  template <typename ArgType>
    requires(ArgType::lanes == lanes && sizeof(typename ArgType::vector_type) == sizeof(VectorType))
  ace ArgType Select(ArgType true_value, ArgType false_value) const {
#ifdef ARGON_PLATFORM_MVE
    const auto t = std::bit_cast<mask_type>(true_value.vec());
    const auto f = std::bit_cast<mask_type>(false_value.vec());
    return ArgType{std::bit_cast<typename ArgType::vector_type>(mve::predicate_select(t, f, p_))};
#else
    return argon_mask_type{p_}.BitwiseSelect(true_value, false_value);
#endif
  }

  /// @brief Whether any lane is active.
  ace bool Any() const {
#ifdef ARGON_PLATFORM_MVE
    return p_ != 0;
#else
    for (uint64_t word : words()) {
      if (word != 0) return true;
    }
    return false;
#endif
  }

  /// @brief Whether every lane is active.
  ace bool All() const {
#ifdef ARGON_PLATFORM_MVE
    return p_ == 0xFFFF;
#else
    for (uint64_t word : words()) {
      if (word != ~uint64_t{0}) return false;
    }
    return true;
#endif
  }

  /// @brief Whether no lane is active.
  ace bool None() const { return !Any(); }

  /// @brief The number of active lanes.
  ace size_t Count() const {
#ifdef ARGON_PLATFORM_MVE
    if constexpr (sizeof(scalar_type) < 8) {
      // Armv8.1-M has no popcount instruction; count with a predicated across-vector add instead.
      return mve::reduce_add(mve::duplicate(mask_scalar{1}), p_);
    } else {
      return std::popcount(static_cast<uint16_t>(p_)) / sizeof(scalar_type);
    }
#else
    size_t bits = 0;
    for (uint64_t word : words()) {
      bits += std::popcount(word);
    }
    return bits / (8 * sizeof(scalar_type));
#endif
  }

  /// @brief Whether a single lane is active.
  /// @param i The lane index.
  ace bool Active(size_t i) const {
#ifdef ARGON_PLATFORM_MVE
    return (p_ >> (i * sizeof(scalar_type))) & 1;
#else
    return std::bit_cast<std::array<mask_scalar, lanes>>(p_)[i] != 0;
#endif
  }

  /// @brief The active state of every lane, in lane order.
  ace std::array<bool, lanes> to_array() const {
    std::array<bool, lanes> out{};
    for (size_t i = 0; i < lanes; ++i) {
      out[i] = Active(i);
    }
    return out;
  }

 private:
#ifndef ARGON_PLATFORM_MVE
  /// The mask viewed as 64-bit words, which is how Any/All/Count fold it on NEON.
  ace std::array<uint64_t, sizeof(mask_type) / 8> words() const {
    return std::bit_cast<std::array<uint64_t, sizeof(mask_type) / 8>>(p_);
  }
#endif

  storage_type p_;
};

}  // namespace argon

#undef ace
#undef simd
