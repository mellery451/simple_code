
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

add_library("sum_bin"
  sum_bin.cpp
)

add_executable("sum_bin_test"
  test_main.cpp
)

target_link_libraries("sum_bin_test" 
  "sum_bin"
)

add_test("sum_bin_unit_tests" sum_bin_test)


