cmake_minimum_required(VERSION 3.1)
 
project(simple_code)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR};${CMAKE_MODULE_PATH}")

enable_testing()

add_subdirectory(cdx_tree)
add_subdirectory(sum_bin)

add_executable(atoi atoi/atoi.cpp)
add_executable(dedup dedup/dedup.cpp)
add_executable(djb_hash djb_hash/hash.cpp)
add_executable(fib fib/fib.cpp)
add_executable(fizz_buzz fizz_buzz/fizz_buzz.cpp)
add_executable(get_my_ip get_my_ip/get_ip.cpp)
add_executable(hex_to hex_to/hex_to.cpp)
add_executable(rev_words rev_words/rev_words.cpp)


