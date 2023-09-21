#include "argon.hpp"
#include <algorithm>
#include <array>
#include <ranges>
#include <numeric>

// // This is from SSE2NEON (MIT license)
// // reduces an 8 x 16 vector to 16 bits representing the state of its input lanes
// // (great for masked comparisons where lanes are 0xFF or 0x00!)
// uint16_t movemask(uint8x16_t input) {
//   uint16x8_t high_bits = vreinterpretq_u16_u8(vshrq_n_u8(input, 7));
//   uint32x4_t paired16 = vreinterpretq_u32_u16(vsraq_n_u16(high_bits, high_bits, 7));
//   uint64x2_t paired32 = vreinterpretq_u64_u32(vsraq_n_u32(paired16, paired16, 14));
//   uint8x16_t paired64 = vreinterpretq_u8_u64(vsraq_n_u64(paired32, paired32, 28));
//   return vgetq_lane_u8(paired64, 0) | ((uint16_t)vgetq_lane_u8(paired64, 8) << 8);
// }

// uint16_t movemask_neon(uint8x16_t input) {
//   auto high_bits = neon::reinterpret<uint16x8_t>(neon::shift_right<7>(input));
//   auto paired16 = neon::reinterpret<uint32x4_t>(neon::shift_right_accumulate<7>(high_bits, high_bits));
//   auto paired32 = neon::reinterpret<uint64x2_t>(neon::shift_right_accumulate<14>(paired16, paired16));
//   auto paired64 = neon::reinterpret<uint8x16_t>(neon::shift_right_accumulate<28>(paired32, paired32));
//   return neon::get<0>(paired64) | (static_cast<uint16_t>(neon::get<8>(paired64)) << 8);
// }

// uint16_t movemask_argon(argon::uint8_q input) {
//   using namespace argon;
//   auto high_bits = reinterpret<uint16_q>(input.ShiftRight<7>());
//   auto paired16 = reinterpret<uint32_q>(high_bits.ShiftRightAccumulate<7>(high_bits));
//   auto paired32 = reinterpret<uint64_q>(paired16.ShiftRightAccumulate<14>(paired16));
//   auto paired64 = reinterpret<uint8_q>(paired32.ShiftRightAccumulate<28>(paired32));
//   return paired64[0] | (static_cast<uint16_t>(paired64[8]) << 8);
// }

// // Rotates an 8x8 bitmap (as a 64bit pack) to the right 90degrees
// uint64_t bitmap_rotr_90(uint64_t x) {
//   // Output order should be 87654321
//   constexpr uint8x16_t mask_hi_2{
//       0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,  //< bitmask for eighth bit
//       0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,  //< bitmask for seventh bit
//   };
//   constexpr uint8x16_t mask_hi_1{
//       0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,  //< bitmask for sixth bit
//       0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,  //< bitmask for fifth bit
//   };
//   constexpr uint8x16_t mask_lo_2{
//       0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,  //< bitmask for fourth bit
//       0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,  //< bitmask for third bit
//   };
//   constexpr uint8x16_t mask_lo_1{
//       0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,  //< bitmask for second bit
//       0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,  //< bitmask for first bit
//   };

//   uint64x2_t x_v1 = vdupq_n_u64(x);              // load our input into both lanes
//   uint8x16_t x_u8 = vreinterpretq_u8_u64(x_v1);  // nop

//   // bitmasking: byte & (1 << x)
//   uint8x16_t r_hi_2 = vandq_u8(x_u8, mask_hi_2);  // bits 8 and 7
//   uint8x16_t r_hi_1 = vandq_u8(x_u8, mask_hi_1);  // bits 6 and 5
//   uint8x16_t r_lo_2 = vandq_u8(x_u8, mask_lo_2);  // bits 4 and 3
//   uint8x16_t r_lo_1 = vandq_u8(x_u8, mask_lo_1);  // bits 2 and 1

//   // comparison: byte == (1 << x)
//   // this is necessary as it sets the contents of each lane to either 0xFF or
//   // 0x00
//   r_hi_2 = vceqq_u8(r_hi_2, mask_hi_2);  // [8, 7]
//   r_hi_1 = vceqq_u8(r_hi_1, mask_hi_1);  // [6, 5]
//   r_lo_2 = vceqq_u8(r_lo_2, mask_lo_2);  // [4, 3]
//   r_lo_1 = vceqq_u8(r_lo_1, mask_lo_1);  // [2, 1]

//   // extract the masks (i.e. the results of each lane's comparison and combine
//   // them into a single uin16_t)
//   uint64_t t_hi_2 = static_cast<uint64_t>(movemask(r_hi_2));        // upper 16 bits of top 32 bits of output    [8, 7]
//   uint64_t t_hi_1 = static_cast<uint64_t>(movemask_neon(r_hi_1));   // lower 16 bits of top 32 bits of output    [6, 5]
//   uint64_t t_lo_2 = static_cast<uint64_t>(movemask_argon(r_lo_2));  // upper 16 bits of bottom 32 bits of output [4, 3]
//   uint64_t t_lo_1 = static_cast<uint64_t>(movemask(r_lo_1));        // lower 16 bits of bottom 32 bits of output [2, 1]

//   return (t_hi_2 << 48) | (t_hi_1 << 32) | (t_lo_2 << 16) | (t_lo_1 << 0);
// }

#include <iostream>

int main(void) {
  printf("Hello World!");
  // using namespace argon;
  // std::array<uint8_t, 64> array;
  // std::iota(array.begin(), array.end(), 0);

  // for (auto *it = array.begin(); it < array.end(); it += Neon64<uint8_t>::lanes) {
  //   Neon64<uint8_t> vec = Neon64<uint8_t>::Load(it);
  //   vec += 1;
  //   for (size_t i = 0; i < decltype(vec)::lanes; ++i) {
  //     std::cout << vec[i] << std::endl;
  //   }
  // }
  
  while (true) { 
    ; 
  }
}