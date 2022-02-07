cmake_minimum_required(VERSION 3.20)
project(algorithm)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DLOCAL)
MATH(EXPR stack_size "102400000")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

add_executable(tmp tmp.cpp)


add_executable(A codeforces/contest/edu/122/A.cpp)
add_executable(B codeforces/contest/edu/122/B.cpp)
add_executable(C codeforces/contest/edu/122/C.cpp)
add_executable(D codeforces/contest/round/768/D.cpp)

add_executable(E codeforces/contest/edu/122/E.cpp)
add_executable(acwing_1801 acwing/practice/winter_daily_2022/week_4/acwing_1801.cpp)
add_executable(acwing_1789 acwing/practice/winter_daily_2022/week_5/acwing_1789.cpp)
add_executable(acwing_1738 acwing/practice/winter_daily_2022/week_5/acwing_1738.cpp)
add_executable(acwing_1750 acwing/practice/winter_daily_2022/week_5/acwing_1750.cpp)
add_executable(acwing_1776 acwing/practice/winter_daily_2022/week_5/acwing_1776.cpp)
add_executable(acwing_1762 acwing/practice/winter_daily_2022/week_5/acwing_1762.cpp)
add_executable(acwing_1049 acwing/improvement_course/1_dp/1.4_state_machine/acwing_1049.cpp)
add_executable(acwing_1057 acwing/improvement_course/1_dp/1.4_state_machine/acwing_1057.cpp)
add_executable(acwing_1058 acwing/improvement_course/1_dp/1.4_state_machine/acwing_1058.cpp)