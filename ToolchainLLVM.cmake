set(CMAKE_SYSTEM_NAME               Generic)
set(CMAKE_SYSTEM_PROCESSOR          ARM)

if(WIN32)
  set(TOOLCHAIN_EXT ".exe" )
else()
  set(TOOLCHAIN_EXT "" )
endif(WIN32)

cmake_path(SET ARM_TOOLCHAIN_ROOT LLVMEmbeddedToolchainForArm/)
cmake_path(ABSOLUTE_PATH ARM_TOOLCHAIN_ROOT)

set(ARCH_COMBO armv7a_hard_neon)
set(CLANG_TARGET_TRIPLE armv7a-none-eabihf)

cmake_path(SET CMAKE_SYSROOT ${ARM_TOOLCHAIN_ROOT}/lib/clang-runtimes/arm-none-eabi/${ARCH_COMBO})
#cmake_path(SET CMAKE_FIND_ROOT_PATH ${ARM_TOOLCHAIN_ROOT}/lib/clang-runtimes/arm-none-eabi/${ARCH_COMBO})
cmake_path(SET ARM_TOOLCHAIN_BIN_PATH ${ARM_TOOLCHAIN_ROOT}/bin)

# Without that flag CMake is not able to pass test compilation check
set(CMAKE_TRY_COMPILE_TARGET_TYPE   STATIC_LIBRARY)

set(CMAKE_AR           ${ARM_TOOLCHAIN_BIN_PATH}/llvm-ar${TOOLCHAIN_EXT} CACHE FILEPATH "Path to archiver.")
set(CMAKE_ASM_COMPILER ${ARM_TOOLCHAIN_BIN_PATH}/clang${TOOLCHAIN_EXT} CACHE FILEPATH "Path to ASM compiler.")
set(CMAKE_C_COMPILER   ${ARM_TOOLCHAIN_BIN_PATH}/clang${TOOLCHAIN_EXT} CACHE FILEPATH "Path to C Compiler.")
set(CMAKE_CXX_COMPILER ${ARM_TOOLCHAIN_BIN_PATH}/clang++${TOOLCHAIN_EXT} CACHE FILEPATH "Path to C++ Compiler.")
set(CMAKE_LINKER       ${ARM_TOOLCHAIN_BIN_PATH}/lld${TOOLCHAIN_EXT} CACHE FILEPATH "Path to linker.")
set(CMAKE_OBJCOPY      ${ARM_TOOLCHAIN_BIN_PATH}/llvm-objcopy${TOOLCHAIN_EXT} CACHE FILEPATH "Path to objcopy.")
set(CMAKE_RANLIB       ${ARM_TOOLCHAIN_BIN_PATH}/llvm-ranlib${TOOLCHAIN_EXT} CACHE FILEPATH "Path to ranlib.")
set(CMAKE_SIZE         ${ARM_TOOLCHAIN_BIN_PATH}/llvm-size${TOOLCHAIN_EXT} CACHE FILEPATH "Path to size.")
set(CMAKE_STRIP        ${ARM_TOOLCHAIN_BIN_PATH}/llvm-strip${TOOLCHAIN_EXT} CACHE FILEPATH "Path to strip.")


set(CMAKE_C_COMPILER_TARGET ${CLANG_TARGET_TRIPLE})
set(CMAKE_CXX_COMPILER_TARGET ${CLANG_TARGET_TRIPLE})
set(CMAKE_ASM_COMPILER_TARGET ${CLANG_TARGET_TRIPLE})

set(CMAKE_ASM_FLAGS_RELEASE "-O2 -DNDEBUG" CACHE STRING "Flags used by the ASM compiler during RELEASE builds." FORCE)
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG" CACHE STRING "Flags used by the C compiler during RELEASE builds."   FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG" CACHE STRING "Flags used by the C++ compiler during RELEASE builds."  FORCE)

# Architecture
set(ARCH_FLAGS
  -mcpu=cortex-a9
  -mfpu=neon
  -mfloat-abi=hard
  -marm
#  -mthumb-interwork
  -mlittle-endian
)
add_compile_options(${ARCH_FLAGS})
add_link_options(${ARCH_FLAGS})

add_compile_options(
  -fmessage-length=0
)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)