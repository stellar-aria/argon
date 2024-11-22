#pragma once
#include <array>
#include "argon_for.hpp"

namespace argon {
namespace detail {
template <class intrinsic_type, std::size_t N, std::size_t... I>
constexpr std::array<impl::ArgonFor_t<intrinsic_type>, N> to_array_impl(intrinsic_type (&a)[N],
                                                                        std::index_sequence<I...>) {
  using argon_type = impl::ArgonFor_t<intrinsic_type>;
  return {{argon_type{a[I]}...}};
}

template <class intrinsic_type, std::size_t N, std::size_t... I>
constexpr std::array<impl::ArgonFor_t<intrinsic_type>, N> to_array_impl(intrinsic_type (&&a)[N],
                                                                        std::index_sequence<I...>) {
  using argon_type = impl::ArgonFor_t<intrinsic_type>;
  return {{argon_type{std::move(a[I])}...}};
}
}  // namespace detail

template <class intrinsic_type, std::size_t N>
constexpr std::array<impl::ArgonFor_t<intrinsic_type>, N> to_array(intrinsic_type (&a)[N]) {
  return detail::to_array_impl(a, std::make_index_sequence<N>{});
}

template <class intrinsic_type, std::size_t N>
constexpr std::array<impl::ArgonFor_t<intrinsic_type>, N> to_array(intrinsic_type (&&a)[N]) {
  return detail::to_array_impl(std::move(a), std::make_index_sequence<N>{});
}

}  // namespace argon
