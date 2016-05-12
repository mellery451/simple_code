
add_library("game" OBJECT
  game.cpp
)

add_executable(tic_tac_toe
  main.cpp
  $<TARGET_OBJECTS:game>
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

