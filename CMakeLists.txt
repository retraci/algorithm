cmake_minimum_required(VERSION 3.20)
project(algorithm)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DLOCAL)
MATH(EXPR stack_size "102400000")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

add_executable(tmp tmp.cpp)

add_executable(E dgut/contest/25/E.cpp)

add_executable(B codeforces/contest/round/770/B.cpp)
add_executable(acwing_831 acwing/base_course/2_data_structure/2.7_kmp/acwing_831.cpp)
add_executable(acwing_1052 acwing/improvement_course/1_dp/1.4_state_machine/acwing_1052.cpp)

add_executable(acwing_1064 acwing/improvement_course/1_dp/1.5_state_compression/acwing_1064.cpp)