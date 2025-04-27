cmake_minimum_required(VERSION 3.27)
project(Algorithms)

set(CMAKE_CXX_STANDARD 17)

add_executable(Rabin_Karp Rabin_Karp/main.cpp)
add_executable(KMP Knuth_Morris_Pratt/main.cpp)
add_executable(Dijkstra Dijkstra/main.cpp)
add_executable(Prime Prime/main.cpp)
add_executable(BST BST/main.cpp)
add_executable(Hopcroft_Karp Hopcroft-Karp/main.cpp)
add_executable(Red_Black_Tree Red_Black_Tree/main.cpp)
add_executable(B_Tree B_Tree/main.cpp)

