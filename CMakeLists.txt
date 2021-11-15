cmake_minimum_required(VERSION 3.20)
project(algorithm)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DLOCAL)

add_executable(acwing_349 "bluebook/0x60 graph/0x62 min spanning tree/acwing_349.cpp")
add_executable(I codeforces/gym/103186/I.cpp)

add_executable(F codeforces/gym/103049/F.cpp)
add_executable(acwing_340 "bluebook/0x60 graph/0x61 shortest path/acwing_340.cpp")
add_executable(acwing_363 "bluebook/0x60 graph/0x66 tarjan-dcc/acwing_363.cpp")
add_executable(acwing_364 "bluebook/0x60 graph/0x66 tarjan-dcc/acwing_364.cpp")

add_executable(tmp tmp.cpp)
add_executable(acwing_367 "bluebook/0x60 graph/0x67 tarjan-scc/acwing_367.cpp")
add_executable(acwing_368 "bluebook/0x60 graph/0x67 tarjan-scc/acwing_368.cpp")
add_executable(M codeforces/gym/103388/M.cpp)

add_executable(acwing_348 "bluebook/0x60 graph/0x62 min spanning tree/acwing_348.cpp")

add_executable(A dgutoj/contest/25/A.cpp)
add_executable(B dgutoj/contest/25/B.cpp)
add_executable(C dgutoj/contest/25/C.cpp)
add_executable(D dgutoj/contest/25/D.cpp)
add_executable(E dgutoj/contest/25/E.cpp)
add_executable(E2 dgutoj/contest/25/E2.cpp)