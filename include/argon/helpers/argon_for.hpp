#pragma once
#include "arm_simd/helpers/concepts.hpp"
#include "arm_simd/helpers/nonvec.hpp"

#ifdef __ARM_NEON
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#define simd helium
#endif
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
}  // namespace argon::impl
#undef simd
