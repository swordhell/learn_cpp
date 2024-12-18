cmake_minimum_required(VERSION 3.15)
project(abel-curl-test VERSION 1.0.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(nlohmann-json_IMPLICIT_CONVERSIONS OFF)

# vcpkg 工具链文件路径（手动设置或通过 CMake 参数传入）
if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
endif()

# 查找依赖
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(spdlog REQUIRED)
find_package(yaml-cpp REQUIRED)

# 添加可执行文件
add_executable(abel-curl-test main.cpp cur_client.cpp)

# 链接依赖库
target_link_libraries(abel-curl-test PRIVATE CURL::libcurl)
target_link_libraries(abel-curl-test PRIVATE nlohmann_json::nlohmann_json )
target_link_libraries(abel-curl-test PRIVATE spdlog::spdlog )
target_link_libraries(abel-curl-test PRIVATE yaml-cpp )