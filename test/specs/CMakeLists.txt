include(FetchContent)
FetchContent_Declare(c++spec
  GIT_REPOSITORY https://github.com/toroidal-code/cppspec
  GIT_TAG ddf0f86196d017750ad20d766d7de2c140d6df65
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(c++spec)

link_libraries(argon)
link_libraries(simde)

discover_specs(${CMAKE_CURRENT_SOURCE_DIR} TRUE)
