cmake_minimum_required(VERSION 3.26)

project(argon
  VERSION 0.1.0
  LANGUAGES CXX
)

add_library(argon INTERFACE)
target_include_directories(argon INTERFACE include)
target_sources(argon PUBLIC 
  include/argon.hpp 
  include/neon.hpp 
  include/neon/helpers.hpp
)

add_subdirectory(test)