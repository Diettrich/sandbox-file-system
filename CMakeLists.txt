cmake_minimum_required(VERSION 3.26)
project(File_System__MSIP C)

set(CMAKE_C_STANDARD 11)

set(SOURCES src/main.c
        src/shell.c
        src/commands.c
)
set(HEADER_FILES
        headers/shell.h
        headers/commands.h
)


add_executable(File_System__MSIP ${SOURCES} ${HEADER_FILES})

target_include_directories(File_System__MSIP PUBLIC headers/)
