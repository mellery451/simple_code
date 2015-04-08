
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

include(LibFindMacros)
# Use pkg-config to get hints about paths
libfind_pkg_check_modules(LIBCHECK_PKGCONF check)
find_path(LIBCHECK_INCLUDE_DIR
    NAMES check.h
    PATHS ${LIBCHECK_PKGCONF_INCLUDE_DIRS}
)
find_library(LIBCHECK_LIBRARY
    NAMES check
    PATHS ${LIBCHECK_PKGCONF_LIBRARY_DIRS}
)

include_directories( ${LIBCHECK_INCLUDE_DIR} )

add_executable("test_driver"
  tests/main.cpp
)

target_link_libraries("test_driver" 
  "tree_thing"
  ${LIBCHECK_LIBRARY}
)

add_test("unit_tests" test_driver)


