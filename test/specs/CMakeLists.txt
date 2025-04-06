include(FetchContent)
FetchContent_Declare(c++spec
  GIT_REPOSITORY https://github.com/toroidal-code/cppspec
  GIT_TAG 6a5eaf6460dba160ced3232bbb7b3ce027f32d2f
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(c++spec)

link_libraries(argon)
link_libraries(simde)

discover_specs(${CMAKE_CURRENT_SOURCE_DIR} TRUE)
