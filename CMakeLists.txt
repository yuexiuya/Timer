cmake_minimum_required(VERSION 3.14)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp HTimer.h HTimer.cpp)
target_link_libraries(untitled pthread)