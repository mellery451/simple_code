
include_directories( ${LIBCHECK_INCLUDE_DIR} )

add_executable("hash_tests_driver"
  tests.cpp
)

target_link_libraries("hash_tests_driver"
  ${LIBCHECK_LIBRARY}
)

add_test("hash_tests" hash_tests_driver)

