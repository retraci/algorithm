cmake_minimum_required(VERSION 3.20)
project(algorithm)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DLOCAL)
MATH(EXPR stack_size "102400000")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

add_executable(tmp tmp.cpp)


add_executable(acwing_1884 acwing/practice/winter_daily_2022/week_3/acwing_1884.cpp)
add_executable(acwing_1875 acwing/practice/winter_daily_2022/week_4/acwing_1875.cpp)
add_executable(acwing_1855 acwing/practice/winter_daily_2022/week_4/acwing_1855.cpp)
add_executable(acwing_850 "acwing/practice/shortest path/acwing_850.cpp")
add_executable(acwing_1843 acwing/practice/winter_daily_2022/week_4/acwing_1843.cpp)
add_executable(acwing_1826 acwing/practice/winter_daily_2022/week_4/acwing_1826.cpp)
add_executable(acwing_1813 acwing/practice/winter_daily_2022/week_4/acwing_1813.cpp)
add_executable(A codeforces/contest/edu/122/A.cpp)
add_executable(B codeforces/contest/edu/122/B.cpp)
add_executable(C codeforces/contest/edu/122/C.cpp)
add_executable(D codeforces/contest/edu/122/D.cpp)