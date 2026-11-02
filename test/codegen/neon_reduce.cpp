// Across-lane reductions on AArch32 NEON: check_neon_reduce.sh holds each reduce_* function to the d-register fold
// (vadd/vmax/vmin of the halves, then vpadd/vpmax/vpmin), with no q-register lane shuffle, no trip through memory and
// no call.
#include "argon.hpp"

extern "C" {
int32_t reduce_add_s32(int32x4_t v) { return Argon<int32_t>{v}.ReduceAdd(); }
int16_t reduce_add_s16(int16x8_t v) { return Argon<int16_t>{v}.ReduceAdd(); }
uint8_t reduce_add_u8(uint8x16_t v) { return Argon<uint8_t>{v}.ReduceAdd(); }
float reduce_add_f32(float32x4_t v) { return Argon<float>{v}.ReduceAdd(); }
int32_t reduce_max_s32(int32x4_t v) { return Argon<int32_t>{v}.ReduceMax(); }
uint16_t reduce_max_u16(uint16x8_t v) { return Argon<uint16_t>{v}.ReduceMax(); }
float reduce_max_f32(float32x4_t v) { return Argon<float>{v}.ReduceMax(); }
int32_t reduce_min_s32(int32x4_t v) { return Argon<int32_t>{v}.ReduceMin(); }
int8_t reduce_min_s8(int8x16_t v) { return Argon<int8_t>{v}.ReduceMin(); }
float reduce_min_f32(float32x4_t v) { return Argon<float>{v}.ReduceMin(); }
}
