
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

add_executable("hash_tests_driver"
  tests.cpp
)

target_link_libraries("hash_tests_driver"
  ${LIBCHECK_LIBRARY}
)

add_test("hash_tests" hash_tests_driver)

