cmake_minimum_required(VERSION 3.20)
project(algorithm)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DLOCAL)
MATH(EXPR stack_size "102400000")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

add_executable(tmp tmp.cpp)
add_executable(D "codeforces/contest/round/#765 (Div. 2)/D.cpp")
add_executable(E "codeforces/contest/round/#766 (Div. 2)/E.cpp")

add_executable(acwing_2060 "acwing/winter daily 2022/week 1/acwing_2060.cpp")
add_executable(acwing_2019 "acwing/winter daily 2022/week 1/acwing_2019.cpp")
add_executable(acwing_190 "acwing/bluebook/0x20 searching/0x29 summary & practice/acwing_190.cpp")
add_executable(acwing_191 "acwing/bluebook/0x20 searching/0x29 summary & practice/acwing_191.cpp")
add_executable(acwing_1015 "acwing/improvement course/1. dp/1.1 number triangle/acwing_1015.cpp")
add_executable(acwing_1018 "acwing/improvement course/1. dp/1.1 number triangle/acwing_1018.cpp")
add_executable(acwing_1027 "acwing/improvement course/1. dp/1.1 number triangle/acwing_1027.cpp")
add_executable(acwing_275 "acwing/improvement course/1. dp/1.1 number triangle/acwing_275.cpp")
add_executable(acwing_2014 "acwing/winter daily 2022/week 1/acwing_2014.cpp")
add_executable(acwing_2005 "acwing/winter daily 2022/week 1/acwing_2005.cpp")
add_executable(A "codeforces/contest/educational codeforces round/121/A.cpp")
add_executable(B "codeforces/contest/educational codeforces round/121/B.cpp")

add_executable(F "codeforces/contest/round/#764 (Div. 3)/F.cpp")
add_executable(acwing_1996 "acwing/winter daily 2022/week 1/acwing_1996.cpp")

add_executable(G "codeforces/contest/round/#764 (Div. 3)/G.cpp")

add_executable(acwing_1017 "acwing/improvement course/1. dp/1.2 lis/acwing_1017.cpp")
add_executable(acwing_1014 "acwing/improvement course/1. dp/1.2 lis/acwing_1014.cpp")
add_executable(acwing_482 "acwing/improvement course/1. dp/1.2 lis/acwing_482.cpp")
add_executable(acwing_1012 "acwing/improvement course/1. dp/1.2 lis/acwing_1012.cpp")
add_executable(acwing_1016 "acwing/improvement course/1. dp/1.2 lis/acwing_1016.cpp")
add_executable(acwing_1010 "acwing/improvement course/1. dp/1.2 lis/acwing_1010.cpp")

add_executable(acwing_187 "acwing/improvement course/1. dp/1.2 lis/acwing_187.cpp")
add_executable(acwing_272 "acwing/improvement course/1. dp/1.2 lis/acwing_272.cpp")

add_executable(acwing_1987 "acwing/winter daily 2022/week 2/acwing_1987.cpp")
add_executable(acwing_1978 "acwing/winter daily 2022/week 2/acwing_1978.cpp")
add_executable(acwing_1969 "acwing/winter daily 2022/week 2/acwing_1969.cpp")
add_executable(P5494 "luogu/seg tree split/P5494.cpp")

add_executable(P4556 "luogu/seg tree split/P4556.cpp")
add_executable(P2824 "luogu/seg tree split/P2824.cpp")
add_executable(acwing_3419 "acwing/seg tree split/acwing_3419.cpp")
add_executable(acwing_3189 "acwing/dsu on tree/acwing_3189.cpp")
add_executable(P4551 luogu/trie/P4551.cpp)

add_executable(C "codeforces/contest/educational codeforces round/121/C.cpp")

add_executable(acwing_136 "acwing/bluebook/0x10 base data structures/0x13 linked list/acwing_136.cpp")

add_executable(acwing_1960 "acwing/winter daily 2022/week 2/acwing_1960.cpp")
add_executable(acwing_1952 "acwing/winter daily 2022/week 2/acwing_1952.cpp")

add_executable(acwing_423 "acwing/improvement course/1. dp/1.3 knapsack/acwing_423.cpp")
add_executable(acwing_1024 "acwing/improvement course/1. dp/1.3 knapsack/acwing_1024.cpp")
add_executable(acwing_1022 "acwing/improvement course/1. dp/1.3 knapsack/acwing_1022.cpp")

add_executable(acwing_278 "acwing/improvement course/1. dp/1.3 knapsack/acwing_278.cpp")