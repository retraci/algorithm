cmake_minimum_required(VERSION 3.20)
project(algorithm)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DLOCAL)
MATH(EXPR stack_size "204800000")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

add_executable(tmp tmp.cpp)

add_executable(compiler luogu/practice/dp/knapsack/P3188.cpp)
