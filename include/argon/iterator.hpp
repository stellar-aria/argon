#pragma once
#include "arm_simd/helpers/nonvec.hpp"

namespace argon {
template <typename intrinsic_type>
struct MainIterator {
  using scalar_type = simd::NonVec_t<intrinsic_type>;
  constexpr size_t lanes = sizeof(intrinsic_type) / sizeof(scalar_type);
  constexpr static scalar_type* vectorizeable_size(size_t size) { return size & ~(lanes - 1); }

 public:
  using iterator = scalar_type*;
  using const_iterator = const scalar_type*;

  MainIterator(scalar_type* start, size_t size) : store_(start), size_(vectorizeable_size(size)) {}
  MainIterator(const std::span<scalar_type> span) : store_(span.begin()), size_(vectorizeable_size(span.size())) {}
  MainIterator(scalar_type* start, scalar_type* end) : store_(start), size_(vectorizeable_size(end - start)) {}

  scalar_type operator*() { return *store_; }
  scalar_type& operator*() { return *store_; }
  void operator++() { store_ += lanes; }
  bool operator!=(MainIterator<intrinsic_type>& o) { return store_ != o.store_; }

  iterator begin() { return &store_[0]; }
  const_iterator cbegin() const { return &store_[0]; }
  iterator end() { return &store_[size_]; }
  const_iterator cend() const { return &store_[size_]; }

 private:
  T* store_;
  size_t size_;
};

template <typename intrinsic_type>
struct TailIterator {
  using scalar_type = simd::NonVec_t<intrinsic_type>;
  constexpr size_t lanes = sizeof(intrinsic_type) / sizeof(scalar_type);
  constexpr static scalar_type* vectorizeable_size(size_t size) { return size & ~(lanes - 1); }

 public:
  using iterator = scalar_type*;
  using const_iterator = const scalar_type*;

  TailIterator(scalar_type* start, size_t size) : store_(num_vectors(start)), size_(tail_size(size)) {}
  TailIterator(const std::span<scalar_type> span) : store_(size(span.begin())), size_(span.end()) {}
  TailIterator(scalar_type* start, scalar_type* end) : store_(size(start)), size_((end-start)) {}

  scalar_type operator*() { return *store_; }
  scalar_type& operator*() { return *store_; }
  void operator++() { store_ += 1; }
  bool operator!=(TailIterator<intrinsic_type>& o) { return store_ != o.store_; }

  iterator begin() { return &store_[0]; }
  const_iterator cbegin() const { return &store_[0]; }
  iterator end() { return &store_[size]; }
  const_iterator cend() const { return &store_[size]; }

 private:
  T* store_;
  size_t size_;
};
}  // namespace argon