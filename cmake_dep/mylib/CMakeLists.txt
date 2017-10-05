
set(GENERATED_FILE ${CMAKE_CURRENT_BINARY_DIR}/inc/generated/generated_header.hpp)
get_filename_component(GENERATED_DIR ${GENERATED_FILE} DIRECTORY)

execute_process(COMMAND date OUTPUT_VARIABLE NOW OUTPUT_STRIP_TRAILING_WHITESPACE)

add_custom_command(
    OUTPUT ${GENERATED_FILE}
    COMMAND mkdir -p ${GENERATED_DIR}
    COMMAND echo "#define SOMETHING \"${NOW}\"" > ${GENERATED_FILE}
    COMMENT "making header file....${GENERATED_FILE}"
    VERBATIM)

add_custom_target(generate_src
    DEPENDS ${GENERATED_FILE})

add_library(mylib INTERFACE)
target_include_directories(mylib
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/inc ${CMAKE_CURRENT_BINARY_DIR}/inc)
add_dependencies(mylib generate_src)


