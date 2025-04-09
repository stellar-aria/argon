
if(ARGON_TEST_CPU STREQUAL "A9")
  message(STATUS "Building for Cortex-A9")
  set(CPU_OPTIONS
    -mcpu=cortex-a9
    -mfloat-abi=hard
    -mfpu=neon
  )
  add_compile_options(${CPU_OPTIONS} -Wno-psabi -static)
  add_link_options(${CPU_OPTIONS})
elseif(ARGON_TEST_CPU STREQUAL "M55")
  message(STATUS "Building for Cortex-M55")
  set(CPU_OPTIONS
    -mcpu=cortex-m55
    -mfloat-abi=hard
  )
  add_compile_options(${CPU_OPTIONS} -Wno-psabi -static)
  add_link_options(${CPU_OPTIONS})
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
