cmake_minimum_required(VERSION 3.20)
project(algorithm)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DLOCAL)

add_executable(tmp tmp.cpp)
add_executable(D "codeforces/contest/educational codeforces round/120/D.cpp")
add_executable(E "codeforces/contest/Hello 2022/E.cpp")

add_executable(acwing_2060 acwing/other/acwing_2060.cpp)
add_executable(acwing_2019 acwing/other/acwing_2019.cpp)
add_executable(acwing_190 "bluebook/0x20 searching/0x29 summary & practice/acwing_190.cpp")
add_executable(acwing_191 "bluebook/0x20 searching/0x29 summary & practice/acwing_191.cpp")