#pragma once
#include "arm_neon.hpp"
#include <stdint.h>
#include <cstddef>

#include <type_traits>

namespace argon {
namespace impl {
template <typename type>
struct Neon64 {};
template <typename type>
struct Neon128 {};

// clang-format off
template <> struct Neon64<int8_t> {using type = int8x8_t; };
template <> struct Neon128<int8_t>  {using type = int8x16_t; };

template <> struct Neon64<uint8_t> {using type = uint8x8_t; };
template <> struct Neon128<uint8_t>  {using type = uint8x16_t; };

template <> struct Neon64<int16_t> {using type = int16x4_t; };
template <> struct Neon128<int16_t>  {using type = int16x8_t; };

template <> struct Neon64<uint16_t> {using type = uint16x4_t; };
template <> struct Neon128<uint16_t>  {using type = uint16x8_t; };

template <> struct Neon64<int32_t> {using type = int32x2_t; };
template <> struct Neon128<int32_t>  {using type = int32x4_t; };

template <> struct Neon64<uint32_t> {using type = uint32x2_t; };
template <> struct Neon128<uint32_t>  {using type = uint32x4_t; };

template <> struct Neon64<int64_t> {using type = int64x1_t; };
template <> struct Neon128<int64_t>  {using type = int64x2_t; };

template <> struct Neon64<uint64_t> {using type = uint64x1_t; };
template <> struct Neon128<uint64_t>  {using type = uint64x2_t; };

template <> struct Neon64<float> {using type = float32x2_t; };
template <> struct Neon128<float>  {using type = float32x4_t; };

template <typename vector_type>
class Common {
public:
  using T = Common<vector_type>;

	constexpr Common(vector_type vector) : vec_(vector){};


	constexpr T Add(T b) const { return neon::add(vec_, b); }

	constexpr T operator+(T b) const { return neon::add(vec_, b); }

	constexpr auto Get(const int i) const {
		switch (i) {
		case 0:
			return neon::get<0>(vec_);
		case 1:
			return neon::get<1>(vec_);
		case 2:
			return neon::get<2>(vec_);
		case 3:
			return neon::get<3>(vec_);
		case 4:
			return neon::get<4>(vec_);
		case 5:
			return neon::get<5>(vec_);
		case 6:
			return neon::get<6>(vec_);
		case 7:
			return neon::get<7>(vec_);
    	case 8:
			return neon::get<8>(vec_);
		default:
			__builtin_unreachable();
		}
	}

	constexpr auto operator[](const int i) const { return Get(i); }

  template <int i>
  constexpr T ShiftRight() const {
      return neon::shift_right<i>(vec_);
  }

  constexpr T ShiftRight(const int i) const {
		switch (i) {
		case 1:
			return ShiftRight<1>();
		case 2:
			return ShiftRight<2>();
		case 3:
			return ShiftRight<3>();
		case 4:
			return ShiftRight<4>();
		case 5:
			return ShiftRight<5>();
		case 6:
			return ShiftRight<6>();
		case 7:
			return ShiftRight<7>();
        case 8:
			return ShiftRight<8>();
		default:
			__builtin_unreachable();
		}
	}
    
    /// A = B + (C >> D)
  template <int i>
  constexpr T ShiftRightAccumulate(T adder) const {
        return neon::shift_right_accumulate<i>(adder.vec_, vec_);
	}

  constexpr T operator>>(const int i) const { return ShiftRight(i); }

	constexpr operator vector_type() const { return vec_; }

  constexpr vector_type vec() const { return vec_; }

private:
	vector_type vec_;
};

// clang-format on

}  // namespace impl

template <typename base>
class Neon64 : public impl::Common<typename impl::Neon64<base>::type> {
  using T = impl::Common<typename impl::Neon64<base>::type>;

 public:
  using vector_type = impl::Neon64<base>::type;
  using T::T;
  constexpr Neon64(T&& in) : T(in){};
};

template <typename base>
class Neon128 : public impl::Common<typename impl::Neon128<base>::type> {
  using T = impl::Common<typename impl::Neon128<base>::type>;

 public:
  using vector_type = impl::Neon128<base>::type;
  using T::T;
  constexpr Neon128(T&& in) : T(in){};
};

// template <typename T>
// T T(impl::Common<T> in) {
//     return in.vec();
// }

template <typename T>
concept doubleword = std::is_same_v<T, uint8x8_t> || std::is_same_v<T, uint16x4_t> || std::is_same_v<T, uint32x2_t> ||
                     std::is_same_v<T, uint64x1_t>;

template <typename T>
concept quadword = std::is_same_v<T, uint8x16_t> || std::is_same_v<T, uint16x8_t> || std::is_same_v<T, uint32x4_t> ||
                   std::is_same_v<T, uint64x2_t>;

template <typename T>
concept vector_type = doubleword<T> || quadword<T>;

template <typename N, vector_type V>
N reinterpret(impl::Common<V> in) {
  return {neon::reinterpret<typename N::vector_type>(in.vec())};
}

template <typename N, vector_type V>
N reinterpret(V in) {
  static_assert(!std::is_same_v<typename N::vector_type, V>);
  return N{neon::reinterpret<typename N::vector_type>(in)};
}

using uint8 = Neon64<uint8_t>;
using uint8_q = Neon128<uint8_t>;
using uint16 = Neon64<uint16_t>;
using uint16_q = Neon128<uint16_t>;
using uint32 = Neon64<uint32_t>;
using uint32_q = Neon128<uint32_t>;
using uint64 = Neon64<uint64_t>;
using uint64_q = Neon128<uint64_t>;

using int8 = Neon64<int8_t>;
using int8_q = Neon128<int8_t>;
using int16 = Neon64<int16_t>;
using int16_q = Neon128<int16_t>;
using int32 = Neon64<int32_t>;
using int32_q = Neon128<int32_t>;
using int64 = Neon64<int64_t>;
using int64_q = Neon128<int64_t>;

using float32 = Neon64<float>;
using float32_q = Neon128<float>;

}  // namespace argon

