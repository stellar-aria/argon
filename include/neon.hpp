#include "neon/vfpv3.hpp"

#ifdef __ARM_FEATURE_FMA
#include "neon/vfpv4.hpp"
#endif

#if (__ARM_ARCH >= 8)  // ARMv8
// Always include A32
#include "neon/a32.hpp"

#ifdef __aarch64__  // A64
#include "neon/a64.hpp"
#endif  // __aarch64__
#endif  // __ARM_ARCH >= 8
