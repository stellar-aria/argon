#pragma once
#include <initializer_list>
#include <span>
#include "common.hpp"

#ifdef __clang__
#define ace [[gnu::always_inline]] constexpr
#else
#define ace [[gnu::always_inline]] inline
#endif


template <typename scalar_type>
class Argon64 : public argon::impl::Common<typename neon::Vec64<scalar_type>::type> {
  using T = argon::impl::Common<typename neon::Vec64<scalar_type>::type>;

 public:
  using vector_type = neon::Vec64<scalar_type>::type;
  using lane_type = argon::impl::Lane<vector_type>;

  static_assert(neon::is_doubleword_v<vector_type>);

  static constexpr size_t bytes = 8;
  static constexpr size_t lanes = bytes / sizeof(scalar_type);

  ace Argon64() : T(){};
  ace Argon64(vector_type vector) : T(vector){};
  ace Argon64(scalar_type scalar) : T(scalar){};
  ace Argon64(scalar_type const* ptr) : T(ptr){};
  ace Argon64(T&& in) : T(in){};
  ace Argon64(std::array<scalar_type, 2> value_list) : T(value_list.data()) {};
  ace Argon64(std::span<scalar_type> slice) : T(slice) {};

  ace static Argon64<scalar_type> Create(uint64_t a) { return neon::create<vector_type>(a); }

  ace Argon64<scalar_type> operator=(scalar_type b) { return this->vec_ = neon::duplicate<vector_type>(b); }
  ace Argon64<scalar_type> operator=(argon::impl::Lane<typename neon::Vec64<scalar_type>::type> b) { return this->vec_ = neon::duplicate_lane<vector_type>(b.vec(), b.lane()); }
  ace Argon64<scalar_type> operator=(argon::impl::Lane<typename neon::Vec128<scalar_type>::type> b) {
    constexpr size_t doubleword_lanes = Argon64<scalar_type>::lanes;
    size_t lane = b.lane();
    Argon128<scalar_type> vec = b.vec();
    Argon64<scalar_type> half;
    if (lane >= doubleword_lanes) {
        half = vec.GetHigh();
        lane -= doubleword_lanes;
    } else {
        half = vec.GetLow();
    }
    return this->vec_ = neon::duplicate_lane<vector_type>(half, lane);
  }

  template <typename U>
  requires argon::impl::has_larger_v<scalar_type>
  ace Argon128<U> AddLong(Argon64<scalar_type> b) const { return neon::add_long(this->vec_, b); }

  template <typename U>
  requires argon::impl::has_larger_v<scalar_type>
  ace Argon128<U> MultiplyLong(Argon64<scalar_type> b) const { return neon::multiply_long(this->vec_, b); }

  template <typename U>
  requires argon::impl::has_larger_v<scalar_type>
  ace Argon128<U> MultiplyLong(scalar_type b) const { return neon::multiply_long(this->vec_, b); }

  template <typename U>
  requires argon::impl::has_larger_v<scalar_type>
  ace Argon128<U> MultiplyLong(lane_type b) const { return neon::multiply_long_lane(this->vec_, b.vec(), b.lane()); }

  template <typename U>
  requires (std::is_same_v<vector_type, int16x4_t> || std::is_same_v<vector_type, int32x2_t>)
  ace Argon128<U> MultiplyFixedLong(Argon64<scalar_type> b) const { return neon::multiply_subtract_long(this->vec_, b); }

  template <typename U>
  requires (std::is_same_v<vector_type, int16x4_t> || std::is_same_v<vector_type, int32x2_t>)
  ace Argon128<U> MultiplyFixedLong(scalar_type b) const { return neon::multiply_subtract_long(this->vec_, b); }

  template <typename U>
  requires (std::is_same_v<vector_type, int16x4_t> || std::is_same_v<vector_type, int32x2_t>)
  ace Argon128<U> MultiplyFixedLong(lane_type b) const { return neon::multiply_subtract_long(this->vec_, b.vec(), b.lane()); }

  template <typename U>
  requires argon::impl::has_larger_v<scalar_type>
  ace Argon128<U> SubtractLong(Argon64<scalar_type> b) const { return neon::subtract_long(this->vec_, b); }

  template <typename U>
  requires argon::impl::has_larger_v<scalar_type>
  ace Argon128<U> SubtractAbsoluteLong(Argon64<scalar_type> b) const { return neon::subtract_absolute_long(this->vec_, b); }

  template <typename U>
  requires argon::impl::has_larger_v<scalar_type>
  ace Argon128<U> PairwiseAddLong() const { return neon::pairwise_add_long(this->vec_); }

  template <typename U>
  requires argon::impl::has_smaller_v<scalar_type>
  ace Argon128<U> PairwiseAddLong(Argon64<typename argon::impl::NextSmaller<scalar_type>> b) const { return neon::pairwise_add_long(this->vec_, b); }

  template <typename U>
  requires argon::impl::has_larger_v<scalar_type>
  ace Argon128<U> Widen() const { return neon::move_long(this->vec_); }

  ace Argon64<scalar_type> TableLookup(Argon64<scalar_type> idx) { return neon::table_lookup1(this->vec_, idx); }
  ace Argon64<scalar_type> TableExtension(Argon64<scalar_type> b, Argon64<scalar_type> idx) { return neon::table_extension1(this->vec_, b, idx); }

  template <size_t num_tables>
  ace Argon64<scalar_type> TableExtension(std::array<Argon64<scalar_type>, num_tables> b, Argon64<scalar_type> idx) {
    return TableExtension<num_tables>((vector_type*)b.data(), idx);
  }

  template <size_t num_tables>
  ace Argon64<scalar_type> TableExtension(vector_type* b, Argon64<scalar_type> idx) {
    static_assert(num_tables > 1 && num_tables < 5, "Table Extension can only be performed with 1, 2, 3, or 4 tables");

    using multivec_type = argon::impl::MultiVec<vector_type, num_tables>::type;

    multivec_type multivec = *(multivec_type*)b;

    if constexpr (num_tables == 2) {
      return neon::table_extension2(this->vec_, multivec, idx);
    } else if constexpr (num_tables == 3) {
      return neon::table_extension3(this->vec_, multivec, idx);
    } else if constexpr (num_tables == 4) {
      return neon::table_extension4(this->vec_, multivec, idx);
    }
  }

  template <typename U> ace Argon64<U> Convert() { return neon::convert<typename neon::Vec64<U>::type>(this->vec_); }
  template <typename U> ace Argon64<U> Convert(int n) { return neon::convert_n<typename neon::Vec64<U>::type>(this->vec_, n); }

  ace Argon128<scalar_type> CombineWith(Argon64<scalar_type> high) const { return neon::combine(this->vec_, high); }
};

#undef ace
