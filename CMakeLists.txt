cmake_minimum_required(VERSION 3.26)
project(sandbox_file_system C)

set(CMAKE_C_STANDARD 11)

set(SOURCES src/main.c
        src/shell.c
        src/commands.c
)
set(HEADER_FILES
        headers/shell.h
        headers/commands.h
)


add_executable(sandbox_file_system ${SOURCES} ${HEADER_FILES})

target_include_directories(sandbox_file_system PUBLIC headers/)
