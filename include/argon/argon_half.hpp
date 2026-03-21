#pragma once
#include "vector.hpp"

#ifndef ARGON_PLATFORM_MVE
#ifdef __clang__
#define ace [[gnu::always_inline]] constexpr
#else
#define ace [[gnu::always_inline]] inline
#endif
template <typename ScalarType>
class ArgonHalf;

/// @brief A 64-bit SIMD half-vector for types that cannot be widened (`double`, `uint64_t`, `int64_t`).
/// @tparam ScalarType Must be `double`, `uint64_t`, or `int64_t`.
/// @details Provides the full `argon::Vector` lane-wise API plus helpers such as `Create`, `As`,
/// `CombineWith`, and table-lookup operations. Combine two halves via `CombineWith` to make an
/// `Argon<ScalarType>` 128-bit vector.
template <typename ScalarType>
  requires std::same_as<ScalarType, double> || std::same_as<ScalarType, uint64_t> || std::same_as<ScalarType, int64_t>
class ArgonHalf<ScalarType> : public argon::Vector<neon::Vec64_t<ScalarType>> {
  using T = argon::Vector<neon::Vec64_t<ScalarType>>;

 public:
  using vector_type = neon::Vec64_t<ScalarType>;
  using lane_type = const argon::Lane<vector_type>;

  static_assert(neon::is_doubleword_v<vector_type>);

  static constexpr size_t bytes = 8;
  static constexpr size_t lanes = bytes / sizeof(ScalarType);

  using T::T;
  ace ArgonHalf(argon::Vector<vector_type> vec) : T{std::move(vec)} {};
  ace ArgonHalf(const ArgonHalf&) = default;
  ace ArgonHalf(ArgonHalf&&) = default;
  ace ArgonHalf& operator=(const ArgonHalf&) = default;
  ace ArgonHalf& operator=(ArgonHalf&&) = default;

  /// @brief Create a new ArgonHalf from a raw 64-bit value
  /// @param a The raw 64-bit value to create the ArgonHalf from
  ace static ArgonHalf<ScalarType> Create(uint64_t a) { return neon::create<vector_type>(a); }

  /// @brief reinterpret an ArgonHalf to a different type
  /// @tparam NewScalarType The type to reinterpret to
  template <typename NewScalarType>
  ace ArgonHalf<NewScalarType> As() const {
    return neon::reinterpret<neon::Vec64_t<NewScalarType>>(this->vec_);
  }

  /// @brief Look up each index lane in `idx` from this vector acting as a one-register table.
  /// @param idx Index vector. Out-of-range indices produce 0.
  ace ArgonHalf<ScalarType> TableLookup(ArgonHalf<ScalarType> idx) { return neon::table_lookup1(this->vec_, idx); }

  /// @brief Extend a previous table-lookup result using this vector as an additional table (1 extension register).
  /// @param b   The extension table.
  /// @param idx Index vector used for the lookup.
  ace ArgonHalf<ScalarType> TableExtension(ArgonHalf<ScalarType> b, ArgonHalf<ScalarType> idx) {
    return neon::table_extension1(this->vec_, b, idx);
  }

  /// @brief Multi-register table extension lookup (2–4 registers) supplied as `std::array`.
  /// @tparam NumTables Number of extension tables (2, 3, or 4).
  template <size_t NumTables>
  ace ArgonHalf<ScalarType> TableExtension(std::array<ArgonHalf<ScalarType>, NumTables> b, ArgonHalf<ScalarType> idx) {
    return TableExtension<NumTables>((vector_type*)b.data(), idx);
  }

  /// @brief Multi-register table extension lookup (2–4 registers) from a raw pointer.
  /// @tparam NumTables Number of extension tables (2, 3, or 4).
  template <size_t NumTables>
  ace ArgonHalf<ScalarType> TableExtension(vector_type* b, ArgonHalf<ScalarType> idx) {
    static_assert(NumTables > 1 && NumTables < 5, "Table Extension can only be performed with 1, 2, 3, or 4 tables");

    using multivec_type = neon::MultiVector_t<vector_type, NumTables>;

    multivec_type multivector = *(multivec_type*)b;

    if constexpr (NumTables == 2) {
      return neon::table_extension2(this->vec_, multivector, idx);
    } else if constexpr (NumTables == 3) {
      return neon::table_extension3(this->vec_, multivector, idx);
    } else if constexpr (NumTables == 4) {
      return neon::table_extension4(this->vec_, multivector, idx);
    }
  }

  /// @brief Convert each lane to a different element type.
  /// @tparam U The destination element type.
  template <typename U>
  ace ArgonHalf<U> ConvertTo() {
    return neon::convert<typename neon::Vec64<U>::type>(this->vec_);
  }

  /// @brief Convert each lane to a different type using a fixed-point fractional bit count.
  /// @tparam U        The destination element type (`float`, `int32_t`, or `uint32_t`).
  /// @tparam fracbits The number of fractional bits.
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

  /// @brief Combine this (low) half with `high` to form a 128-bit `Argon<ScalarType>` vector.
  ace Argon<ScalarType> CombineWith(ArgonHalf<ScalarType> high) const { return neon::combine(this->vec_, high); }

  /// @brief Reverse the order of all elements within this 64-bit vector.
  ace ArgonHalf<ScalarType> Reverse() const { return this->Reverse64bit(); }
};

/// @brief A 64-bit SIMD half-vector for types that can be widened to a next-larger element type.
/// @tparam ScalarType An integer or floating-point type constrained by `argon::helpers::has_larger`
///         (e.g., `int8_t` → `int16_t`, `int16_t` → `int32_t`, `int32_t` → `int64_t`, `float` → `double`).
/// @details Extends `argon::Vector` with widening arithmetic (`AddLong`, `MultiplyLong`, `SubtractLong`,
/// `Widen`, `ShiftLeftLong`, etc.) as well as the common table-lookup and conversion helpers.
/// Two halves can be joined via `CombineWith` to form an `Argon<ScalarType>` 128-bit vector.
template <argon::helpers::has_larger ScalarType>
class ArgonHalf<ScalarType> : public argon::Vector<neon::Vec64_t<ScalarType>> {
  using T = argon::Vector<neon::Vec64_t<ScalarType>>;
  using next_larger = typename argon::helpers::NextLarger_t<ScalarType>;
  using argon_next_larger = Argon<next_larger>;

 public:
  using vector_type = neon::Vec64_t<ScalarType>;
  using lane_type = const argon::Lane<vector_type>;

  static_assert(neon::is_doubleword_v<vector_type>);

  static constexpr size_t bytes = 8;
  static constexpr size_t lanes = bytes / sizeof(ScalarType);

  using T::T;

  /// @brief Create a new ArgonHalf from a raw 64-bit value
  /// @param a The raw 64-bit value to create the ArgonHalf from
  ace static ArgonHalf<ScalarType> Create(uint64_t a) { return neon::create<vector_type>(a); }

  /// @brief reinterpret an ArgonHalf to a different type
  /// @tparam NewScalarType The type to reinterpret to
  template <typename NewScalarType>
  ace ArgonHalf<NewScalarType> As() const {
    return neon::reinterpret<neon::Vec64_t<NewScalarType>>(this->vec_);
  }

  /// @brief Add this and `b`, widening each lane to the next-larger element type.
  ace argon_next_larger AddLong(ArgonHalf<ScalarType> b) const { return neon::add_long(this->vec_, b); }

  /// @brief Multiply this and `b`, widening each product to the next-larger element type (vector × vector).
  ace argon_next_larger MultiplyLong(ArgonHalf<ScalarType> b) const { return neon::multiply_long(this->vec_, b); }

  /// @brief Multiply this by a scalar, widening each product (vector × scalar).
  ace argon_next_larger MultiplyLong(ScalarType b) const { return neon::multiply_long(this->vec_, b); }

  /// @brief Multiply this by a lane value, widening each product (vector × lane).
  ace argon_next_larger MultiplyLong(lane_type b) const {
    return neon::multiply_long_lane(this->vec_, b.vec(), b.lane());
  }

  /// @brief Multiply this and `b`, widen each product, and prepare for long accumulation (vector × vector).
  ace argon_next_larger MultiplyAddLong(ArgonHalf<ScalarType> b) const {
    return neon::multiply_add_long(this->vec_, b);
  }

  /// @brief Multiply-accumulate long (vector × scalar).
  ace argon_next_larger MultiplyAddLong(ScalarType b) const { return neon::multiply_add_long(this->vec_, b); }

  /// @brief Multiply-accumulate long (vector × lane).
  ace argon_next_larger MultiplyAddLong(lane_type b) const {
    return neon::multiply_add_long_lane(this->vec_, b.vec(), b.lane());
  }

  /// @brief Multiply, double, and saturate long: `saturate(2 * this * b)` widened (vector × vector).
  ace argon_next_larger MultiplyDoubleSaturateLong(ArgonHalf<ScalarType> b) const
    requires(std::is_same_v<vector_type, int16x4_t> || std::is_same_v<vector_type, int32x2_t>)
  {
    return neon::multiply_double_saturate_long(this->vec_, b);
  }

  /// @brief Multiply, double, and saturate long (vector × scalar).
  ace argon_next_larger MultiplyDoubleSaturateLong(ScalarType b) const
    requires(std::is_same_v<vector_type, int16x4_t> || std::is_same_v<vector_type, int32x2_t>)
  {
    return neon::multiply_double_saturate_long(this->vec_, b);
  }

  /// @brief Multiply, double, and saturate long (vector × lane).
  ace argon_next_larger MultiplyDoubleSaturateLong(lane_type b) const
    requires(std::is_same_v<vector_type, int16x4_t> || std::is_same_v<vector_type, int32x2_t>)
  {
    return neon::multiply_double_saturate_long_lane(this->vec_, b.vec(), b.lane());
  }

  /// @brief Multiply, double, add, and saturate long: `saturate(acc + 2 * this * b)` widened (vector × vector).
  ace argon_next_larger MultiplyDoubleAddSaturateLong(ArgonHalf<ScalarType> b) const
    requires(std::is_same_v<vector_type, int16x4_t> || std::is_same_v<vector_type, int32x2_t>)
  {
    return neon::multiply_double_add_saturate_long(this->vec_, b);
  }

  /// @brief Multiply, double, add, and saturate long (vector × scalar).
  ace argon_next_larger MultiplyDoubleAddSaturateLong(ScalarType b) const
    requires(std::is_same_v<vector_type, int16x4_t> || std::is_same_v<vector_type, int32x2_t>)
  {
    return neon::multiply_double_add_saturate_long(this->vec_, b);
  }

  /// @brief Multiply, double, add, and saturate long (vector × lane).
  ace argon_next_larger MultiplyDoubleAddSaturateLong(lane_type b) const
    requires(std::is_same_v<vector_type, int16x4_t> || std::is_same_v<vector_type, int32x2_t>)
  {
    return neon::multiply_double_add_saturate_long_lane(this->vec_, b.vec(), b.lane());
  }

  /// @brief Subtract `b` from this, widening each result to the next-larger element type.
  ace argon_next_larger SubtractLong(ArgonHalf<ScalarType> b) const { return neon::subtract_long(this->vec_, b); }

  /// @brief Absolute difference and widen: `|this - b|` widened to the next-larger element type.
  ace argon_next_larger SubtractAbsoluteLong(ArgonHalf<ScalarType> b) const {
    return neon::subtract_absolute_long(this->vec_, b);
  }

  /// @brief Pairwise add adjacent lanes and widen: produces `lanes/2` wider-type results.
  ace argon_next_larger PairwiseAddLong() const { return neon::pairwise_add_long(this->vec_); }

  /// @brief Pairwise add this and the next-smaller-type vector `b`, widening into `argon_next_larger`.
  ace argon_next_larger PairwiseAddLong(ArgonHalf<typename argon::helpers::NextSmaller<ScalarType>> b) const {
    return neon::pairwise_add_long(this->vec_, b);
  }

  /// @brief Zero-extend (widen) each lane to the next-larger element type.
  ace argon_next_larger Widen() const { return neon::move_long(this->vec_); }

  /// @brief Shift each lane left by `n` bits, widening the result to the next-larger element type.
  /// @tparam n Shift amount (0 ≤ n ≤ element bits).
  template <size_t n>
  ace argon_next_larger ShiftLeftLong() {
    return neon::shift_left_long<n>(this->vec_);
  }

  /// @brief Look up each index lane in `idx` from this vector acting as a one-register table.
  /// @param idx Index vector. Out-of-range indices produce 0.
  ace ArgonHalf<ScalarType> TableLookup(ArgonHalf<ScalarType> idx) { return neon::table_lookup1(this->vec_, idx); }

  /// @brief Extend a previous table-lookup result using this vector as an additional table (1 extension register).
  /// @param b   The extension table.
  /// @param idx Index vector used for the lookup.
  ace ArgonHalf<ScalarType> TableExtension(ArgonHalf<ScalarType> b, ArgonHalf<ScalarType> idx) {
    return neon::table_extension1(this->vec_, b, idx);
  }

  /// @brief Multi-register table extension lookup (2–4 registers) supplied as `std::array`.
  /// @tparam NumTables Number of extension tables (2, 3, or 4).
  template <size_t NumTables>
  ace ArgonHalf<ScalarType> TableExtension(std::array<ArgonHalf<ScalarType>, NumTables> b, ArgonHalf<ScalarType> idx) {
    return TableExtension<NumTables>((vector_type*)b.data(), idx);
  }

  /// @brief Multi-register table extension lookup (2–4 registers) from a raw pointer.
  /// @tparam NumTables Number of extension tables (2, 3, or 4).
  template <size_t NumTables>
  ace ArgonHalf<ScalarType> TableExtension(vector_type* b, ArgonHalf<ScalarType> idx) {
    static_assert(NumTables > 1 && NumTables < 5, "Table Extension can only be performed with 1, 2, 3, or 4 tables");

    using multivec_type = neon::MultiVector_t<vector_type, NumTables>;

    multivec_type multivector = *(multivec_type*)b;

    if constexpr (NumTables == 2) {
      return neon::table_extension2(this->vec_, multivector, idx);
    } else if constexpr (NumTables == 3) {
      return neon::table_extension3(this->vec_, multivector, idx);
    } else if constexpr (NumTables == 4) {
      return neon::table_extension4(this->vec_, multivector, idx);
    }
  }

  /// @brief Convert each lane to a different element type.
  /// @tparam U The destination element type.
  template <typename U>
  ace ArgonHalf<U> ConvertTo() {
    return neon::convert<typename neon::Vec64<U>::type>(this->vec_);
  }

  /// @brief Convert each lane to a different type using a fixed-point fractional bit count.
  /// @tparam U        The destination element type (`float`, `int32_t`, or `uint32_t`).
  /// @tparam fracbits The number of fractional bits.
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

  /// @brief Combine this (low) half with `high` to form a 128-bit `Argon<ScalarType>` vector.
  ace Argon<ScalarType> CombineWith(ArgonHalf<ScalarType> high) const { return neon::combine(this->vec_, high); }

  /// @brief Reverse the order of all elements within this 64-bit vector.
  ace ArgonHalf<ScalarType> Reverse() const { return this->Reverse64bit(); }
};

template <class... ArgTypes>
  requires(sizeof...(ArgTypes) > 1)
ArgonHalf(ArgTypes...) -> ArgonHalf<std::tuple_element_t<0, std::tuple<ArgTypes...>>>;

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
#endif
#undef ace
