cmake_minimum_required(VERSION 3.1)
 
project(simple_code)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR};${CMAKE_MODULE_PATH}")

enable_testing()

add_subdirectory(atoi)
add_subdirectory(cdx_tree)
