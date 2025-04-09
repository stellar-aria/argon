#pragma once

namespace argon::utility {
/// @brief A constexpr function template for compile-time iteration. Used to unroll loops at compile time.
/// @tparam Start The starting value of the iteration.
/// @tparam End The ending value of the iteration.
/// @tparam Increment The increment value for each iteration step.
/// @tparam FunctionType The callable type to be invoked during each iteration step.
/// @param f The callable object to be invoked with the current iteration value.
template <auto Start, auto End, auto Increment, class FunctionType>
constexpr void constexpr_for(FunctionType&& f) {
  if constexpr (Start < End) {
    f.template operator()<Start>();
    constexpr_for<Start + Increment, End, Increment>(f);
  }
}
}  // namespace argon::utility
