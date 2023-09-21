cmake_minimum_required(VERSION 3.26)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/ToolchainGNU.cmake)

project(argon)

add_executable(argon main.cpp)

target_compile_options(argon PUBLIC 
    -Og
    -g
)

set_target_properties(argon 
  PROPERTIES 
    CXX_STANDARD 23 
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS YES
)