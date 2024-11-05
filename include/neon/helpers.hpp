#pragma once
#include <arm_neon.h>
#include "../neon.hpp"

#ifdef __clang__
#define nce [[gnu::always_inline]] constexpr
#else
#define nce [[gnu::always_inline]] inline
#endif

namespace neon {
// clang-format off
template <typename T> struct make_unsigned;
template <typename T> struct make_signed;

template <> struct make_unsigned<int8x8_t> { using type = uint8x8_t; };
template <> struct make_unsigned<int8x16_t> { using type = uint8x16_t; };

template <> struct make_unsigned<uint8x8_t> { using type = uint8x8_t; };
template <> struct make_unsigned<uint8x16_t> { using type = uint8x16_t; };

template <> struct make_signed<uint8x8_t> { using type = int8x8_t; };
template <> struct make_signed<uint8x16_t> { using type = int8x16_t; };

template <> struct make_signed<int8x8_t> { using type = int8x8_t; };
template <> struct make_signed<int8x16_t> { using type = int8x16_t; };

template <> struct make_unsigned<int16x4_t> { using type = uint16x4_t; };
template <> struct make_unsigned<int16x8_t> { using type = uint16x8_t; };

template <> struct make_unsigned<uint16x4_t> { using type = uint16x4_t; };
template <> struct make_unsigned<uint16x8_t> { using type = uint16x8_t; };

template <> struct make_signed<uint16x4_t> { using type = int16x4_t; };
template <> struct make_signed<uint16x8_t> { using type = int16x8_t; };

template <> struct make_signed<int16x4_t> { using type = int16x4_t; };
template <> struct make_signed<int16x8_t> { using type = int16x8_t; };

template <> struct make_unsigned<int32x2_t> { using type = uint32x2_t; };
template <> struct make_unsigned<int32x4_t> { using type = uint32x4_t; };

template <> struct make_unsigned<uint32x2_t> { using type = uint32x2_t; };
template <> struct make_unsigned<uint32x4_t> { using type = uint32x4_t; };

template <> struct make_signed<uint32x2_t> { using type = int32x2_t; };
template <> struct make_signed<uint32x4_t> { using type = int32x4_t; };

template <> struct make_signed<int32x2_t> { using type = int32x2_t; };
template <> struct make_signed<int32x4_t> { using type = int32x4_t; };

template <> struct make_unsigned<int64x1_t> { using type = uint64x1_t; };
template <> struct make_unsigned<int64x2_t> { using type = uint64x2_t; };

template <> struct make_unsigned<uint64x1_t> { using type = uint64x1_t; };
template <> struct make_unsigned<uint64x2_t> { using type = uint64x2_t; };

template <> struct make_signed<uint64x1_t> { using type = int64x1_t; };
template <> struct make_signed<uint64x2_t> { using type = int64x2_t; };

template <> struct make_signed<int64x1_t> { using type = int64x1_t; };
template <> struct make_signed<int64x2_t> { using type = int64x2_t; };

template <> struct make_signed<float32x2_t> { using type = float32x2_t; };
template <> struct make_signed<float32x4_t> { using type = float32x4_t; };

template <typename T> struct NonVec;
template <> struct NonVec<int8x8_t> { using type = int8_t; };
template <> struct NonVec<uint8x8_t> { using type = uint8_t; };
template <> struct NonVec<int16x4_t> { using type = int16_t; };
template <> struct NonVec<uint16x4_t> { using type = uint16_t; };
template <> struct NonVec<int32x2_t> { using type = int32_t; };
template <> struct NonVec<uint32x2_t> { using type = uint32_t; };
template <> struct NonVec<int64x1_t> { using type = int64_t; };
template <> struct NonVec<uint64x1_t> { using type = uint64_t; };
template <> struct NonVec<float32x2_t> { using type = float; };

template <> struct NonVec<int8x16_t> { using type = int8_t; };
template <> struct NonVec<uint8x16_t> { using type = uint8_t; };
template <> struct NonVec<int16x8_t> { using type = int16_t; };
template <> struct NonVec<uint16x8_t> { using type = uint16_t; };
template <> struct NonVec<int32x4_t> { using type = int32_t; };
template <> struct NonVec<uint32x4_t> { using type = uint32_t; };
template <> struct NonVec<int64x2_t> { using type = int64_t; };
template <> struct NonVec<uint64x2_t> { using type = uint64_t; };
template <> struct NonVec<float32x4_t> { using type = float; };

template <typename type> struct Vec64 {};
template <typename type> struct Vec128 {};
template <> struct Vec64<int8_t> {using type = int8x8_t; };
template <> struct Vec128<int8_t>  {using type = int8x16_t; };

template <> struct Vec64<uint8_t> {using type = uint8x8_t; };
template <> struct Vec128<uint8_t>  {using type = uint8x16_t; };

template <> struct Vec64<int16_t> {using type = int16x4_t; };
template <> struct Vec128<int16_t>  {using type = int16x8_t; };

template <> struct Vec64<uint16_t> {using type = uint16x4_t; };
template <> struct Vec128<uint16_t>  {using type = uint16x8_t; };

template <> struct Vec64<int32_t> {using type = int32x2_t; };
template <> struct Vec128<int32_t>  {using type = int32x4_t; };

template <> struct Vec64<uint32_t> {using type = uint32x2_t; };
template <> struct Vec128<uint32_t>  {using type = uint32x4_t; };

template <> struct Vec64<int64_t> {using type = int64x1_t; };
template <> struct Vec128<int64_t>  {using type = int64x2_t; };

template <> struct Vec64<uint64_t> {using type = uint64x1_t; };
template <> struct Vec128<uint64_t>  {using type = uint64x2_t; };

template <> struct Vec64<float> {using type = float32x2_t; };
template <> struct Vec128<float>  {using type = float32x4_t; };

template <typename T>
constexpr bool is_doubleword_v =
    std::is_same_v<T, uint8x8_t> || std::is_same_v<T, uint16x4_t> || std::is_same_v<T, uint32x2_t> ||
    std::is_same_v<T, uint64x1_t> || std::is_same_v<T, int8x8_t> || std::is_same_v<T, int16x4_t> ||
    std::is_same_v<T, int32x2_t> || std::is_same_v<T, int64x1_t> || std::is_same_v<T, float32x2_t>;

template <typename T>
constexpr bool is_quadword_v =
    std::is_same_v<T, uint8x16_t> || std::is_same_v<T, uint16x8_t> || std::is_same_v<T, uint32x4_t> ||
    std::is_same_v<T, uint64x2_t> || std::is_same_v<T, int8x16_t> || std::is_same_v<T, int16x8_t> ||
    std::is_same_v<T, int32x4_t> || std::is_same_v<T, int64x2_t> || std::is_same_v<T, float32x4_t>;

template <typename T>
concept is_doubleword = is_doubleword_v<T>;

template <typename T>
concept is_quadword = is_quadword_v<T>;

template <typename T>
concept is_vector_type = is_doubleword<T> || is_quadword<T>;
// clang-format on

template <typename T>
nce auto get_lane(T vec, const int i);

template <>
nce auto get_lane(uint8x16_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get_lane<0>(vec);
    case 1:
      return neon::get_lane<1>(vec);
    case 2:
      return neon::get_lane<2>(vec);
    case 3:
      return neon::get_lane<3>(vec);
    case 4:
      return neon::get_lane<4>(vec);
    case 5:
      return neon::get_lane<5>(vec);
    case 6:
      return neon::get_lane<6>(vec);
    case 7:
      return neon::get_lane<7>(vec);
    case 8:
      return neon::get_lane<8>(vec);
    case 9:
      return neon::get_lane<9>(vec);
    case 10:
      return neon::get_lane<10>(vec);
    case 11:
      return neon::get_lane<11>(vec);
    case 12:
      return neon::get_lane<12>(vec);
    case 13:
      return neon::get_lane<13>(vec);
    case 14:
      return neon::get_lane<14>(vec);
    case 15:
      return neon::get_lane<15>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(int8x16_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get_lane<0>(vec);
    case 1:
      return neon::get_lane<1>(vec);
    case 2:
      return neon::get_lane<2>(vec);
    case 3:
      return neon::get_lane<3>(vec);
    case 4:
      return neon::get_lane<4>(vec);
    case 5:
      return neon::get_lane<5>(vec);
    case 6:
      return neon::get_lane<6>(vec);
    case 7:
      return neon::get_lane<7>(vec);
    case 8:
      return neon::get_lane<8>(vec);
    case 9:
      return neon::get_lane<9>(vec);
    case 10:
      return neon::get_lane<10>(vec);
    case 11:
      return neon::get_lane<11>(vec);
    case 12:
      return neon::get_lane<12>(vec);
    case 13:
      return neon::get_lane<13>(vec);
    case 14:
      return neon::get_lane<14>(vec);
    case 15:
      return neon::get_lane<15>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(uint8x8_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get_lane<0>(vec);
    case 1:
      return neon::get_lane<1>(vec);
    case 2:
      return neon::get_lane<2>(vec);
    case 3:
      return neon::get_lane<3>(vec);
    case 4:
      return neon::get_lane<4>(vec);
    case 5:
      return neon::get_lane<5>(vec);
    case 6:
      return neon::get_lane<6>(vec);
    case 7:
      return neon::get_lane<7>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(int8x8_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get_lane<0>(vec);
    case 1:
      return neon::get_lane<1>(vec);
    case 2:
      return neon::get_lane<2>(vec);
    case 3:
      return neon::get_lane<3>(vec);
    case 4:
      return neon::get_lane<4>(vec);
    case 5:
      return neon::get_lane<5>(vec);
    case 6:
      return neon::get_lane<6>(vec);
    case 7:
      return neon::get_lane<7>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(uint16x8_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get_lane<0>(vec);
    case 1:
      return neon::get_lane<1>(vec);
    case 2:
      return neon::get_lane<2>(vec);
    case 3:
      return neon::get_lane<3>(vec);
    case 4:
      return neon::get_lane<4>(vec);
    case 5:
      return neon::get_lane<5>(vec);
    case 6:
      return neon::get_lane<6>(vec);
    case 7:
      return neon::get_lane<7>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(int16x8_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get_lane<0>(vec);
    case 1:
      return neon::get_lane<1>(vec);
    case 2:
      return neon::get_lane<2>(vec);
    case 3:
      return neon::get_lane<3>(vec);
    case 4:
      return neon::get_lane<4>(vec);
    case 5:
      return neon::get_lane<5>(vec);
    case 6:
      return neon::get_lane<6>(vec);
    case 7:
      return neon::get_lane<7>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(uint16x4_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get_lane<0>(vec);
    case 1:
      return neon::get_lane<1>(vec);
    case 2:
      return neon::get_lane<2>(vec);
    case 3:
      return neon::get_lane<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(int16x4_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get_lane<0>(vec);
    case 1:
      return neon::get_lane<1>(vec);
    case 2:
      return neon::get_lane<2>(vec);
    case 3:
      return neon::get_lane<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(uint32x4_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get_lane<0>(vec);
    case 1:
      return neon::get_lane<1>(vec);
    case 2:
      return neon::get_lane<2>(vec);
    case 3:
      return neon::get_lane<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(int32x4_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get_lane<0>(vec);
    case 1:
      return neon::get_lane<1>(vec);
    case 2:
      return neon::get_lane<2>(vec);
    case 3:
      return neon::get_lane<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(float32x4_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get_lane<0>(vec);
    case 1:
      return neon::get_lane<1>(vec);
    case 2:
      return neon::get_lane<2>(vec);
    case 3:
      return neon::get_lane<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(uint32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get_lane<0>(vec);
    case 1:
      return neon::get_lane<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(int32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get_lane<0>(vec);
    case 1:
      return neon::get_lane<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(uint64x2_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get_lane<0>(vec);
    case 1:
      return neon::get_lane<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(int64x2_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get_lane<0>(vec);
    case 1:
      return neon::get_lane<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(float32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get_lane<0>(vec);
    case 1:
      return neon::get_lane<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(uint64x1_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get_lane<0>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(int64x1_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get_lane<0>(vec);
    default:
      __builtin_unreachable();
  }
}

template <typename T>
nce T set_lane(T vec, const int i, typename NonVec<T>::type a);

template <>
nce uint8x16_t set_lane(uint8x16_t vec, const int i, uint8_t a) {
  switch (i) {
    case 0:
      return neon::set_lane<0>(a, vec);
    case 1:
      return neon::set_lane<1>(a, vec);
    case 2:
      return neon::set_lane<2>(a, vec);
    case 3:
      return neon::set_lane<3>(a, vec);
    case 4:
      return neon::set_lane<4>(a, vec);
    case 5:
      return neon::set_lane<5>(a, vec);
    case 6:
      return neon::set_lane<6>(a, vec);
    case 7:
      return neon::set_lane<7>(a, vec);
    case 8:
      return neon::set_lane<8>(a, vec);
    case 9:
      return neon::set_lane<9>(a, vec);
    case 10:
      return neon::set_lane<10>(a, vec);
    case 11:
      return neon::set_lane<11>(a, vec);
    case 12:
      return neon::set_lane<12>(a, vec);
    case 13:
      return neon::set_lane<13>(a, vec);
    case 14:
      return neon::set_lane<14>(a, vec);
    case 15:
      return neon::set_lane<15>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int8x16_t set_lane(int8x16_t vec, const int i, int8_t a) {
  switch (i) {
    case 0:
      return neon::set_lane<0>(a, vec);
    case 1:
      return neon::set_lane<1>(a, vec);
    case 2:
      return neon::set_lane<2>(a, vec);
    case 3:
      return neon::set_lane<3>(a, vec);
    case 4:
      return neon::set_lane<4>(a, vec);
    case 5:
      return neon::set_lane<5>(a, vec);
    case 6:
      return neon::set_lane<6>(a, vec);
    case 7:
      return neon::set_lane<7>(a, vec);
    case 8:
      return neon::set_lane<8>(a, vec);
    case 9:
      return neon::set_lane<9>(a, vec);
    case 10:
      return neon::set_lane<10>(a, vec);
    case 11:
      return neon::set_lane<11>(a, vec);
    case 12:
      return neon::set_lane<12>(a, vec);
    case 13:
      return neon::set_lane<13>(a, vec);
    case 14:
      return neon::set_lane<14>(a, vec);
    case 15:
      return neon::set_lane<15>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint8x8_t set_lane(uint8x8_t vec, const int i, uint8_t a) {
  switch (i) {
    case 0:
      return neon::set_lane<0>(a, vec);
    case 1:
      return neon::set_lane<1>(a, vec);
    case 2:
      return neon::set_lane<2>(a, vec);
    case 3:
      return neon::set_lane<3>(a, vec);
    case 4:
      return neon::set_lane<4>(a, vec);
    case 5:
      return neon::set_lane<5>(a, vec);
    case 6:
      return neon::set_lane<6>(a, vec);
    case 7:
      return neon::set_lane<7>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int8x8_t set_lane(int8x8_t vec, const int i, int8_t a) {
  switch (i) {
    case 0:
      return neon::set_lane<0>(a, vec);
    case 1:
      return neon::set_lane<1>(a, vec);
    case 2:
      return neon::set_lane<2>(a, vec);
    case 3:
      return neon::set_lane<3>(a, vec);
    case 4:
      return neon::set_lane<4>(a, vec);
    case 5:
      return neon::set_lane<5>(a, vec);
    case 6:
      return neon::set_lane<6>(a, vec);
    case 7:
      return neon::set_lane<7>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint16x8_t set_lane(uint16x8_t vec, const int i, uint16_t a) {
  switch (i) {
    case 0:
      return neon::set_lane<0>(a, vec);
    case 1:
      return neon::set_lane<1>(a, vec);
    case 2:
      return neon::set_lane<2>(a, vec);
    case 3:
      return neon::set_lane<3>(a, vec);
    case 4:
      return neon::set_lane<4>(a, vec);
    case 5:
      return neon::set_lane<5>(a, vec);
    case 6:
      return neon::set_lane<6>(a, vec);
    case 7:
      return neon::set_lane<7>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int16x8_t set_lane(int16x8_t vec, const int i, int16_t a) {
  switch (i) {
    case 0:
      return neon::set_lane<0>(a, vec);
    case 1:
      return neon::set_lane<1>(a, vec);
    case 2:
      return neon::set_lane<2>(a, vec);
    case 3:
      return neon::set_lane<3>(a, vec);
    case 4:
      return neon::set_lane<4>(a, vec);
    case 5:
      return neon::set_lane<5>(a, vec);
    case 6:
      return neon::set_lane<6>(a, vec);
    case 7:
      return neon::set_lane<7>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint16x4_t set_lane(uint16x4_t vec, const int i, uint16_t a) {
  switch (i) {
    case 0:
      return neon::set_lane<0>(a, vec);
    case 1:
      return neon::set_lane<1>(a, vec);
    case 2:
      return neon::set_lane<2>(a, vec);
    case 3:
      return neon::set_lane<3>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int16x4_t set_lane(int16x4_t vec, const int i, int16_t a) {
  switch (i) {
    case 0:
      return neon::set_lane<0>(a, vec);
    case 1:
      return neon::set_lane<1>(a, vec);
    case 2:
      return neon::set_lane<2>(a, vec);
    case 3:
      return neon::set_lane<3>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint32x4_t set_lane(uint32x4_t vec, const int i, uint32_t a) {
  switch (i) {
    case 0:
      return neon::set_lane<0>(a, vec);
    case 1:
      return neon::set_lane<1>(a, vec);
    case 2:
      return neon::set_lane<2>(a, vec);
    case 3:
      return neon::set_lane<3>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int32x4_t set_lane(int32x4_t vec, const int i, int32_t a) {
  switch (i) {
    case 0:
      return neon::set_lane<0>(a, vec);
    case 1:
      return neon::set_lane<1>(a, vec);
    case 2:
      return neon::set_lane<2>(a, vec);
    case 3:
      return neon::set_lane<3>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce float32x4_t set_lane(float32x4_t vec, const int i, float32_t a) {
  switch (i) {
    case 0:
      return neon::set_lane<0>(a, vec);
    case 1:
      return neon::set_lane<1>(a, vec);
    case 2:
      return neon::set_lane<2>(a, vec);
    case 3:
      return neon::set_lane<3>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint32x2_t set_lane(uint32x2_t vec, const int i, uint32_t a) {
  switch (i) {
    case 0:
      return neon::set_lane<0>(a, vec);
    case 1:
      return neon::set_lane<1>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int32x2_t set_lane(int32x2_t vec, const int i, int32_t a) {
  switch (i) {
    case 0:
      return neon::set_lane<0>(a, vec);
    case 1:
      return neon::set_lane<1>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint64x2_t set_lane(uint64x2_t vec, const int i, uint64_t a) {
  switch (i) {
    case 0:
      return neon::set_lane<0>(a, vec);
    case 1:
      return neon::set_lane<1>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int64x2_t set_lane(int64x2_t vec, const int i, int64_t a) {
  switch (i) {
    case 0:
      return neon::set_lane<0>(a, vec);
    case 1:
      return neon::set_lane<1>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce float32x2_t set_lane(float32x2_t vec, const int i, float32_t a) {
  switch (i) {
    case 0:
      return neon::set_lane<0>(a, vec);
    case 1:
      return neon::set_lane<1>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint64x1_t set_lane(uint64x1_t vec, const int i, uint64_t a) {
  switch (i) {
    case 0:
      return neon::set_lane<0>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int64x1_t set_lane(int64x1_t vec, const int i, int64_t a) {
  switch (i) {
    case 0:
      return neon::set_lane<0>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <typename T>
nce T duplicate_lane(typename Vec64<typename NonVec<T>::type>::type vec, const int i);

template <>
nce uint8x8_t duplicate_lane(uint8x8_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::duplicate_lane<0>(vec);
    case 1:
      return neon::duplicate_lane<1>(vec);
    case 2:
      return neon::duplicate_lane<2>(vec);
    case 3:
      return neon::duplicate_lane<3>(vec);
    case 4:
      return neon::duplicate_lane<4>(vec);
    case 5:
      return neon::duplicate_lane<5>(vec);
    case 6:
      return neon::duplicate_lane<6>(vec);
    case 7:
      return neon::duplicate_lane<7>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint8x16_t duplicate_lane(uint8x8_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::duplicate_lane_quad<0>(vec);
    case 1:
      return neon::duplicate_lane_quad<1>(vec);
    case 2:
      return neon::duplicate_lane_quad<2>(vec);
    case 3:
      return neon::duplicate_lane_quad<3>(vec);
    case 4:
      return neon::duplicate_lane_quad<4>(vec);
    case 5:
      return neon::duplicate_lane_quad<5>(vec);
    case 6:
      return neon::duplicate_lane_quad<6>(vec);
    case 7:
      return neon::duplicate_lane_quad<7>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int8x8_t duplicate_lane(int8x8_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::duplicate_lane<0>(vec);
    case 1:
      return neon::duplicate_lane<1>(vec);
    case 2:
      return neon::duplicate_lane<2>(vec);
    case 3:
      return neon::duplicate_lane<3>(vec);
    case 4:
      return neon::duplicate_lane<4>(vec);
    case 5:
      return neon::duplicate_lane<5>(vec);
    case 6:
      return neon::duplicate_lane<6>(vec);
    case 7:
      return neon::duplicate_lane<7>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int8x16_t duplicate_lane(int8x8_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::duplicate_lane_quad<0>(vec);
    case 1:
      return neon::duplicate_lane_quad<1>(vec);
    case 2:
      return neon::duplicate_lane_quad<2>(vec);
    case 3:
      return neon::duplicate_lane_quad<3>(vec);
    case 4:
      return neon::duplicate_lane_quad<4>(vec);
    case 5:
      return neon::duplicate_lane_quad<5>(vec);
    case 6:
      return neon::duplicate_lane_quad<6>(vec);
    case 7:
      return neon::duplicate_lane_quad<7>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint16x4_t duplicate_lane(uint16x4_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::duplicate_lane<0>(vec);
    case 1:
      return neon::duplicate_lane<1>(vec);
    case 2:
      return neon::duplicate_lane<2>(vec);
    case 3:
      return neon::duplicate_lane<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint16x8_t duplicate_lane(uint16x4_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::duplicate_lane_quad<0>(vec);
    case 1:
      return neon::duplicate_lane_quad<1>(vec);
    case 2:
      return neon::duplicate_lane_quad<2>(vec);
    case 3:
      return neon::duplicate_lane_quad<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int16x4_t duplicate_lane(int16x4_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::duplicate_lane<0>(vec);
    case 1:
      return neon::duplicate_lane<1>(vec);
    case 2:
      return neon::duplicate_lane<2>(vec);
    case 3:
      return neon::duplicate_lane<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int16x8_t duplicate_lane(int16x4_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::duplicate_lane_quad<0>(vec);
    case 1:
      return neon::duplicate_lane_quad<1>(vec);
    case 2:
      return neon::duplicate_lane_quad<2>(vec);
    case 3:
      return neon::duplicate_lane_quad<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint32x2_t duplicate_lane(uint32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::duplicate_lane<0>(vec);
    case 1:
      return neon::duplicate_lane<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint32x4_t duplicate_lane(uint32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::duplicate_lane_quad<0>(vec);
    case 1:
      return neon::duplicate_lane_quad<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int32x2_t duplicate_lane(int32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::duplicate_lane<0>(vec);
    case 1:
      return neon::duplicate_lane<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int32x4_t duplicate_lane(int32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::duplicate_lane_quad<0>(vec);
    case 1:
      return neon::duplicate_lane_quad<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint64x2_t duplicate_lane(uint64x1_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::duplicate_lane_quad<0>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce float32x2_t duplicate_lane(float32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::duplicate_lane<0>(vec);
    case 1:
      return neon::duplicate_lane<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce float32x4_t duplicate_lane(float32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::duplicate_lane_quad<0>(vec);
    case 1:
      return neon::duplicate_lane_quad<1>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_right(uint64x2_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    case 8:
      return shift_right<8>(vec);
    case 9:
      return shift_right<9>(vec);
    case 10:
      return shift_right<10>(vec);
    case 11:
      return shift_right<11>(vec);
    case 12:
      return shift_right<12>(vec);
    case 13:
      return shift_right<13>(vec);
    case 14:
      return shift_right<14>(vec);
    case 15:
      return shift_right<15>(vec);
    case 16:
      return shift_right<16>(vec);
    case 17:
      return shift_right<17>(vec);
    case 18:
      return shift_right<18>(vec);
    case 19:
      return shift_right<19>(vec);
    case 20:
      return shift_right<20>(vec);
    case 21:
      return shift_right<21>(vec);
    case 22:
      return shift_right<22>(vec);
    case 23:
      return shift_right<23>(vec);
    case 24:
      return shift_right<24>(vec);
    case 25:
      return shift_right<25>(vec);
    case 26:
      return shift_right<26>(vec);
    case 27:
      return shift_right<27>(vec);
    case 28:
      return shift_right<28>(vec);
    case 29:
      return shift_right<29>(vec);
    case 30:
      return shift_right<30>(vec);
    case 31:
      return shift_right<31>(vec);
    case 32:
      return shift_right<32>(vec);
    case 33:
      return shift_right<33>(vec);
    case 34:
      return shift_right<34>(vec);
    case 35:
      return shift_right<35>(vec);
    case 36:
      return shift_right<36>(vec);
    case 37:
      return shift_right<37>(vec);
    case 38:
      return shift_right<38>(vec);
    case 39:
      return shift_right<39>(vec);
    case 40:
      return shift_right<40>(vec);
    case 41:
      return shift_right<41>(vec);
    case 42:
      return shift_right<42>(vec);
    case 43:
      return shift_right<43>(vec);
    case 44:
      return shift_right<44>(vec);
    case 45:
      return shift_right<45>(vec);
    case 46:
      return shift_right<46>(vec);
    case 47:
      return shift_right<47>(vec);
    case 48:
      return shift_right<48>(vec);
    case 49:
      return shift_right<49>(vec);
    case 50:
      return shift_right<50>(vec);
    case 51:
      return shift_right<51>(vec);
    case 52:
      return shift_right<52>(vec);
    case 53:
      return shift_right<53>(vec);
    case 54:
      return shift_right<54>(vec);
    case 55:
      return shift_right<55>(vec);
    case 56:
      return shift_right<56>(vec);
    case 57:
      return shift_right<57>(vec);
    case 58:
      return shift_right<58>(vec);
    case 59:
      return shift_right<59>(vec);
    case 60:
      return shift_right<60>(vec);
    case 61:
      return shift_right<61>(vec);
    case 62:
      return shift_right<62>(vec);
    case 63:
      return shift_right<63>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_right(uint64x1_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    case 8:
      return shift_right<8>(vec);
    case 9:
      return shift_right<9>(vec);
    case 10:
      return shift_right<10>(vec);
    case 11:
      return shift_right<11>(vec);
    case 12:
      return shift_right<12>(vec);
    case 13:
      return shift_right<13>(vec);
    case 14:
      return shift_right<14>(vec);
    case 15:
      return shift_right<15>(vec);
    case 16:
      return shift_right<16>(vec);
    case 17:
      return shift_right<17>(vec);
    case 18:
      return shift_right<18>(vec);
    case 19:
      return shift_right<19>(vec);
    case 20:
      return shift_right<20>(vec);
    case 21:
      return shift_right<21>(vec);
    case 22:
      return shift_right<22>(vec);
    case 23:
      return shift_right<23>(vec);
    case 24:
      return shift_right<24>(vec);
    case 25:
      return shift_right<25>(vec);
    case 26:
      return shift_right<26>(vec);
    case 27:
      return shift_right<27>(vec);
    case 28:
      return shift_right<28>(vec);
    case 29:
      return shift_right<29>(vec);
    case 30:
      return shift_right<30>(vec);
    case 31:
      return shift_right<31>(vec);
    case 32:
      return shift_right<32>(vec);
    case 33:
      return shift_right<33>(vec);
    case 34:
      return shift_right<34>(vec);
    case 35:
      return shift_right<35>(vec);
    case 36:
      return shift_right<36>(vec);
    case 37:
      return shift_right<37>(vec);
    case 38:
      return shift_right<38>(vec);
    case 39:
      return shift_right<39>(vec);
    case 40:
      return shift_right<40>(vec);
    case 41:
      return shift_right<41>(vec);
    case 42:
      return shift_right<42>(vec);
    case 43:
      return shift_right<43>(vec);
    case 44:
      return shift_right<44>(vec);
    case 45:
      return shift_right<45>(vec);
    case 46:
      return shift_right<46>(vec);
    case 47:
      return shift_right<47>(vec);
    case 48:
      return shift_right<48>(vec);
    case 49:
      return shift_right<49>(vec);
    case 50:
      return shift_right<50>(vec);
    case 51:
      return shift_right<51>(vec);
    case 52:
      return shift_right<52>(vec);
    case 53:
      return shift_right<53>(vec);
    case 54:
      return shift_right<54>(vec);
    case 55:
      return shift_right<55>(vec);
    case 56:
      return shift_right<56>(vec);
    case 57:
      return shift_right<57>(vec);
    case 58:
      return shift_right<58>(vec);
    case 59:
      return shift_right<59>(vec);
    case 60:
      return shift_right<60>(vec);
    case 61:
      return shift_right<61>(vec);
    case 62:
      return shift_right<62>(vec);
    case 63:
      return shift_right<63>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_right(uint32x4_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    case 8:
      return shift_right<8>(vec);
    case 9:
      return shift_right<9>(vec);
    case 10:
      return shift_right<10>(vec);
    case 11:
      return shift_right<11>(vec);
    case 12:
      return shift_right<12>(vec);
    case 13:
      return shift_right<13>(vec);
    case 14:
      return shift_right<14>(vec);
    case 15:
      return shift_right<15>(vec);
    case 16:
      return shift_right<16>(vec);
    case 17:
      return shift_right<17>(vec);
    case 18:
      return shift_right<18>(vec);
    case 19:
      return shift_right<19>(vec);
    case 20:
      return shift_right<20>(vec);
    case 21:
      return shift_right<21>(vec);
    case 22:
      return shift_right<22>(vec);
    case 23:
      return shift_right<23>(vec);
    case 24:
      return shift_right<24>(vec);
    case 25:
      return shift_right<25>(vec);
    case 26:
      return shift_right<26>(vec);
    case 27:
      return shift_right<27>(vec);
    case 28:
      return shift_right<28>(vec);
    case 29:
      return shift_right<29>(vec);
    case 30:
      return shift_right<30>(vec);
    case 31:
      return shift_right<31>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_right(uint32x2_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    case 8:
      return shift_right<8>(vec);
    case 9:
      return shift_right<9>(vec);
    case 10:
      return shift_right<10>(vec);
    case 11:
      return shift_right<11>(vec);
    case 12:
      return shift_right<12>(vec);
    case 13:
      return shift_right<13>(vec);
    case 14:
      return shift_right<14>(vec);
    case 15:
      return shift_right<15>(vec);
    case 16:
      return shift_right<16>(vec);
    case 17:
      return shift_right<17>(vec);
    case 18:
      return shift_right<18>(vec);
    case 19:
      return shift_right<19>(vec);
    case 20:
      return shift_right<20>(vec);
    case 21:
      return shift_right<21>(vec);
    case 22:
      return shift_right<22>(vec);
    case 23:
      return shift_right<23>(vec);
    case 24:
      return shift_right<24>(vec);
    case 25:
      return shift_right<25>(vec);
    case 26:
      return shift_right<26>(vec);
    case 27:
      return shift_right<27>(vec);
    case 28:
      return shift_right<28>(vec);
    case 29:
      return shift_right<29>(vec);
    case 30:
      return shift_right<30>(vec);
    case 31:
      return shift_right<31>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_right(uint16x8_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    case 8:
      return shift_right<8>(vec);
    case 9:
      return shift_right<9>(vec);
    case 10:
      return shift_right<10>(vec);
    case 11:
      return shift_right<11>(vec);
    case 12:
      return shift_right<12>(vec);
    case 13:
      return shift_right<13>(vec);
    case 14:
      return shift_right<14>(vec);
    case 15:
      return shift_right<15>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_right(uint16x4_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    case 8:
      return shift_right<8>(vec);
    case 9:
      return shift_right<9>(vec);
    case 10:
      return shift_right<10>(vec);
    case 11:
      return shift_right<11>(vec);
    case 12:
      return shift_right<12>(vec);
    case 13:
      return shift_right<13>(vec);
    case 14:
      return shift_right<14>(vec);
    case 15:
      return shift_right<15>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_right(uint8x16_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_right(uint8x8_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_left(uint64x2_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    case 8:
      return shift_left<8>(vec);
    case 9:
      return shift_left<9>(vec);
    case 10:
      return shift_left<10>(vec);
    case 11:
      return shift_left<11>(vec);
    case 12:
      return shift_left<12>(vec);
    case 13:
      return shift_left<13>(vec);
    case 14:
      return shift_left<14>(vec);
    case 15:
      return shift_left<15>(vec);
    case 16:
      return shift_left<16>(vec);
    case 17:
      return shift_left<17>(vec);
    case 18:
      return shift_left<18>(vec);
    case 19:
      return shift_left<19>(vec);
    case 20:
      return shift_left<20>(vec);
    case 21:
      return shift_left<21>(vec);
    case 22:
      return shift_left<22>(vec);
    case 23:
      return shift_left<23>(vec);
    case 24:
      return shift_left<24>(vec);
    case 25:
      return shift_left<25>(vec);
    case 26:
      return shift_left<26>(vec);
    case 27:
      return shift_left<27>(vec);
    case 28:
      return shift_left<28>(vec);
    case 29:
      return shift_left<29>(vec);
    case 30:
      return shift_left<30>(vec);
    case 31:
      return shift_left<31>(vec);
    case 32:
      return shift_left<32>(vec);
    case 33:
      return shift_left<33>(vec);
    case 34:
      return shift_left<34>(vec);
    case 35:
      return shift_left<35>(vec);
    case 36:
      return shift_left<36>(vec);
    case 37:
      return shift_left<37>(vec);
    case 38:
      return shift_left<38>(vec);
    case 39:
      return shift_left<39>(vec);
    case 40:
      return shift_left<40>(vec);
    case 41:
      return shift_left<41>(vec);
    case 42:
      return shift_left<42>(vec);
    case 43:
      return shift_left<43>(vec);
    case 44:
      return shift_left<44>(vec);
    case 45:
      return shift_left<45>(vec);
    case 46:
      return shift_left<46>(vec);
    case 47:
      return shift_left<47>(vec);
    case 48:
      return shift_left<48>(vec);
    case 49:
      return shift_left<49>(vec);
    case 50:
      return shift_left<50>(vec);
    case 51:
      return shift_left<51>(vec);
    case 52:
      return shift_left<52>(vec);
    case 53:
      return shift_left<53>(vec);
    case 54:
      return shift_left<54>(vec);
    case 55:
      return shift_left<55>(vec);
    case 56:
      return shift_left<56>(vec);
    case 57:
      return shift_left<57>(vec);
    case 58:
      return shift_left<58>(vec);
    case 59:
      return shift_left<59>(vec);
    case 60:
      return shift_left<60>(vec);
    case 61:
      return shift_left<61>(vec);
    case 62:
      return shift_left<62>(vec);
    case 63:
      return shift_left<63>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_left(uint64x1_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    case 8:
      return shift_left<8>(vec);
    case 9:
      return shift_left<9>(vec);
    case 10:
      return shift_left<10>(vec);
    case 11:
      return shift_left<11>(vec);
    case 12:
      return shift_left<12>(vec);
    case 13:
      return shift_left<13>(vec);
    case 14:
      return shift_left<14>(vec);
    case 15:
      return shift_left<15>(vec);
    case 16:
      return shift_left<16>(vec);
    case 17:
      return shift_left<17>(vec);
    case 18:
      return shift_left<18>(vec);
    case 19:
      return shift_left<19>(vec);
    case 20:
      return shift_left<20>(vec);
    case 21:
      return shift_left<21>(vec);
    case 22:
      return shift_left<22>(vec);
    case 23:
      return shift_left<23>(vec);
    case 24:
      return shift_left<24>(vec);
    case 25:
      return shift_left<25>(vec);
    case 26:
      return shift_left<26>(vec);
    case 27:
      return shift_left<27>(vec);
    case 28:
      return shift_left<28>(vec);
    case 29:
      return shift_left<29>(vec);
    case 30:
      return shift_left<30>(vec);
    case 31:
      return shift_left<31>(vec);
    case 32:
      return shift_left<32>(vec);
    case 33:
      return shift_left<33>(vec);
    case 34:
      return shift_left<34>(vec);
    case 35:
      return shift_left<35>(vec);
    case 36:
      return shift_left<36>(vec);
    case 37:
      return shift_left<37>(vec);
    case 38:
      return shift_left<38>(vec);
    case 39:
      return shift_left<39>(vec);
    case 40:
      return shift_left<40>(vec);
    case 41:
      return shift_left<41>(vec);
    case 42:
      return shift_left<42>(vec);
    case 43:
      return shift_left<43>(vec);
    case 44:
      return shift_left<44>(vec);
    case 45:
      return shift_left<45>(vec);
    case 46:
      return shift_left<46>(vec);
    case 47:
      return shift_left<47>(vec);
    case 48:
      return shift_left<48>(vec);
    case 49:
      return shift_left<49>(vec);
    case 50:
      return shift_left<50>(vec);
    case 51:
      return shift_left<51>(vec);
    case 52:
      return shift_left<52>(vec);
    case 53:
      return shift_left<53>(vec);
    case 54:
      return shift_left<54>(vec);
    case 55:
      return shift_left<55>(vec);
    case 56:
      return shift_left<56>(vec);
    case 57:
      return shift_left<57>(vec);
    case 58:
      return shift_left<58>(vec);
    case 59:
      return shift_left<59>(vec);
    case 60:
      return shift_left<60>(vec);
    case 61:
      return shift_left<61>(vec);
    case 62:
      return shift_left<62>(vec);
    case 63:
      return shift_left<63>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_left(uint32x4_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    case 8:
      return shift_left<8>(vec);
    case 9:
      return shift_left<9>(vec);
    case 10:
      return shift_left<10>(vec);
    case 11:
      return shift_left<11>(vec);
    case 12:
      return shift_left<12>(vec);
    case 13:
      return shift_left<13>(vec);
    case 14:
      return shift_left<14>(vec);
    case 15:
      return shift_left<15>(vec);
    case 16:
      return shift_left<16>(vec);
    case 17:
      return shift_left<17>(vec);
    case 18:
      return shift_left<18>(vec);
    case 19:
      return shift_left<19>(vec);
    case 20:
      return shift_left<20>(vec);
    case 21:
      return shift_left<21>(vec);
    case 22:
      return shift_left<22>(vec);
    case 23:
      return shift_left<23>(vec);
    case 24:
      return shift_left<24>(vec);
    case 25:
      return shift_left<25>(vec);
    case 26:
      return shift_left<26>(vec);
    case 27:
      return shift_left<27>(vec);
    case 28:
      return shift_left<28>(vec);
    case 29:
      return shift_left<29>(vec);
    case 30:
      return shift_left<30>(vec);
    case 31:
      return shift_left<31>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_left(uint32x2_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    case 8:
      return shift_left<8>(vec);
    case 9:
      return shift_left<9>(vec);
    case 10:
      return shift_left<10>(vec);
    case 11:
      return shift_left<11>(vec);
    case 12:
      return shift_left<12>(vec);
    case 13:
      return shift_left<13>(vec);
    case 14:
      return shift_left<14>(vec);
    case 15:
      return shift_left<15>(vec);
    case 16:
      return shift_left<16>(vec);
    case 17:
      return shift_left<17>(vec);
    case 18:
      return shift_left<18>(vec);
    case 19:
      return shift_left<19>(vec);
    case 20:
      return shift_left<20>(vec);
    case 21:
      return shift_left<21>(vec);
    case 22:
      return shift_left<22>(vec);
    case 23:
      return shift_left<23>(vec);
    case 24:
      return shift_left<24>(vec);
    case 25:
      return shift_left<25>(vec);
    case 26:
      return shift_left<26>(vec);
    case 27:
      return shift_left<27>(vec);
    case 28:
      return shift_left<28>(vec);
    case 29:
      return shift_left<29>(vec);
    case 30:
      return shift_left<30>(vec);
    case 31:
      return shift_left<31>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_left(uint16x8_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    case 8:
      return shift_left<8>(vec);
    case 9:
      return shift_left<9>(vec);
    case 10:
      return shift_left<10>(vec);
    case 11:
      return shift_left<11>(vec);
    case 12:
      return shift_left<12>(vec);
    case 13:
      return shift_left<13>(vec);
    case 14:
      return shift_left<14>(vec);
    case 15:
      return shift_left<15>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_left(uint16x4_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    case 8:
      return shift_left<8>(vec);
    case 9:
      return shift_left<9>(vec);
    case 10:
      return shift_left<10>(vec);
    case 11:
      return shift_left<11>(vec);
    case 12:
      return shift_left<12>(vec);
    case 13:
      return shift_left<13>(vec);
    case 14:
      return shift_left<14>(vec);
    case 15:
      return shift_left<15>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_left(uint8x16_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_left(uint8x8_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_right(int64x2_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    case 8:
      return shift_right<8>(vec);
    case 9:
      return shift_right<9>(vec);
    case 10:
      return shift_right<10>(vec);
    case 11:
      return shift_right<11>(vec);
    case 12:
      return shift_right<12>(vec);
    case 13:
      return shift_right<13>(vec);
    case 14:
      return shift_right<14>(vec);
    case 15:
      return shift_right<15>(vec);
    case 16:
      return shift_right<16>(vec);
    case 17:
      return shift_right<17>(vec);
    case 18:
      return shift_right<18>(vec);
    case 19:
      return shift_right<19>(vec);
    case 20:
      return shift_right<20>(vec);
    case 21:
      return shift_right<21>(vec);
    case 22:
      return shift_right<22>(vec);
    case 23:
      return shift_right<23>(vec);
    case 24:
      return shift_right<24>(vec);
    case 25:
      return shift_right<25>(vec);
    case 26:
      return shift_right<26>(vec);
    case 27:
      return shift_right<27>(vec);
    case 28:
      return shift_right<28>(vec);
    case 29:
      return shift_right<29>(vec);
    case 30:
      return shift_right<30>(vec);
    case 31:
      return shift_right<31>(vec);
    case 32:
      return shift_right<32>(vec);
    case 33:
      return shift_right<33>(vec);
    case 34:
      return shift_right<34>(vec);
    case 35:
      return shift_right<35>(vec);
    case 36:
      return shift_right<36>(vec);
    case 37:
      return shift_right<37>(vec);
    case 38:
      return shift_right<38>(vec);
    case 39:
      return shift_right<39>(vec);
    case 40:
      return shift_right<40>(vec);
    case 41:
      return shift_right<41>(vec);
    case 42:
      return shift_right<42>(vec);
    case 43:
      return shift_right<43>(vec);
    case 44:
      return shift_right<44>(vec);
    case 45:
      return shift_right<45>(vec);
    case 46:
      return shift_right<46>(vec);
    case 47:
      return shift_right<47>(vec);
    case 48:
      return shift_right<48>(vec);
    case 49:
      return shift_right<49>(vec);
    case 50:
      return shift_right<50>(vec);
    case 51:
      return shift_right<51>(vec);
    case 52:
      return shift_right<52>(vec);
    case 53:
      return shift_right<53>(vec);
    case 54:
      return shift_right<54>(vec);
    case 55:
      return shift_right<55>(vec);
    case 56:
      return shift_right<56>(vec);
    case 57:
      return shift_right<57>(vec);
    case 58:
      return shift_right<58>(vec);
    case 59:
      return shift_right<59>(vec);
    case 60:
      return shift_right<60>(vec);
    case 61:
      return shift_right<61>(vec);
    case 62:
      return shift_right<62>(vec);
    case 63:
      return shift_right<63>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_right(int64x1_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    case 8:
      return shift_right<8>(vec);
    case 9:
      return shift_right<9>(vec);
    case 10:
      return shift_right<10>(vec);
    case 11:
      return shift_right<11>(vec);
    case 12:
      return shift_right<12>(vec);
    case 13:
      return shift_right<13>(vec);
    case 14:
      return shift_right<14>(vec);
    case 15:
      return shift_right<15>(vec);
    case 16:
      return shift_right<16>(vec);
    case 17:
      return shift_right<17>(vec);
    case 18:
      return shift_right<18>(vec);
    case 19:
      return shift_right<19>(vec);
    case 20:
      return shift_right<20>(vec);
    case 21:
      return shift_right<21>(vec);
    case 22:
      return shift_right<22>(vec);
    case 23:
      return shift_right<23>(vec);
    case 24:
      return shift_right<24>(vec);
    case 25:
      return shift_right<25>(vec);
    case 26:
      return shift_right<26>(vec);
    case 27:
      return shift_right<27>(vec);
    case 28:
      return shift_right<28>(vec);
    case 29:
      return shift_right<29>(vec);
    case 30:
      return shift_right<30>(vec);
    case 31:
      return shift_right<31>(vec);
    case 32:
      return shift_right<32>(vec);
    case 33:
      return shift_right<33>(vec);
    case 34:
      return shift_right<34>(vec);
    case 35:
      return shift_right<35>(vec);
    case 36:
      return shift_right<36>(vec);
    case 37:
      return shift_right<37>(vec);
    case 38:
      return shift_right<38>(vec);
    case 39:
      return shift_right<39>(vec);
    case 40:
      return shift_right<40>(vec);
    case 41:
      return shift_right<41>(vec);
    case 42:
      return shift_right<42>(vec);
    case 43:
      return shift_right<43>(vec);
    case 44:
      return shift_right<44>(vec);
    case 45:
      return shift_right<45>(vec);
    case 46:
      return shift_right<46>(vec);
    case 47:
      return shift_right<47>(vec);
    case 48:
      return shift_right<48>(vec);
    case 49:
      return shift_right<49>(vec);
    case 50:
      return shift_right<50>(vec);
    case 51:
      return shift_right<51>(vec);
    case 52:
      return shift_right<52>(vec);
    case 53:
      return shift_right<53>(vec);
    case 54:
      return shift_right<54>(vec);
    case 55:
      return shift_right<55>(vec);
    case 56:
      return shift_right<56>(vec);
    case 57:
      return shift_right<57>(vec);
    case 58:
      return shift_right<58>(vec);
    case 59:
      return shift_right<59>(vec);
    case 60:
      return shift_right<60>(vec);
    case 61:
      return shift_right<61>(vec);
    case 62:
      return shift_right<62>(vec);
    case 63:
      return shift_right<63>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_right(int32x4_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    case 8:
      return shift_right<8>(vec);
    case 9:
      return shift_right<9>(vec);
    case 10:
      return shift_right<10>(vec);
    case 11:
      return shift_right<11>(vec);
    case 12:
      return shift_right<12>(vec);
    case 13:
      return shift_right<13>(vec);
    case 14:
      return shift_right<14>(vec);
    case 15:
      return shift_right<15>(vec);
    case 16:
      return shift_right<16>(vec);
    case 17:
      return shift_right<17>(vec);
    case 18:
      return shift_right<18>(vec);
    case 19:
      return shift_right<19>(vec);
    case 20:
      return shift_right<20>(vec);
    case 21:
      return shift_right<21>(vec);
    case 22:
      return shift_right<22>(vec);
    case 23:
      return shift_right<23>(vec);
    case 24:
      return shift_right<24>(vec);
    case 25:
      return shift_right<25>(vec);
    case 26:
      return shift_right<26>(vec);
    case 27:
      return shift_right<27>(vec);
    case 28:
      return shift_right<28>(vec);
    case 29:
      return shift_right<29>(vec);
    case 30:
      return shift_right<30>(vec);
    case 31:
      return shift_right<31>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_right(int32x2_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    case 8:
      return shift_right<8>(vec);
    case 9:
      return shift_right<9>(vec);
    case 10:
      return shift_right<10>(vec);
    case 11:
      return shift_right<11>(vec);
    case 12:
      return shift_right<12>(vec);
    case 13:
      return shift_right<13>(vec);
    case 14:
      return shift_right<14>(vec);
    case 15:
      return shift_right<15>(vec);
    case 16:
      return shift_right<16>(vec);
    case 17:
      return shift_right<17>(vec);
    case 18:
      return shift_right<18>(vec);
    case 19:
      return shift_right<19>(vec);
    case 20:
      return shift_right<20>(vec);
    case 21:
      return shift_right<21>(vec);
    case 22:
      return shift_right<22>(vec);
    case 23:
      return shift_right<23>(vec);
    case 24:
      return shift_right<24>(vec);
    case 25:
      return shift_right<25>(vec);
    case 26:
      return shift_right<26>(vec);
    case 27:
      return shift_right<27>(vec);
    case 28:
      return shift_right<28>(vec);
    case 29:
      return shift_right<29>(vec);
    case 30:
      return shift_right<30>(vec);
    case 31:
      return shift_right<31>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_right(int16x8_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    case 8:
      return shift_right<8>(vec);
    case 9:
      return shift_right<9>(vec);
    case 10:
      return shift_right<10>(vec);
    case 11:
      return shift_right<11>(vec);
    case 12:
      return shift_right<12>(vec);
    case 13:
      return shift_right<13>(vec);
    case 14:
      return shift_right<14>(vec);
    case 15:
      return shift_right<15>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_right(int16x4_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    case 8:
      return shift_right<8>(vec);
    case 9:
      return shift_right<9>(vec);
    case 10:
      return shift_right<10>(vec);
    case 11:
      return shift_right<11>(vec);
    case 12:
      return shift_right<12>(vec);
    case 13:
      return shift_right<13>(vec);
    case 14:
      return shift_right<14>(vec);
    case 15:
      return shift_right<15>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_right(int8x16_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_right(int8x8_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_left(int64x2_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    case 8:
      return shift_left<8>(vec);
    case 9:
      return shift_left<9>(vec);
    case 10:
      return shift_left<10>(vec);
    case 11:
      return shift_left<11>(vec);
    case 12:
      return shift_left<12>(vec);
    case 13:
      return shift_left<13>(vec);
    case 14:
      return shift_left<14>(vec);
    case 15:
      return shift_left<15>(vec);
    case 16:
      return shift_left<16>(vec);
    case 17:
      return shift_left<17>(vec);
    case 18:
      return shift_left<18>(vec);
    case 19:
      return shift_left<19>(vec);
    case 20:
      return shift_left<20>(vec);
    case 21:
      return shift_left<21>(vec);
    case 22:
      return shift_left<22>(vec);
    case 23:
      return shift_left<23>(vec);
    case 24:
      return shift_left<24>(vec);
    case 25:
      return shift_left<25>(vec);
    case 26:
      return shift_left<26>(vec);
    case 27:
      return shift_left<27>(vec);
    case 28:
      return shift_left<28>(vec);
    case 29:
      return shift_left<29>(vec);
    case 30:
      return shift_left<30>(vec);
    case 31:
      return shift_left<31>(vec);
    case 32:
      return shift_left<32>(vec);
    case 33:
      return shift_left<33>(vec);
    case 34:
      return shift_left<34>(vec);
    case 35:
      return shift_left<35>(vec);
    case 36:
      return shift_left<36>(vec);
    case 37:
      return shift_left<37>(vec);
    case 38:
      return shift_left<38>(vec);
    case 39:
      return shift_left<39>(vec);
    case 40:
      return shift_left<40>(vec);
    case 41:
      return shift_left<41>(vec);
    case 42:
      return shift_left<42>(vec);
    case 43:
      return shift_left<43>(vec);
    case 44:
      return shift_left<44>(vec);
    case 45:
      return shift_left<45>(vec);
    case 46:
      return shift_left<46>(vec);
    case 47:
      return shift_left<47>(vec);
    case 48:
      return shift_left<48>(vec);
    case 49:
      return shift_left<49>(vec);
    case 50:
      return shift_left<50>(vec);
    case 51:
      return shift_left<51>(vec);
    case 52:
      return shift_left<52>(vec);
    case 53:
      return shift_left<53>(vec);
    case 54:
      return shift_left<54>(vec);
    case 55:
      return shift_left<55>(vec);
    case 56:
      return shift_left<56>(vec);
    case 57:
      return shift_left<57>(vec);
    case 58:
      return shift_left<58>(vec);
    case 59:
      return shift_left<59>(vec);
    case 60:
      return shift_left<60>(vec);
    case 61:
      return shift_left<61>(vec);
    case 62:
      return shift_left<62>(vec);
    case 63:
      return shift_left<63>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_left(int64x1_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    case 8:
      return shift_left<8>(vec);
    case 9:
      return shift_left<9>(vec);
    case 10:
      return shift_left<10>(vec);
    case 11:
      return shift_left<11>(vec);
    case 12:
      return shift_left<12>(vec);
    case 13:
      return shift_left<13>(vec);
    case 14:
      return shift_left<14>(vec);
    case 15:
      return shift_left<15>(vec);
    case 16:
      return shift_left<16>(vec);
    case 17:
      return shift_left<17>(vec);
    case 18:
      return shift_left<18>(vec);
    case 19:
      return shift_left<19>(vec);
    case 20:
      return shift_left<20>(vec);
    case 21:
      return shift_left<21>(vec);
    case 22:
      return shift_left<22>(vec);
    case 23:
      return shift_left<23>(vec);
    case 24:
      return shift_left<24>(vec);
    case 25:
      return shift_left<25>(vec);
    case 26:
      return shift_left<26>(vec);
    case 27:
      return shift_left<27>(vec);
    case 28:
      return shift_left<28>(vec);
    case 29:
      return shift_left<29>(vec);
    case 30:
      return shift_left<30>(vec);
    case 31:
      return shift_left<31>(vec);
    case 32:
      return shift_left<32>(vec);
    case 33:
      return shift_left<33>(vec);
    case 34:
      return shift_left<34>(vec);
    case 35:
      return shift_left<35>(vec);
    case 36:
      return shift_left<36>(vec);
    case 37:
      return shift_left<37>(vec);
    case 38:
      return shift_left<38>(vec);
    case 39:
      return shift_left<39>(vec);
    case 40:
      return shift_left<40>(vec);
    case 41:
      return shift_left<41>(vec);
    case 42:
      return shift_left<42>(vec);
    case 43:
      return shift_left<43>(vec);
    case 44:
      return shift_left<44>(vec);
    case 45:
      return shift_left<45>(vec);
    case 46:
      return shift_left<46>(vec);
    case 47:
      return shift_left<47>(vec);
    case 48:
      return shift_left<48>(vec);
    case 49:
      return shift_left<49>(vec);
    case 50:
      return shift_left<50>(vec);
    case 51:
      return shift_left<51>(vec);
    case 52:
      return shift_left<52>(vec);
    case 53:
      return shift_left<53>(vec);
    case 54:
      return shift_left<54>(vec);
    case 55:
      return shift_left<55>(vec);
    case 56:
      return shift_left<56>(vec);
    case 57:
      return shift_left<57>(vec);
    case 58:
      return shift_left<58>(vec);
    case 59:
      return shift_left<59>(vec);
    case 60:
      return shift_left<60>(vec);
    case 61:
      return shift_left<61>(vec);
    case 62:
      return shift_left<62>(vec);
    case 63:
      return shift_left<63>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_left(int32x4_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    case 8:
      return shift_left<8>(vec);
    case 9:
      return shift_left<9>(vec);
    case 10:
      return shift_left<10>(vec);
    case 11:
      return shift_left<11>(vec);
    case 12:
      return shift_left<12>(vec);
    case 13:
      return shift_left<13>(vec);
    case 14:
      return shift_left<14>(vec);
    case 15:
      return shift_left<15>(vec);
    case 16:
      return shift_left<16>(vec);
    case 17:
      return shift_left<17>(vec);
    case 18:
      return shift_left<18>(vec);
    case 19:
      return shift_left<19>(vec);
    case 20:
      return shift_left<20>(vec);
    case 21:
      return shift_left<21>(vec);
    case 22:
      return shift_left<22>(vec);
    case 23:
      return shift_left<23>(vec);
    case 24:
      return shift_left<24>(vec);
    case 25:
      return shift_left<25>(vec);
    case 26:
      return shift_left<26>(vec);
    case 27:
      return shift_left<27>(vec);
    case 28:
      return shift_left<28>(vec);
    case 29:
      return shift_left<29>(vec);
    case 30:
      return shift_left<30>(vec);
    case 31:
      return shift_left<31>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_left(int32x2_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    case 8:
      return shift_left<8>(vec);
    case 9:
      return shift_left<9>(vec);
    case 10:
      return shift_left<10>(vec);
    case 11:
      return shift_left<11>(vec);
    case 12:
      return shift_left<12>(vec);
    case 13:
      return shift_left<13>(vec);
    case 14:
      return shift_left<14>(vec);
    case 15:
      return shift_left<15>(vec);
    case 16:
      return shift_left<16>(vec);
    case 17:
      return shift_left<17>(vec);
    case 18:
      return shift_left<18>(vec);
    case 19:
      return shift_left<19>(vec);
    case 20:
      return shift_left<20>(vec);
    case 21:
      return shift_left<21>(vec);
    case 22:
      return shift_left<22>(vec);
    case 23:
      return shift_left<23>(vec);
    case 24:
      return shift_left<24>(vec);
    case 25:
      return shift_left<25>(vec);
    case 26:
      return shift_left<26>(vec);
    case 27:
      return shift_left<27>(vec);
    case 28:
      return shift_left<28>(vec);
    case 29:
      return shift_left<29>(vec);
    case 30:
      return shift_left<30>(vec);
    case 31:
      return shift_left<31>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_left(int16x8_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    case 8:
      return shift_left<8>(vec);
    case 9:
      return shift_left<9>(vec);
    case 10:
      return shift_left<10>(vec);
    case 11:
      return shift_left<11>(vec);
    case 12:
      return shift_left<12>(vec);
    case 13:
      return shift_left<13>(vec);
    case 14:
      return shift_left<14>(vec);
    case 15:
      return shift_left<15>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_left(int16x4_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    case 8:
      return shift_left<8>(vec);
    case 9:
      return shift_left<9>(vec);
    case 10:
      return shift_left<10>(vec);
    case 11:
      return shift_left<11>(vec);
    case 12:
      return shift_left<12>(vec);
    case 13:
      return shift_left<13>(vec);
    case 14:
      return shift_left<14>(vec);
    case 15:
      return shift_left<15>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_left(int8x16_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_left(int8x8_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    default:
      __builtin_unreachable();
  }
}

}  // namespace neon
#undef nce
