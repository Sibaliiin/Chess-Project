cmake_minimum_required(VERSION 3.10)

project(chess C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(program main.c)

target_compile_options(program PRIVATE
    -Wall
    -Wextra
)
