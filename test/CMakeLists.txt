
if(ARGON_TEST_CPU STREQUAL "A9")
  message(STATUS "Building for Cortex-A9")
  set(CPU_OPTIONS
    -mcpu=cortex-a9
    -mfloat-abi=hard
    -mfpu=neon
  )
  add_compile_options(${CPU_OPTIONS} -Wno-psabi -static)
  add_link_options(${CPU_OPTIONS})

  set(CMAKE_CROSSCOMPILING TRUE)
  set(CMAKE_CROSSCOMPILING_EMULATOR /usr/bin/qemu-arm;-L;/usr/arm-linux-gnueabihf;-cpu;cortex-a9)
  set(CPPSPEC_SPEC_RUNNER ${CMAKE_CROSSCOMPILING_EMULATOR})
elseif(ARGON_TEST_CPU STREQUAL "A7")
  message(STATUS "Building for Cortex-A7 (ARMv7, VFPv4 + NEON)")
  set(CPU_OPTIONS
    -mcpu=cortex-a7
    -mfloat-abi=hard
    -mfpu=neon-vfpv4
  )
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # GCC only exposes the float16 vector types on AArch32 with an explicit FP16 storage format
    list(APPEND CPU_OPTIONS -mfp16-format=ieee)
  endif()
  add_compile_options(${CPU_OPTIONS} -Wno-psabi -static)
  add_link_options(${CPU_OPTIONS})

  set(CMAKE_CROSSCOMPILING TRUE)
  set(CMAKE_CROSSCOMPILING_EMULATOR /usr/bin/qemu-arm;-L;/usr/arm-linux-gnueabihf;-cpu;cortex-a7)
  set(CPPSPEC_SPEC_RUNNER ${CMAKE_CROSSCOMPILING_EMULATOR})
elseif(ARGON_TEST_CPU STREQUAL "A55")
  message(STATUS "Building for Cortex-A55 (ARMv8, AArch64 NEON)")
  set(CPU_OPTIONS
    -mcpu=cortex-a55
  )
  if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # AArch64 has no float-ABI choice; GCC rejects the flag outright
    list(APPEND CPU_OPTIONS -mfloat-abi=hard)
  endif()
  add_compile_options(${CPU_OPTIONS} -Wno-psabi -static)
  add_link_options(${CPU_OPTIONS})

  set(CMAKE_CROSSCOMPILING TRUE)
  # the specs link dynamically: point qemu at the AArch64 sysroot
  set(CMAKE_CROSSCOMPILING_EMULATOR /usr/bin/qemu-aarch64;-L;/usr/aarch64-linux-gnu;-cpu;cortex-a55)
  set(CPPSPEC_SPEC_RUNNER ${CMAKE_CROSSCOMPILING_EMULATOR})
elseif(ARGON_TEST_CPU STREQUAL "M55")
  set(CPU_OPTIONS
    -mcpu=cortex-m55
    -mfloat-abi=hard
  )
  add_compile_options(${CPU_OPTIONS} -Wno-psabi -static -specs=rdimon.specs)
  add_link_options(${CPU_OPTIONS} -specs=rdimon.specs)

  message(STATUS "Building for Cortex-M55")
  set(CMAKE_CROSSCOMPILING TRUE)
  set(CMAKE_CROSSCOMPILING_EMULATOR /usr/bin/qemu-arm -cpu cortex-m55)
  add_compile_options(${CPU_OPTIONS} -Wno-psabi)
  add_compile_definitions(CPPSPEC_SEMIHOSTED=1)
  set(CPPSPEC_SPEC_RUNNER ${CMAKE_CROSSCOMPILING_EMULATOR})

  # qemu-system-arm -cpu cortex-m55 -machine mps3-an547 -nographic -monitor none -serial none -semihosting -semihosting-config enable=on,target=native -kernel .\gather_spec
elseif(ARGON_TEST_CPU STREQUAL "SIMDe" OR NOT ARGON_TEST_CPU)
  message(STATUS "Building for host (SIMDe fallback)")
endif()

include(FetchContent)
FetchContent_Declare(
  simde
  GIT_REPOSITORY https://github.com/simd-everywhere/simde
  GIT_TAG v0.8.2
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(simde)

add_library(simde INTERFACE ${simde_SOURCE_DIR}/simde)
target_include_directories(simde INTERFACE ${simde_SOURCE_DIR}/simde)

if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(simde INTERFACE -Wno-macro-redefined)
endif()

add_subdirectory(specs)

# AArch32: every Argon<float> operation must stay on NEON (GCC scalarises float vector extensions there).
if(ARGON_TEST_CPU STREQUAL "A9" OR ARGON_TEST_CPU STREQUAL "A7")
  add_library(argon_float_codegen OBJECT codegen/float_ops.cpp)
  target_link_libraries(argon_float_codegen PRIVATE argon)
  target_compile_options(argon_float_codegen PRIVATE -O2)
  find_program(ARGON_ARM_OBJDUMP NAMES arm-linux-gnueabihf-objdump llvm-objdump REQUIRED)
  add_test(NAME float_ops_use_neon
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/codegen/check_neon_float.sh ${ARGON_ARM_OBJDUMP} $<TARGET_OBJECTS:argon_float_codegen>)

  # The partial step of for_each, for_each_interleaved and the with_tail() views must branch on its scalar lane count:
  # no NEON-to-core lane transfers (vmov r, d[k]), which stall the A9 and A7 pipelines.
  add_library(argon_neon_tail_codegen OBJECT codegen/neon_tail_loops.cpp)
  target_link_libraries(argon_neon_tail_codegen PRIVATE argon)
  target_compile_options(argon_neon_tail_codegen PRIVATE -O2)
  add_test(NAME tail_loops_stay_on_neon
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/codegen/check_neon_tail.sh ${ARGON_ARM_OBJDUMP} $<TARGET_OBJECTS:argon_neon_tail_codegen>)
endif()

# Helium: with_tail() views and FirstN loops must compile to low-overhead tail-predicated loops (dlstp/letp).
if(ARGON_TEST_CPU STREQUAL "M55")
  add_library(argon_tail_codegen OBJECT codegen/tail_loops.cpp)
  target_link_libraries(argon_tail_codegen PRIVATE argon)
  target_compile_options(argon_tail_codegen PRIVATE -O2 -fno-trapping-math)
  find_program(ARGON_ARM_NONE_OBJDUMP NAMES arm-none-eabi-objdump llvm-objdump REQUIRED)
  add_test(NAME tail_loops_use_dlstp
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/codegen/check_mve_tail.sh ${ARGON_ARM_NONE_OBJDUMP} $<TARGET_OBJECTS:argon_tail_codegen>)

  # Float Max/Min and MultiplyAdd/MultiplySubtract must stay on Helium, fused, without -ffast-math.
  add_library(argon_mve_float_codegen OBJECT codegen/mve_float_ops.cpp)
  target_link_libraries(argon_mve_float_codegen PRIVATE argon)
  target_compile_options(argon_mve_float_codegen PRIVATE -O2)
  add_test(NAME float_ops_use_mve
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/codegen/check_mve_float.sh ${ARGON_ARM_NONE_OBJDUMP} $<TARGET_OBJECTS:argon_mve_float_codegen>)
endif()
