# Vectorized Views

The Argon library provides several vectorized views for processing data using SIMD operations. These views work with contiguous ranges and provide iterator-based access to the vectorized data.

## Vectorized read (vectorize::load)

The `load` view presents a read-only view of a contiguous set of data (i.e. a `std::ranges::input_range`). `Load` is lazy, and occurs only on dereference (and on every dereference, as it is not memoized).

```cpp
#include <argon/vectorize/load.hpp>
#include <array>

int main() {
  std::array<int32_t, 512> data;
  data.fill(5);

  // Read data using SIMD loads
  for (auto vec : argon::vectorize::load(data)) {
      // Process loaded data
      // vec is loaded using SIMD load operations
  }
}
```

## Vectorized write (vectorize::store)

The `store` presents a write-only view of a contiguous set of data (i.e. a `std::ranges::output_range`). `StoreTo` is lazy, and occurs _only_ on incrementing or decrementing the iterator.

```cpp
#include <argon/vectorize/store.hpp>
#include <array>

int main() {
  std::array<int32_t, 512> data;
  data.fill(0);

  // Write data using SIMD stores
  for (auto& vec : argon::vectorize::store(data)) {
      vec = {1, 2, 3, 4}; // Values are stored using SIMD store operations
  }
}
```

## Vectorized In-place Read/Write (vectorize::load_store)

The `load_store` view allows you to process data in-place using SIMD operations. Internally,
a vector is stored in the iterator that is loaded on creation, and then stored on increment, before the next element is loaded. Dereferencing accesses the internal stored vector, and will not `Load` again without a manual `.reload()` call.

Note: If you do not need _both_ read _and_ write on the same range, use either `vectorize::load` or `vectorize::store` instead, as `vectorize::load_store` incurs the read latency and writeback penalty of them combined.

```cpp
#include <argon/vectorize.hpp>
#include <array>

int main() {
  std::array<int32_t, 512> data;
  data.fill(5);

  // Increment each element using SIMD operations
  for (auto& vec : argon::vectorize::load_store(data)) {
      vec = vec + 1;
  }
}
```

## Interleaved Data Access

For working with interleaved data (like RGB values), Argon provides specialized views:

### Loading Interleaved Data

```cpp
#include <argon/vectorize/load.hpp>
#include <array>

int main() {
  std::array<int32_t, 512> data; // Interleaved data (e.g. RGBRGBRGB...)

  // Load interleaved data with stride of 3 (RGB)
  for (auto [r, g, b] : argon::vectorize::load_interleaved<3>(data)) {
      // Process r, g, b vectors separately
  }
}
```

### Storing Interleaved Data

```cpp
#include <argon/vectorize/store.hpp>
#include <array>

int main() {
  std::array<int32_t, 512> data;

  // Store interleaved data with stride of 2
  for (auto& [even, odd] : argon::vectorize::store_interleaved<2>(data)) {
      even = {0, 2, 4, 6};  // Even indices
      odd = {1, 3, 5, 7};   // Odd indices
  }
}
```

## Key Features

- All views work with contiguous ranges (arrays, vectors, spans)
- Automatic alignment and size handling
- Efficient SIMD operations through Argon's SIMD wrappers
- Iterator-based interface compatible with C++ ranges
- Support for different data types (int32_t, float, etc.)

## Notes

1. The number of elements processed in each iteration depends on the SIMD vector size for the target architecture
2. Data size should ideally be aligned to the SIMD vector size
3. Non-aligned sizes are handled automatically (remaining elements are not processed)
4. Interleaved operations support strides of 2, 3, or 4

## Error Handling

The views handle common errors gracefully:

- Non-contiguous ranges: Will not compile
- Invalid strides: Static assertions prevent invalid stride values
- Misaligned sizes: Automatically handled by processing only aligned portions
