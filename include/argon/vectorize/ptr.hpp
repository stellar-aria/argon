// Copyright (c) 2025 Katherine Whitlock
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <ranges>
#include "argon/argon_full.hpp"
#include "arm_simd/helpers/nonvec.hpp"
#include "arm_simd/helpers/vec128.hpp"
#include "store.hpp"

#ifdef __ARM_FEATURE_MVE
#define simd helium
#else
#define simd neon
#endif


// Smart pointer for argon type
template <typename scalar_type>
struct ArgonPtr {
  using intrinsic_type = simd::Vec128_t<scalar_type>;
  static constexpr size_t lanes = sizeof(intrinsic_type) / sizeof(scalar_type);
  static constexpr size_t vectorizeable_size(size_t size) { return size & ~(lanes - 1); }

  using difference_type = std::ptrdiff_t;
  using value_type = Argon<scalar_type>;
  using pointer = Argon<scalar_type>*;

  ArgonPtr(scalar_type* ptr) : ptr_{ptr}, vec_{Argon<scalar_type>::Load(ptr_)} {}
  ArgonPtr(const ArgonPtr&) = default;
  ArgonPtr& operator=(const ArgonPtr&) = default;
  ArgonPtr(ArgonPtr&&) = default;

  ~ArgonPtr() {
    if (dirty_) {
      vec_.StoreTo(ptr_);
    }
  }

  pointer operator->() {
    dirty_ = true;
    return &vec_;
  }

  value_type& operator*() {
    dirty_ = true;
    return vec_;
  }

  const value_type& operator*() const { return vec_; }
  const pointer operator->() const { return &vec_; }

  void store() { vec_.StoreTo(ptr_); }
  void reload() { vec_ = value_type::Load(ptr_); }

  friend bool operator==(const ArgonPtr& a, const ArgonPtr& b) { return a.ptr_ == b.ptr_; }
  friend bool operator==(const ArgonPtr& a, const scalar_type* ptr) { return a.ptr_ == ptr; }
  friend bool operator!=(const ArgonPtr& a, const ArgonPtr& b) { return a.ptr_ != b.ptr_; }
  friend bool operator!=(const ArgonPtr& a, const scalar_type* ptr) { return a.ptr_ != ptr; }

 private:
  scalar_type* ptr_;
  value_type vec_;
  bool dirty_ = false;
};

namespace argon {

template <typename scalar_type>
struct vectorize_ptr : std::ranges::view_interface<vectorize_ptr<scalar_type>> {
  using intrinsic_type = simd::Vec128_t<scalar_type>;
  static constexpr size_t lanes = sizeof(intrinsic_type) / sizeof(scalar_type);
  static constexpr size_t vectorizeable_size(size_t size) { return size & ~(lanes - 1); }

 public:
  struct Iterator {
    using difference_type = std::ptrdiff_t;
    using value_type = ArgonPtr<scalar_type>;

    Iterator(scalar_type* ptr) : ptr{ptr} {}

    value_type operator*() const { return value_type{ptr}; }

    Iterator& operator++() {
      ptr += lanes;
      return *this;
    }

    void operator++(int) { ++*this; }
    friend bool operator==(const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; }
    friend bool operator==(const Iterator& a, const scalar_type* ptr) { return a.ptr == ptr; }
    friend bool operator!=(const Iterator& a, const Iterator& b) { return a.ptr != b.ptr; }
    friend bool operator!=(const Iterator& a, const scalar_type* ptr) { return a.ptr != ptr; }

   private:
    scalar_type* ptr = nullptr;
  };
  static_assert(std::input_iterator<Iterator>);

  using iterator = Iterator;

  iterator begin() { return start_; }
  scalar_type* end() { return start_ + size_; }
  size_t size() const { return size_ / lanes; }

  template <std::ranges::contiguous_range R>
  vectorize_ptr(R&& r) : start_{&*std::ranges::begin(r)}, size_{vectorizeable_size(std::ranges::size(r))} {}

 private:
  scalar_type* start_;
  size_t size_;
};
template <std::ranges::contiguous_range R>
vectorize_ptr(R&& r) -> vectorize_ptr<std::ranges::range_value_t<R>>;

static_assert(std::ranges::range<vectorize_ptr<int32_t>>);
static_assert(std::ranges::view<vectorize_ptr<int32_t>>);
static_assert(std::movable<vectorize_ptr<int32_t>>);
static_assert(std::ranges::viewable_range<vectorize_ptr<int32_t>>);

}  // namespace argon
#undef simd
