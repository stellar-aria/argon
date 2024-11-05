add_executable(test EXCLUDE_FROM_ALL main.cpp)
target_link_libraries(test argon)

target_compile_options(test PUBLIC
  -O2
  -funsafe-math-optimizations
)

set_target_properties(test
  PROPERTIES
    CXX_STANDARD 20
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
