cmake_minimum_required(VERSION 3.20)
project(algorithm)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DLOCAL)
MATH(EXPR stack_size "102400000")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

add_executable(tmp tmp.cpp)

add_executable(acwing_321 acwing/improvement_course/1_dp/1.6_interval/acwing_321.cpp)
add_executable(acwing_1072 acwing/improvement_course/1_dp/1.7_tree/acwing_1072.cpp)
add_executable(acwing_1073 acwing/improvement_course/1_dp/1.7_tree/acwing_1073.cpp)
add_executable(acwing_1075 acwing/improvement_course/1_dp/1.7_tree/acwing_1075.cpp)
add_executable(acwing_1074 acwing/improvement_course/1_dp/1.7_tree/acwing_1074.cpp)
add_executable(acwing_10 acwing/improvement_course/1_dp/1.3_knapsack/acwing_10.cpp)
add_executable(acwing_323 acwing/improvement_course/1_dp/1.7_tree/acwing_323.cpp)
add_executable(acwing_1077 acwing/improvement_course/1_dp/1.7_tree/acwing_1077.cpp)