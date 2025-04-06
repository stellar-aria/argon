#pragma once
#include <array>
#include "argon_for.hpp"

namespace argon {
namespace detail {
template <class T, std::size_t N, std::size_t... I>
constexpr std::array<helpers::ArgonFor_t<T>, N> to_array_impl(T (&a)[N], std::index_sequence<I...>) {
  using argon_type = helpers::ArgonFor_t<T>;
  return {{argon_type{a[I]}...}};
}

template <class T, std::size_t N, std::size_t... I>
constexpr std::array<helpers::ArgonFor_t<T>, N> to_array_impl(T (&&a)[N], std::index_sequence<I...>) {
  using argon_type = helpers::ArgonFor_t<T>;
  return {{argon_type{std::move(a[I])}...}};
}
}  // namespace detail

/// @brief Convert a C-style array of vector types to a std::array of Argon types.
/// @tparam T The type of the elements in the array.
/// @tparam N The number of elements in the array.
/// @param a  The C-style array to convert.
/// @return A std::array of Argon types.
template <class T, std::size_t N>
constexpr std::array<helpers::ArgonFor_t<T>, N> to_array(T (&a)[N]) {
  return detail::to_array_impl(a, std::make_index_sequence<N>{});
}

/// @brief Convert a C-style array of vector types to a std::array of Argon types.
/// @tparam T The type of the elements in the array.
/// @tparam N The number of elements in the array.
/// @param a  The C-style array to convert.
/// @return A std::array of Argon types.
/// @details This overload is for rvalue references to arrays.
template <class T, std::size_t N>
constexpr std::array<helpers::ArgonFor_t<T>, N> to_array(T (&&a)[N]) {
  return detail::to_array_impl(std::move(a), std::make_index_sequence<N>{});
}

}  // namespace argon
