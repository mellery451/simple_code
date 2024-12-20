
project(simple_code)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} \
# -O3 \
# -foobar")

message(" == c flags == ${CMAKE_CXX_FLAGS}")
message(" == dc flags == ${CMAKE_CXX_FLAGS_DEBUG}")
message(" == rc flags == ${CMAKE_CXX_FLAGS_RELEASE}")
message(" == rwdi flags == ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
message(" == 1l flags == ${CMAKE_EXE_LINKER_FLAGS}")
message(" == d1l flags == ${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
message(" == r1l flags == ${CMAKE_EXE_LINKER_FLAGS_RELEASE}")
message(" == rwdil flags == ${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO}")
message(" == 2l flags == ${CMAKE_SHARED_LINKER_FLAGS}")
message(" == d2l flags == ${CMAKE_SHARED_LINKER_FLAGS_DEBUG}")
message(" == 3l flags == ${CMAKE_STATIC_LINKER_FLAGS}")
message(" == d3l flags == ${CMAKE_STATIC_LINKER_FLAGS_DEBUG}")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR};${CMAKE_MODULE_PATH}")

enable_testing()

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

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(cdx_tree)
add_subdirectory(sum_bin)

add_executable(misc misc.cpp)
add_executable(atoi atoi/atoi.cpp)
add_executable(dedup dedup/dedup.cpp)
add_executable(djb_hash djb_hash/hash.cpp)
add_executable(fib fib/fib.cpp)
add_executable(fizz_buzz fizz_buzz/fizz_buzz.cpp)
add_executable(get_my_ip get_my_ip/get_ip.cpp)
add_executable(hex_to hex_to/hex_to.cpp)
add_executable(rev_words rev_words/rev_words.cpp)
add_executable(ns_thing namespace_thing/test.cpp)
add_executable(simple_increment simple_increment.cpp)

set(CMAKE_CXX_STANDARD 11)
add_executable(ptr_access ptr_access.cpp)
add_executable(casting casting.cpp)
add_executable(class_and_method class_and_method.cpp)
add_executable(strange_cast strange_cast.cpp)
add_executable(merge_sorted merge_sorted.cpp)
add_executable(string_switch string_switch.cpp)
add_executable(max_sublist max_sublist/max_sublist.cpp)
add_executable(linked_list linked_list.cpp)

add_subdirectory(tic_tac_toe)
add_subdirectory(simple_hash_table)

add_subdirectory(bi_map)

add_subdirectory(cmake_dep)
