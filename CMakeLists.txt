cmake_minimum_required(VERSION 3.26)
project(sandbox_file_system C)

set(CMAKE_C_STANDARD 11)

set(SOURCES src/main.c
        src/shell.c
        src/commands.c
        src/file_node.c
        src/commands_helper.c
        src/path.c
        src/utils.c
        src/file_path_utils.c
)
set(HEADER_FILES
        headers/shell.h
        headers/commands.h
        headers/file_node.h
        headers/commands_helper.h
        headers/path.h
        headers/utils.h
        headers/file_path_utils.h
)


add_executable(sandbox_file_system ${SOURCES} ${HEADER_FILES})

target_include_directories(sandbox_file_system PUBLIC headers/)
