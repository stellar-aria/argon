#pragma once
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <ranges>
#include <span>
#include "argon.hpp"
#include "argon/vectorize/tail.hpp"
#include "arm_simd/helpers/vec128.hpp"

#ifdef __ARM_FEATURE_MVE
#define simd mve
#else
#define simd neon
#endif

namespace argon::vectorize {

template <size_t Stride, typename ScalarType>
struct interleaved : public std::ranges::view_interface<interleaved<Stride, ScalarType>> {
  using intrinsic_type = simd::Vec128_t<ScalarType>;
  static constexpr size_t lanes = sizeof(intrinsic_type) / sizeof(ScalarType);
  // Round down to a whole number of iterations; each iteration spans lanes*Stride elements.
  static constexpr size_t vectorizeable_size(size_t size) { return size - (size % (lanes * Stride)); }

 public:
  struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using argon_type = Argon<ScalarType>;
    using value_type = std::array<argon_type, Stride>;
    using difference_type = std::ptrdiff_t;

    Iterator() = default;
    Iterator(ScalarType* ptr) : ptr{ptr} {}

    value_type& operator*() {
      load();
      dirty_ = true;
      return vec;
    }
    value_type* operator->() { return &**this; }
    const value_type& operator*() const {
      load();
      return vec;
    }
    const value_type* operator->() const { return &**this; }
    Iterator& operator++() {
      if (dirty_) {
        argon::store_interleaved(ptr, vec);  // store before increment
      }
      ptr += lanes * Stride;
      loaded_ = dirty_ = false;  // load lazily: the end position is never read
      return *this;
    }

    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    friend bool operator==(const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; }
    friend bool operator==(const Iterator& a, const ScalarType* ptr) { return a.ptr == ptr; }
    friend bool operator!=(const Iterator& a, const Iterator& b) { return a.ptr != b.ptr; }
    friend bool operator!=(const Iterator& a, const ScalarType* ptr) { return a.ptr != ptr; }

   private:
    void load() const {
      if (!loaded_) {
        vec = argon_type::template LoadInterleaved<Stride>(ptr);
        loaded_ = true;
      }
    }

    ScalarType* ptr = nullptr;
    mutable value_type vec;
    mutable bool loaded_ = false;
    bool dirty_ = false;
  };
  static_assert(std::input_or_output_iterator<Iterator>);
  struct ConstIterator {
    using iterator_category = std::forward_iterator_tag;
    using argon_type = Argon<ScalarType>;
    using value_type = std::array<argon_type, Stride>;
    using difference_type = std::ptrdiff_t;

    ConstIterator() = default;
    ConstIterator(const ScalarType* ptr) : ptr{ptr} {}

    const value_type operator*() const { return argon_type::template LoadInterleaved<Stride>(ptr); }
    ConstIterator& operator++() {
      ptr += lanes * Stride;
      return *this;
    }
    ConstIterator operator++(int) {
      ConstIterator tmp = *this;
      ++(*this);
      return tmp;
    }
    friend bool operator==(const ConstIterator& a, const ConstIterator& b) { return a.ptr == b.ptr; }
    friend bool operator!=(const ConstIterator& a, const ConstIterator& b) { return a.ptr != b.ptr; }
    friend bool operator==(const ConstIterator& a, const ScalarType* ptr) { return a.ptr == ptr; }

   private:
    const ScalarType* ptr = nullptr;
  };
  static_assert(std::input_iterator<ConstIterator>);

  using iterator = Iterator;
  using const_iterator = ConstIterator;

  interleaved(ScalarType* start, ScalarType* end)
      : start_{start}, size_{vectorizeable_size(end - start)}, count_{static_cast<size_t>(end - start)} {};
  interleaved(ScalarType* start, const size_t size) : start_{start}, size_{vectorizeable_size(size)}, count_{size} {};
  interleaved(const std::span<ScalarType> span)
      : start_{span.data()}, size_{vectorizeable_size(span.size())}, count_{span.size()} {};

  iterator begin() const { return Iterator(start_); }
  const ScalarType* end() const { return start_ + size_; }
  const_iterator cbegin() const { return ConstIterator(start_); }
  const ScalarType* cend() const { return start_ + size_; }
  /// @brief The number of iterations (groups of Stride vectors).
  size_t size() const { return size_ / (lanes * Stride); }

  /// @brief A view of the same range that also visits the final, partial group of vectors.
  /// @details This view skips frames after the last whole group; with_tail() visits them too. Each element is a
  /// Partial whose value is one vector per channel; lanes past the end load as zero and are never stored. Elements
  /// that don't complete a frame of `Stride` are not visited.
  load_store_tail<ScalarType, Stride> with_tail() const { return {start_, count_ / Stride}; }

 private:
  ScalarType* start_;
  size_t size_;
  size_t count_;  ///< Number of elements in the range, including any after the last whole group.
};

// template <size_t stride, std::ranges::contiguous_range R>
// interleaved(R&& r) -> interleaved<stride, std::ranges::range_value_t<R>>;

// MSVC's ranges implementation does not accept this view as a std::ranges::range
// (it works on GCC and Clang). TODO: revisit MSVC support for the interleaved
// read-modify-write view; until then, skip the concept checks there.
#if !defined(_MSC_VER) || defined(__clang__)
static_assert(std::ranges::range<interleaved<3, int32_t>>);
static_assert(std::ranges::view<interleaved<3, int32_t>>);
static_assert(std::movable<interleaved<3, int32_t>>);
static_assert(std::ranges::viewable_range<interleaved<3, int32_t>>);
#endif

}  // namespace argon::vectorize

#undef simd
