cmake_minimum_required(VERSION 3.20)
project(algorithm)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DLOCAL)

add_executable(tmp tmp.cpp)
add_executable(D "codeforces/contest/educational codeforces round/120/D.cpp")
add_executable(E "codeforces/contest/Hello 2022/E.cpp")
