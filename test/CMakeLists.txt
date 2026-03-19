
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
elseif(ARGON_TEST_CPU STREQUAL "A55")
  message(STATUS "Building for Cortex-A55 (ARMv8, AArch64 NEON)")
  set(CPU_OPTIONS
    -mcpu=cortex-a55
    -mfloat-abi=hard
  )
  add_compile_options(${CPU_OPTIONS} -Wno-psabi -static)
  add_link_options(${CPU_OPTIONS})

  set(CMAKE_CROSSCOMPILING TRUE)
  set(CMAKE_CROSSCOMPILING_EMULATOR /usr/bin/qemu-aarch64 -cpu cortex-a55)
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
  add_compile_definitions(SIMDE_ENABLE_NATIVE_ALIASES)
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
