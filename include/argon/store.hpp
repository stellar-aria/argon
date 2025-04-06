#pragma once
#include <array>
#include <cstddef>
#include <type_traits>
#include <ranges>
#include "arm_simd/helpers/concepts.hpp"
#include "arm_simd/helpers/scalar.hpp"
#include "helpers/multivec.hpp"


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
template <size_t stride, typename scalar_type, typename intrinsic_type>
ace void store_interleaved(scalar_type* ptr, helpers::MultiVec_t<intrinsic_type, stride> multi_vec) {
  static_assert(stride > 1 && stride < 5, "Interleaving Stores can only be performed with a stride of 2, 3, or 4");
  if constexpr (stride == 2) {
    simd::store2(ptr, multi_vec);
  } else if constexpr (stride == 3) {
    simd::store3(ptr, multi_vec);
  } else if constexpr (stride == 4) {
    simd::store4(ptr, multi_vec);
  }
}

template <size_t stride, typename scalar_type, typename argon_type>
ace void store_interleaved(scalar_type* ptr, std::array<argon_type, stride> multi_vec) {
  using intrinsic_type = typename argon_type::vector_type;
  using multivec_type = helpers::MultiVec_t<intrinsic_type, stride>;
  using array_type = std::array<argon_type, stride>;

  // Since we're using a dirty ugly hack of reinterpreting a C array as a std::array,
  // the validity and POD-ness of std::array needs to be verified
  static_assert(std::is_standard_layout_v<array_type>);
  static_assert(sizeof(multivec_type) == sizeof(array_type),
                "std::array isn't layout-compatible with this NEON multi-vector.");

  store_interleaved<stride, scalar_type, intrinsic_type>(ptr, *(multivec_type*)multi_vec.data());
}

template <size_t stride, typename scalar_type, typename... argon_types>
ace void store_interleaved(scalar_type* ptr, argon_types... vecs) {
  store_interleaved<sizeof...(argon_types)>(
      ptr, std::array<std::common_type_t<argon_types...>, sizeof...(vecs)>{std::forward<argon_types>(vecs)...});
}

template <typename scalar_type, typename argon_type>
  requires std::is_same_v<scalar_type, simd::Scalar_t<typename argon_type::vector_type>>
ace void store(scalar_type* ptr, argon_type vector) {
  simd::store1(ptr, vector);
}

template <typename scalar_type, simd::is_vector_type intrinsic_type>
  requires std::is_same_v<scalar_type, typename simd::Scalar<intrinsic_type>::type>
ace void store(scalar_type* ptr, intrinsic_type vector) {
  simd::store1(ptr, vector);
}

#if defined(__clang__) || (__GNUC__ > 13)
/**
 * @brief Store an array of vectors to a location in memory, potentially with interleaving
 *
 * @tparam stride The interleaving stride: 2, 3, 4
 * @param ptr The location to store to
 * @param vectors The vectors to store.
 * @warning The length of vectors _must_ be a strict multiple of the stride.
 *          This function will attempt to store all vectors possible but WILL NOT STORE ANY REMAINDER.
 */
template <size_t stride = 1, typename scalar_type, typename... intrinsic_types>
  requires(std::is_same_v<scalar_type, simd::Scalar_t<intrinsic_types>> && ...)
ace void store(scalar_type* ptr, intrinsic_types... vectors) {
  // TODO: C++26 change to `typename intrinsic_types...[0]`
  using intrinsic_type = typename std::tuple_element<0, std::tuple<intrinsic_types...>>::type;

  constexpr size_t size = sizeof...(vectors);
  const std::array<intrinsic_type, sizeof...(vectors)> vec_array = {vectors...};

  // Best case scenerio: we know both length and stride
  static_assert(0 < stride && stride < 5, "Stores can only be performed with a stride of 1, 2, 3, or 4");
  static_assert(size >= stride, "You cannot store less vectors than your stride!");
  static_assert(size % stride == 0, "The number of vectors being stored must be a multiple of the stride!");

  if constexpr (stride == 1) {
    constexpr size_t tail_size = size % 4;
#pragma unroll
    for (auto v : vec_array | std::views::chunk(4)) {
      if (v.size() == 4) {  // 4-element chunks
        using multi_type = helpers::MultiVec<intrinsic_type, 4>::type;
        simd::store1_x4(ptr, *(multi_type*)v.begin());
        ptr += (sizeof(intrinsic_type) / sizeof(*ptr)) * 4;  // increment output pointer
      } else {
        if constexpr (tail_size == 1) {  // 1-element tail
          simd::store1(ptr, v.begin());
        } else if constexpr (tail_size == 2) {
          using tail_multi_type = helpers::MultiVec<intrinsic_type, 2>::type;
          simd::store1_x2(ptr, *(tail_multi_type*)v.begin());
        } else if constexpr (tail_size == 3) {
          using tail_multi_type = helpers::MultiVec<intrinsic_type, 3>::type;
          simd::store1_x3(ptr, *(tail_multi_type*)v.begin());
        }
      }
    }
  } else {
#pragma unroll
    for (auto v : vec_array | std::views::chunk(stride)) {
      if constexpr (stride == 2) {
        store_interleaved<2>(ptr, v.begin());
      } else if constexpr (stride == 3) {
        store_interleaved<3>(ptr, v.begin());
      } else if constexpr (stride == 4) {
        store_interleaved<4>(ptr, v.begin());
      }
      ptr += sizeof(intrinsic_type) / sizeof(*ptr);  // increment output pointer
    }
  }
}

template <size_t stride = 1, typename scalar_type, typename... argon_types>
  requires(std::is_same_v<scalar_type, simd::Scalar_t<typename argon_types::vector_type>> && ...)
ace void store(scalar_type* ptr, argon_types... vectors) {
  store<stride>(ptr, std::forward<typename argon_types::vector_type>(vectors)...);
}
#endif

template <int lane, size_t stride, typename scalar_type, typename argon_type>
ace void store_lane_interleaved(scalar_type* ptr, std::array<argon_type, stride> multi_vec) {
  using intrinsic_type = typename argon_type::vector_type;
  using multivec_type = helpers::MultiVec_t<intrinsic_type, stride>;
  using array_type = std::array<argon_type, 2>;

  // Since we're using a dirty ugly hack of reinterpreting a C array as a std::array,
  // the validity and POD-ness of std::array needs to be verified
  static_assert(std::is_standard_layout_v<array_type>);
  static_assert(std::is_trivial_v<array_type>);
  static_assert(sizeof(multivec_type) == sizeof(array_type),
                "std::array isn't layout-compatible with this NEON multi-vector.");

  store_lane_interleaved<lane, stride, scalar_type, intrinsic_type>(ptr, *(multivec_type*)multi_vec.data());
}

template <int lane, size_t stride, typename scalar_type, typename intrinsic_type>
ace void store_lane_interleaved(scalar_type* ptr, helpers::MultiVec_t<intrinsic_type, stride> multi_vec) {
  static_assert(stride > 1 && stride < 5, "Interleaving Stores can only be performed with a stride of 2, 3, or 4");
  if constexpr (stride == 2) {
    simd::store2_lane<lane>(ptr, multi_vec);
  } else if constexpr (stride == 3) {
    simd::store3_lane<lane>(ptr, multi_vec);
  } else if constexpr (stride == 4) {
    simd::store4_lane<lane>(ptr, multi_vec);
  }
}
}  // namespace argon
#undef ace
#undef simd
