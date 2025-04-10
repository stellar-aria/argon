#pragma once
#ifdef __ARM_FEATURE_MVE
#include "argon/utility.hpp"
#include "multivector.hpp"
#include "scalar.hpp"

namespace mve {
template <typename T>
void store1_x2(Scalar_t<T>* ptr, MultiVector_t<T, 2> value) {
  constexpr size_t lanes = sizeof(T) / sizeof(Scalar_t<T>);
  argon::utility::constexpr_for<0, 2, 1>([&](auto i) {  //<
    *ptr = value[i];
    ptr += lanes;
  });
}
template <typename T>
void store1_x3(Scalar_t<T>* ptr, MultiVector_t<T, 3> value) {
  constexpr size_t lanes = sizeof(T) / sizeof(Scalar_t<T>);
  argon::utility::constexpr_for<0, 3, 1>([&](auto i) {  //<
    *ptr = value[i];
    ptr += lanes;
  });
}
template <typename T>
void store1_x4(Scalar_t<T>* ptr, MultiVector_t<T, 4> value) {
  constexpr size_t lanes = sizeof(T) / sizeof(Scalar_t<T>);
  argon::utility::constexpr_for<0, 4, 1>([&](auto i) {  //<
    *ptr = value[i];
    ptr += lanes;
  });
}

template <size_t LaneIndex, typename T>
void store2_lane(Scalar_t<T>* ptr, MultiVector_t<T, 2> value) {
  constexpr size_t lanes = sizeof(T) / sizeof(Scalar_t<T>);
  argon::utility::constexpr_for<0, 2, 1>([&](auto i) {  //<
    *ptr = value[i][LaneIndex];
    ptr += lanes;
  });
}

template <size_t LaneIndex, typename T>
void store3_lane(Scalar_t<T>* ptr, MultiVector_t<T, 3> value) {
  constexpr size_t lanes = sizeof(T) / sizeof(Scalar_t<T>);
  argon::utility::constexpr_for<0, 3, 1>([&](auto i) {  //<
    *ptr = value[i][LaneIndex];
    ptr += lanes;
  });
}

template <size_t LaneIndex, typename T>
void store4_lane(Scalar_t<T>* ptr, MultiVector_t<T, 4> value) {
  constexpr size_t lanes = sizeof(T) / sizeof(Scalar_t<T>);
  argon::utility::constexpr_for<0, 4, 1>([&](auto i) {  //<
    *ptr = value[i][LaneIndex];
    ptr += lanes;
  });
}
}  // namespace mve
#endif
