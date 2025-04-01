# Argon

Argon is a library that provides a sane, zero-overhead C++ interface to ARM's NEON SIMD intrinsics.
It grew out of a desire to use C++ abstractions for vector intrinsics, without sacrificing expressiveness or specificity.
Most C++ vector libraries ([highway](https://github.com/google/highway), [xsimd](https://github.com/xtensor-stack/xsimd))
abstract away all platform uniqueness in favor of common denominators. When considering the use case of those libraries, namely
HPC or multi-platform portability, that's a strength. Unfortunately, when you're targeting a very specific subset of those architectures,
or you have one architecture that needs to be optimized above all others, such abstractions fall short.

This is where Argon was created to exist: A NEON-first, others-second zero-overhead abstraction library with modern constructs
and capabilities.

What Argon is not:
  - A library of commonly used algorithms optimized in NEON.
  - A write-once run-everywhere abstraction

What Argon is:
  - A low-level intrinsics abstraction layer with sane naming conventions and overloaded functions
  - Higher-level encapsulated vector object types built on that layer

