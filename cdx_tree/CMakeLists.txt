
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

# TODO add the unit test...
