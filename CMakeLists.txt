cmake_minimum_required(VERSION 3.25)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project(argon
  VERSION 0.1.0
  LANGUAGES CXX
)

add_library(argon INTERFACE)
target_include_directories(argon INTERFACE include)
target_compile_features(argon INTERFACE cxx_std_23)

file(GLOB_RECURSE sources_GLOB include/**/*.hpp)
target_sources(argon PUBLIC
  ${sources_GLOB}
)

option(ARGON_ENABLE_TESTING "Build Argon tests" OFF)

if(ARGON_ENABLE_TESTING)
  enable_testing()
  include(CTest)
  add_subdirectory(test)
endif(ARGON_ENABLE_TESTING)

if(ARGON_BUILD_DOCS)
  find_package(Doxygen
    OPTIONAL_COMPONENTS dot mscgen dia
  )

  if(DOXYGEN_FOUND)
    cmake_policy(SET CMP0135 NEW)
    include(FetchContent)

    FetchContent_Declare(doxygen-awesome-css
      URL https://github.com/jothepro/doxygen-awesome-css/archive/refs/tags/v2.3.1.tar.gz
    )
    FetchContent_MakeAvailable(doxygen-awesome-css)

    if(NOT ${DOXYGEN_HAVE_DOT})
      message(
        "Can't find GraphViz DOT tool for generating images."
        "Make sure it's on your PATH or install GraphViz")
    endif()

    set(DOXYGEN_PROJECT_NAME "Argon")
    set(DOXYGEN_RECURSIVE YES)
    set(DOXYGEN_EXAMPLE_RECURSIVE YES)

    set(DOXYGEN_NUM_PROC_THREADS ${HOST_NUM_CORES})

    # From doxygen-awesome
    set(DOXYGEN_GENERATE_TREEVIEW YES)
    set(DOXYGEN_DISABLE_INDEX NO)
    set(DOXYGEN_FULL_SIDEBAR NO)
    set(DOXYGEN_HTML_COLORSTYLE LIGHT)
    set(DOXYGEN_HTML_EXTRA_STYLESHEET "${doxygen-awesome-css_SOURCE_DIR}/doxygen-awesome.css")

    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)

    set(DOXYGEN_EXAMPLE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/examples")

    set(DOXYGEN_PREDEFINED
      \"ARGON_HAS_DWORD=1\"
      \"ARGON_HAS_HALF_FLOAT=1\"
      \"ARGON_HAS_DOUBLE_FLOAT=1\"
    )

    set(DOXYGEN_JAVADOC_AUTOBRIEF YES)

    file(GLOB markdown_SOURCES *.md)

    doxygen_add_docs(doxygen ${markdown_SOURCES} include docs)
  else(DOXYGEN_FOUND)
    message(WARNING
        "Doxygen needs to be installed to generate documentation."
        "Please install from https://github.com/doxygen/doxygen/releases")
  endif(DOXYGEN_FOUND)
endif()
