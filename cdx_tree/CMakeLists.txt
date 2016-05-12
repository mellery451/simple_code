
include_directories(
  src
)

add_library("tree_thing"
  src/tree_thing.cpp
)

add_executable(tree
  exe/tree.cpp
)

target_link_libraries("tree" "tree_thing")

include_directories( ${LIBCHECK_INCLUDE_DIR} )

add_executable("tree_test_driver"
  tests/main.cpp
)

target_link_libraries("tree_test_driver"
  "tree_thing"
  ${LIBCHECK_LIBRARY}
)

add_test("unit_tests" tree_test_driver)


