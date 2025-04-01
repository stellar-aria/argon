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
