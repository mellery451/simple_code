
include_directories( ${LIBCHECK_INCLUDE_DIR} )

add_executable("bi_map"
  hw_01.cpp
)

add_executable("bi_map_tests"
  tests.cpp
)

target_link_libraries("bi_map_tests"
  ${LIBCHECK_LIBRARY}
)

add_test("bi_map_tests" bi_map_tests)
