cmake_minimum_required(VERSION 3.27)
project(kutils C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

add_library(${PROJECT_NAME} STATIC
        stream.c
        error.c
        kutils.h
)

add_executable(${PROJECT_NAME}-tests
        tests.c
        stream.c
        error.c
        kutils.h
        error_tests.c
)
