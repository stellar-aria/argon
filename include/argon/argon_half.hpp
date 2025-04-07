#pragma once
#include "vector.hpp"

#ifdef ARGON_PLATFORM_SIMDE
#define ace
#elifdef __clang__
#define ace [[gnu::always_inline]] constexpr
#else
#define ace [[gnu::always_inline]] inline
#endif

template <typename scalar_type>
class ArgonHalf : public argon::Vector<neon::Vec64_t<scalar_type>> {
  using T = argon::Vector<neon::Vec64_t<scalar_type>>;

 public:
  using vector_type = neon::Vec64_t<scalar_type>;
  using lane_type = const argon::Lane<vector_type>;

  static_assert(neon::is_doubleword_v<vector_type>);

  static constexpr size_t bytes = 8;
  static constexpr size_t lanes = bytes / sizeof(scalar_type);

  ace ArgonHalf() : T() {};
  ace ArgonHalf(vector_type vector) : T{vector} {};
  ace ArgonHalf(scalar_type scalar) : T{scalar} {};
  // ace ArgonHalf(scalar_type const* ptr) : T(ptr) {};
  ace ArgonHalf(T&& in) : T{in} {};
  ace ArgonHalf(std::array<scalar_type, 2> value_list) : T{T::Load(value_list.data())} {};
  // ace ArgonHalf(std::span<scalar_type> slice) : T(slice) {};

  template <neon::is_vector_type intrinsic_type>
  ace ArgonHalf(argon::Lane<intrinsic_type> b) : T(b) {};

  template <typename... arg_types>
    requires(sizeof...(arg_types) > 1)
  ace ArgonHalf(arg_types... args) : T{vector_type{args...}} {}

  ace static ArgonHalf<scalar_type> Create(uint64_t a) { return neon::create<vector_type>(a); }

  template <typename new_scalar_type>
  ace ArgonHalf<new_scalar_type> As() const {
    return neon::reinterpret<neon::Vec64_t<new_scalar_type>>(this->vec_);
  }

  template <typename U>
    requires argon::helpers::has_larger_v<scalar_type>
  ace Argon<U> AddLong(ArgonHalf<scalar_type> b) const {
    return neon::add_long(this->vec_, b);
  }

  template <typename U>
    requires argon::helpers::has_larger_v<scalar_type>
  ace Argon<U> MultiplyLong(ArgonHalf<scalar_type> b) const {
    return neon::multiply_long(this->vec_, b);
  }

  template <typename U>
    requires argon::helpers::has_larger_v<scalar_type>
  ace Argon<U> MultiplyLong(scalar_type b) const {
    return neon::multiply_long(this->vec_, b);
  }

  template <typename U>
    requires argon::helpers::has_larger_v<scalar_type>
  ace Argon<U> MultiplyLong(lane_type b) const {
    return neon::multiply_long_lane(this->vec_, b.vec(), b.lane());
  }

  template <typename U>
    requires(std::is_same_v<vector_type, int16x4_t> || std::is_same_v<vector_type, int32x2_t>)
  ace Argon<U> MultiplyFixedLong(ArgonHalf<scalar_type> b) const {
    return neon::multiply_subtract_long(this->vec_, b);
  }

  template <typename U>
    requires(std::is_same_v<vector_type, int16x4_t> || std::is_same_v<vector_type, int32x2_t>)
  ace Argon<U> MultiplyFixedLong(scalar_type b) const {
    return neon::multiply_subtract_long(this->vec_, b);
  }

  template <typename U>
    requires(std::is_same_v<vector_type, int16x4_t> || std::is_same_v<vector_type, int32x2_t>)
  ace Argon<U> MultiplyFixedLong(lane_type b) const {
    return neon::multiply_subtract_long(this->vec_, b.vec(), b.lane());
  }

  template <typename U>
    requires argon::helpers::has_larger_v<scalar_type>
  ace Argon<U> SubtractLong(ArgonHalf<scalar_type> b) const {
    return neon::subtract_long(this->vec_, b);
  }

  template <typename U>
    requires argon::helpers::has_larger_v<scalar_type>
  ace Argon<U> SubtractAbsoluteLong(ArgonHalf<scalar_type> b) const {
    return neon::subtract_absolute_long(this->vec_, b);
  }

  template <typename U>
    requires argon::helpers::has_larger_v<scalar_type>
  ace Argon<U> PairwiseAddLong() const {
    return neon::pairwise_add_long(this->vec_);
  }

  template <typename U>
    requires argon::helpers::has_smaller_v<scalar_type>
  ace Argon<U> PairwiseAddLong(ArgonHalf<typename argon::helpers::NextSmaller<scalar_type>> b) const {
    return neon::pairwise_add_long(this->vec_, b);
  }

  template <typename U>
    requires argon::helpers::has_larger_v<scalar_type>
  ace Argon<U> Widen() const {
    return neon::move_long(this->vec_);
  }

  template <size_t n>
  ace Argon<argon::helpers::NextLarger_t<scalar_type>> ShiftLeftLong()
    requires argon::helpers::has_larger_v<scalar_type>
  {
    return neon::shift_left_long<n>(this->vec_);
  }

  ace Argon<argon::helpers::NextLarger_t<scalar_type>> MultiplyDoubleSaturateLong(ArgonHalf<scalar_type> b)
    requires argon::helpers::has_larger_v<scalar_type>
  {
    return neon::multiply_double_saturate_long(this->vec_, b);
  }

  ace ArgonHalf<scalar_type> TableLookup(ArgonHalf<scalar_type> idx) { return neon::table_lookup1(this->vec_, idx); }
  ace ArgonHalf<scalar_type> TableExtension(ArgonHalf<scalar_type> b, ArgonHalf<scalar_type> idx) {
    return neon::table_extension1(this->vec_, b, idx);
  }

  template <size_t num_tables>
  ace ArgonHalf<scalar_type> TableExtension(std::array<ArgonHalf<scalar_type>, num_tables> b,
                                            ArgonHalf<scalar_type> idx) {
    return TableExtension<num_tables>((vector_type*)b.data(), idx);
  }

  template <size_t num_tables>
  ace ArgonHalf<scalar_type> TableExtension(vector_type* b, ArgonHalf<scalar_type> idx) {
    static_assert(num_tables > 1 && num_tables < 5, "Table Extension can only be performed with 1, 2, 3, or 4 tables");

    using multivec_type = argon::helpers::MultiVec<vector_type, num_tables>::type;

    multivec_type multivec = *(multivec_type*)b;

    if constexpr (num_tables == 2) {
      return neon::table_extension2(this->vec_, multivec, idx);
    } else if constexpr (num_tables == 3) {
      return neon::table_extension3(this->vec_, multivec, idx);
    } else if constexpr (num_tables == 4) {
      return neon::table_extension4(this->vec_, multivec, idx);
    }
  }

  template <typename U>
  ace ArgonHalf<U> ConvertTo() {
    return neon::convert<typename neon::Vec64<U>::type>(this->vec_);
  }
  template <typename U, int fracbits>
    requires(std::is_same_v<U, uint32_t> || std::is_same_v<U, int32_t> || std::is_same_v<U, float>)
  ace ArgonHalf<U> ConvertTo() {
    if constexpr (std::is_same_v<U, float>) {
      return neon::convert_n<fracbits>(this->vec_);
    } else if constexpr (std::is_unsigned_v<U>) {
      return neon::convert_n_unsigned<fracbits>(this->vec_);
    } else if constexpr (std::is_signed_v<U>) {
      return neon::convert_n_signed<fracbits>(this->vec_);
    }
  }

  ace Argon<scalar_type> CombineWith(ArgonHalf<scalar_type> high) const { return neon::combine(this->vec_, high); }

  ace ArgonHalf<scalar_type> Reverse() const { return this->Reverse64bit(); }
};

template <class... arg_types>
  requires(sizeof...(arg_types) > 1)
// ArgonHalf(arg_types...) -> ArgonHalf<arg_types...[0]>;
ArgonHalf(arg_types...) -> ArgonHalf<std::tuple_element_t<0, std::tuple<arg_types...>>>;

template <typename V>
  requires std::is_scalar_v<V>
ace ArgonHalf<V> operator+(const V a, const ArgonHalf<V> b) {
  return b.Add(a);
}

template <typename V>
  requires std::is_scalar_v<V>
ace ArgonHalf<V> operator-(const V a, const ArgonHalf<V> b) {
  return ArgonHalf<V>{a}.Subtract(b);
}

template <typename V>
  requires std::is_scalar_v<V>
ace ArgonHalf<V> operator*(const V a, const ArgonHalf<V> b) {
  return b.Multiply(a);
}

template <typename V>
  requires std::is_scalar_v<V>
ace ArgonHalf<V> operator/(const V a, const ArgonHalf<V> b) {
  return ArgonHalf<V>{a}.Divide(b);
}

namespace std {
template <typename T>
struct tuple_size<ArgonHalf<T>> {
  static constexpr size_t value = ArgonHalf<T>::lanes;
};
template <size_t Index, typename T>
struct tuple_element<Index, ArgonHalf<T>> {
  static_assert(Index < ArgonHalf<T>::lanes);
  using type = argon::Lane<typename ArgonHalf<T>::vector_type>;
};
}  // namespace std

#undef ace
