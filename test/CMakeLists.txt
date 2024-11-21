add_executable(test EXCLUDE_FROM_ALL main.cpp)
target_link_libraries(test argon)

target_compile_options(test PUBLIC
  -O2
  -ggdb3
  $<$<CXX_COMPILER_ID:GCC>:-fpeel-loops>
  $<$<CXX_COMPILER_ID:GCC>:-fpredictive-commoning>
  $<$<CXX_COMPILER_ID:GCC>:-ftree-loop-distribution>
  -fno-tree-vectorize
  -save-temps
  -static
)

set_target_properties(test
  PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS YES
)

function(add_deploy target remote path)
  add_custom_target("deploy_${target}"
    DEPENDS "${target}"
    COMMAND scp "$<TARGET_FILE:${target}>" "${remote}:${path}"
    COMMAND ssh "${remote}" chmod 755 "${path}${target}"
    COMMAND ${CMAKE_COMMAND} -E echo "Deployed ${target} to ${remote}"
  )
endfunction()

add_deploy(test debian@beaglebone.local "~/")

include(FetchContent)
FetchContent_Declare(c++spec
  GIT_REPOSITORY https://github.com/toroidal-code/cppspec
  GIT_TAG main
)
FetchContent_MakeAvailable(c++spec)


link_libraries(argon)
discover_specs(spec)
