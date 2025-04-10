include(FetchContent)
FetchContent_Declare(c++spec
  GIT_REPOSITORY https://github.com/toroidal-code/cppspec
  GIT_TAG 34648866f54639afd305a65a5ca064af9bf843b3
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(c++spec)

link_libraries(argon)
link_libraries(simde)

discover_specs(${CMAKE_CURRENT_SOURCE_DIR} TRUE)
