include(FetchContent)
FetchContent_Declare(c++spec
  GIT_REPOSITORY https://github.com/toroidal-code/cppspec
  GIT_TAG main
)
FetchContent_MakeAvailable(c++spec)

link_libraries(argon)
link_libraries(simde)

function(create_specs_driver driver_name spec_dir)
  # Discover Specs
  file(GLOB_RECURSE spec_sources RELATIVE ${spec_dir} ${spec_dir}/*_spec.cpp)

  create_test_sourcelist(specs ${driver_name}.cpp ${spec_sources})
  add_executable(${driver_name} ${specs})
  target_link_libraries(${driver_name} PRIVATE c++spec)
  target_compile_options(${driver_name} PRIVATE -Wall -Wextra)
  set_target_properties(${driver_name} PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
  )

  foreach(spec IN LISTS spec_sources)
    cmake_path(GET spec STEM LAST_ONLY spec_name)
    string(REPLACE ".cpp" "" spec ${spec})
    add_test(
      NAME ${spec_name}
      COMMAND ${driver_name} ${spec} --verbose
    )
  endforeach()
endfunction()

create_specs_driver(all_specs ${CMAKE_CURRENT_SOURCE_DIR})
