include(FetchContent)
FetchContent_Declare(c++spec
  GIT_REPOSITORY https://github.com/toroidal-code/cppspec
  GIT_TAG develop
)
FetchContent_MakeAvailable(c++spec)

link_libraries(argon)
link_libraries(simde)

discover_specs(${CMAKE_CURRENT_SOURCE_DIR} TRUE)
