cmake_minimum_required(VERSION 3.24)
project(CPP20Modules LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER g++-13)

add_library(math MODULE math.cppm)
add_executable(main main.cpp)
target_link_libraries(main PRIVATE math)