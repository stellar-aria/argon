#pragma once
#include <array>
#include <span>
#include <ranges>
#include <type_traits>
#include "argon/argon64.hpp"
#include "argon/argon128.hpp"
#include "arm_simd/helpers/nonvec.hpp"

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

namespace argon {

template <typename T, typename V>
ace auto reinterpret(impl::Common<V> in) {
  if constexpr(simd::is_quadword_v<V>) {
    return Neon128<T>{simd::reinterpret<typename Neon128<T>::vector_type>(in.vec())};
  } else if constexpr(simd::is_doubleword_v<V>) {
    return Neon64<T>{simd::reinterpret<typename Neon64<T>::vector_type>(in.vec())};
  }
}

template <typename NeonType, simd::is_vector_type V>
ace NeonType reinterpret(V in) {
  static_assert(!std::is_same_v<typename NeonType::vector_type, V>);
  return NeonType{simd::reinterpret<typename NeonType::vector_type>(in)};
}

template <size_t stride, typename scalar_type, typename intrinsic_type>
ace void store_interleaved(scalar_type* ptr, std::array<intrinsic_type, stride> multi_vec) {
  store_interleaved<stride, scalar_type, intrinsic_type>(ptr, multi_vec.data());
}

template <size_t stride, typename scalar_type, typename intrinsic_type>
ace void store_interleaved(scalar_type* ptr, intrinsic_type* multi_vec) {
  static_assert(stride > 1 && stride < 5, "Interleaving Stores can only be performed with a stride of 2, 3, or 4");
  if constexpr (stride == 2) {
    simd::store2(ptr, *(typename impl::MultiVec<intrinsic_type, 2>::type*)multi_vec);
  } else if constexpr (stride == 3) {
    simd::store3(ptr, *(typename impl::MultiVec<intrinsic_type, 3>::type*)multi_vec);
  } else if constexpr (stride == 4) {
    simd::store4(ptr, *(typename impl::MultiVec<intrinsic_type, 4>::type*)multi_vec);
  }
}

template <typename scalar_type, typename intrinsic_type>
ace void store(scalar_type* ptr, intrinsic_type vector) {
  simd::store1(ptr, vector);
}

/**
 * @brief Store a contiguous collection of vectors to a location in memory, potentially with interleaving
 *
 * @tparam stride The interleaving stride: 2, 3, 4
 * @param ptr The location to store to
 * @param vectors The vectors to store.
 * @warning The length of vectors _must_ be a strict multiple of the stride.
 *          This function will attempt to store all vectors possible but WILL NOT STORE THE REMAINDER.
 */
template <size_t stride = 1, typename scalar_type, typename intrinsic_type>
requires std::is_same_v<scalar_type, typename simd::NonVec<intrinsic_type>::type>
ace void store(scalar_type* ptr, std::span<intrinsic_type> vectors) {
  // Best case scenerio: we know both length and stride
  static_assert(0 < stride && stride < 5, "Stores can only be performed with a stride of 1, 2, 3, or 4");
  //assert(vectors.size() >= stride, "You cannot store less vectors than your stride!");
  //assert(vectors.size() % stride == 0, "The number of vectors being stored must be a multiple of the stride!");

  if (stride == 1) {
    size_t tail_size = vectors.size() % 4;
#pragma unroll
    for (auto v : vectors | std::views::chunk(4)) {
      if (v.size() == 4) {  // 4-element chunks
        using multi_type = impl::MultiVec<intrinsic_type, 4>::type;
        simd::store1_x4(ptr, *(multi_type*)v.begin());
        ptr += (sizeof(intrinsic_type) / sizeof(*ptr)) * 4; // increment output pointer
      } else {
        if (tail_size == 1) {  // 1-element tail
          simd::store1(ptr, v.begin());
        } else if (tail_size == 2) {
          using tail_multi_type = impl::MultiVec<intrinsic_type, 2>::type;
          simd::store1_x2(ptr, *(tail_multi_type*)v.begin());
        } else if (tail_size == 3) {
          using tail_multi_type = impl::MultiVec<intrinsic_type, 3>::type;
          simd::store1_x3(ptr, *(tail_multi_type*)v.begin());
        }
      }
    }
  } else {
#pragma unroll
    for (auto v : vectors | std::views::chunk(stride)) {
      if (v.size() != stride) {
        return;
      }

      if constexpr (stride == 2) {
        store_interleaved<2>(ptr, v.begin());
      } else if constexpr (stride == 3) {
        store_interleaved<3>(ptr, v.begin());
      } else if constexpr (stride == 4) {
        store_interleaved<4>(ptr, v.begin());
      }
      ptr += sizeof(intrinsic_type) / sizeof(*ptr); // increment output pointer
    }
  }
}

/**
 * @brief Store an array of vectors to a location in memory, potentially with interleaving
 *
 * @tparam stride The interleaving stride: 2, 3, 4
 * @param ptr The location to store to
 * @param vectors The vectors to store.
 * @warning The length of vectors _must_ be a strict multiple of the stride.
 *          This function will attempt to store all vectors possible but WILL NOT STORE THE REMAINDER.
 */
template <size_t stride = 1, size_t size, typename scalar_type, typename intrinsic_type>
requires std::is_same_v<scalar_type, typename simd::NonVec<intrinsic_type>::type>
ace void store(scalar_type* ptr, std::array<intrinsic_type, size> vectors) {
  // Best case scenerio: we know both length and stride
  static_assert(0 < stride && stride < 5, "Stores can only be performed with a stride of 1, 2, 3, or 4");
  static_assert(size >= stride, "You cannot store less vectors than your stride!");
  static_assert(size % stride == 0, "The number of vectors being stored must be a multiple of the stride!");

  if constexpr (stride == 1) {
    constexpr size_t tail_size = size % 4;
#pragma unroll
    for (auto v : vectors | std::views::chunk(4)) {
      if (v.size() == 4) {  // 4-element chunks
        using multi_type = impl::MultiVec<intrinsic_type, 4>::type;
        simd::store1_x4(ptr, *(multi_type*)v.begin());
        ptr += (sizeof(intrinsic_type) / sizeof(*ptr)) * 4; // increment output pointer
      } else {
        if constexpr (tail_size == 1) {  // 1-element tail
          simd::store1(ptr, v.begin());
        } else if constexpr (tail_size == 2) {
          using tail_multi_type = impl::MultiVec<intrinsic_type, 2>::type;
          simd::store1_x2(ptr, *(tail_multi_type*)v.begin());
        } else if constexpr (tail_size == 3) {
          using tail_multi_type = impl::MultiVec<intrinsic_type, 3>::type;
          simd::store1_x3(ptr, *(tail_multi_type*)v.begin());
        }
      }
    }
  } else {
#pragma unroll
    for (auto v : vectors | std::views::chunk(stride)) {
      if constexpr (stride == 2) {
        store_interleaved<2>(ptr, v.begin());
      } else if constexpr (stride == 3) {
        store_interleaved<3>(ptr, v.begin());
      } else if constexpr (stride == 4) {
        store_interleaved<4>(ptr, v.begin());
      }
      ptr += sizeof(intrinsic_type) / sizeof(*ptr); // increment output pointer
    }
  }
}


template <int lane, size_t stride, typename scalar_type, typename intrinsic_type>
ace void store_lane_interleaved(scalar_type* ptr, std::array<intrinsic_type, stride> multi_vec) {
  store_lane_interleaved<lane, stride, scalar_type, intrinsic_type>(ptr, multi_vec.data());
}

template <int lane, size_t stride, typename scalar_type, typename intrinsic_type>
ace void store_lane_interleaved(scalar_type* ptr, intrinsic_type* multi_vec) {
  static_assert(stride > 1 && stride < 5, "Interleaving Stores can only be performed with a stride of 2, 3, or 4");
  if constexpr (stride == 2) {
    simd::store2_lane<lane>(ptr, *(typename impl::MultiVec<intrinsic_type, 2>::type*)multi_vec);
  } else if constexpr (stride == 3) {
    simd::store3_lane<lane>(ptr, *(typename impl::MultiVec<intrinsic_type, 3>::type*)multi_vec);
  } else if constexpr (stride == 4) {
    simd::store4_lane<lane>(ptr, *(typename impl::MultiVec<intrinsic_type, 4>::type*)multi_vec);
  }
}

template <typename neon_type>
ace std::array<neon_type, 2> zip(neon_type a, neon_type b) {
  using multivec_type = impl::MultiVec<typename neon_type::vector_type, 2>::type;
  using array_type = std::array<neon_type, 2>;

  // Since we're using a dirty ugly hack of reinterpreting a C array as a std::array,
  // the validity and POD-ness of std::array needs to be verified
  static_assert(std::is_standard_layout_v<array_type>);
  static_assert(std::is_trivial_v<array_type>);
  static_assert(sizeof(multivec_type) == sizeof(array_type),
                "std::array isn't layout-compatible with this NEON multi-vector.");

  return *(array_type*)simd::zip(a, b).val;
}

template <typename neon_type>
ace std::array<neon_type, 2> unzip(neon_type a, neon_type b) {
  using multivec_type = impl::MultiVec<typename neon_type::vector_type, 2>::type;
  using array_type = std::array<neon_type, 2>;

  // Since we're using a dirty ugly hack of reinterpreting a C array as a std::array,
  // the validity and POD-ness of std::array needs to be verified
  static_assert(std::is_standard_layout_v<array_type>);
  static_assert(std::is_trivial_v<array_type>);
  static_assert(sizeof(multivec_type) == sizeof(array_type),
                "std::array isn't layout-compatible with this NEON multi-vector.");

  return *(array_type*)simd::unzip(a, b).val;
}

template <typename neon_type>
ace std::array<neon_type, 2> transpose(neon_type a, neon_type b) {
  using multivec_type = impl::MultiVec<typename neon_type::vector_type, 2>::type;
  using array_type = std::array<neon_type, 2>;

  // Since we're using a dirty ugly hack of reinterpreting a C array as a std::array,
  // the validity and POD-ness of std::array needs to be verified
  static_assert(std::is_standard_layout_v<array_type>);
  static_assert(std::is_trivial_v<array_type>);
  static_assert(sizeof(multivec_type) == sizeof(array_type),
                "std::array isn't layout-compatible with this NEON multi-vector.");

  return *(array_type*)simd::transpose(a, b).val;
}

template <typename T>
ace Neon128<T> combine(Neon64<T> low, Neon64<T> high) { return simd::combine(low, high); }

}  // namespace argon

namespace std {
template <typename T>
struct tuple_size<argon::impl::Common<T>> {
  static constexpr size_t value = argon::impl::Common<T>::lanes;
};

template <typename T>
struct tuple_size<Neon128<T>> {
  static constexpr size_t value = Neon128<T>::lanes;
};

template <typename T>
struct tuple_size<Neon64<T>> {
  static constexpr size_t value = Neon64<T>::lanes;
};

template <size_t Index, typename T>
struct tuple_element<Index, argon::impl::Common<T>> {
  static_assert(Index < argon::impl::Common<T>::lanes);
  using type = argon::impl::Common<T>::lane_type;
};

template <size_t Index, typename T>
struct tuple_element<Index, Neon128<T>> {
  static_assert(Index < Neon128<T>::lanes);
  using type = argon::impl::Lane<typename Neon128<T>::vector_type>;
};

template <size_t Index, typename T>
struct tuple_element<Index, Neon64<T>> {
  static_assert(Index < Neon64<T>::lanes);
  using type = argon::impl::Lane<typename Neon64<T>::vector_type>;
};
}  // namespace std

template <typename scalar_type>
using Argon64 = Neon64<scalar_type>;
template <typename scalar_type>
using Argon128 = Neon128<scalar_type>;

#undef ace
#undef simd
