
add_library("game" OBJECT
  game.cpp
)

add_executable(tic_tac_toe
  main.cpp
  $<TARGET_OBJECTS:game>
)

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

add_executable("game_test_driver"
  tests.cpp
  $<TARGET_OBJECTS:game>
)

target_link_libraries("game_test_driver"
  ${LIBCHECK_LIBRARY}
)

add_test("game_tests" game_test_driver)

