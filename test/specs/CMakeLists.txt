include(FetchContent)
FetchContent_Declare(c++spec
  GIT_REPOSITORY https://github.com/toroidal-code/cppspec
  GIT_TAG e469c35c9c3398eff5b6de390ae0998f25198fe1  # v1.0.2
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(c++spec)

link_libraries(argon)
link_libraries(simde)

discover_specs(${CMAKE_CURRENT_SOURCE_DIR} TRUE)
