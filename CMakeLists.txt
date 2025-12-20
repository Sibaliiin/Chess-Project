cmake_minimum_required(VERSION 3.10)

project(p C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(p
	src/main.c
)
