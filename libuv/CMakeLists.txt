cmake_minimum_required(VERSION 3.10)
project(LibUVTest)

find_package(libuv CONFIG REQUIRED)

add_executable(my_executable main.cpp)
target_link_libraries(my_executable PRIVATE $<IF:$<TARGET_EXISTS:libuv::uv_a>,libuv::uv_a,libuv::uv>)
