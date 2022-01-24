cmake_minimum_required(VERSION 3.20)
project(algorithm)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DLOCAL)
MATH(EXPR stack_size "102400000")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

add_executable(tmp tmp.cpp)

add_executable(C "codeforces/contest/round/#767 (Div. 2)/C.cpp")
add_executable(E atcoder/contest/abc/236/E.cpp)
add_executable(F1 "codeforces/contest/round/#767 (Div. 2)/F1.cpp")
add_executable(F2 "codeforces/contest/round/#767 (Div. 2)/F2.cpp")
