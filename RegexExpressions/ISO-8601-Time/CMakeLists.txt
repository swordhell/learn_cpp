cmake_minimum_required (VERSION 3.14)

project(ISO-8601-Time)

add_compile_options(-std=c++20)
SET( CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(iso-8601-time iso-8601-time.cpp)
