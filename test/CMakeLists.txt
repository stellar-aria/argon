
if(ARGON_TEST_QEMU)
  message(STATUS "QEMU testing enabled")
  set(CPU_OPTIONS
  -mcpu=cortex-a9
  -mfloat-abi=hard
  -mfpu=neon
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
target_compile_options(simde INTERFACE -Wno-macro-redefined)

enable_testing()
add_subdirectory(specs)
include(CTest)
