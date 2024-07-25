cmake_minimum_required(VERSION 3.10)
project(MyProject)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CPR_BUILD_TESTS ON)

find_package(cpr CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(OpenSSL REQUIRED)

add_executable(cpr_test main.cpp)

target_link_libraries(cpr_test PRIVATE cpr::cpr)
target_link_libraries(cpr_test PRIVATE spdlog::spdlog)
target_link_libraries(cpr_test PRIVATE yaml-cpp::yaml-cpp)
target_link_libraries(cpr_test PRIVATE OpenSSL::SSL)
