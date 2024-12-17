# 设置 CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称和语言
project(my_project CXX)

# 设置 C++ 标准，这里以 C++17 为例，可根据需求调整
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 vcpkg 安装路径，如果没有设置环境变量，可手动指定
if(DEFINED ENV{VCPKG_ROOT})
    set(VCPKG_ROOT $ENV{VCPKG_ROOT})
else()
    message(FATAL_ERROR "VCPKG_ROOT environment variable not set. Please set it to the vcpkg installation directory.")
endif()


# 查找项目所需的第三方库
find_package(curl CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)

# 添加项目源文件，这里假设只有 main.cpp
add_executable(my_project main.cpp)

# 链接相关的第三方库到项目可执行文件
target_link_libraries(my_project PRIVATE
    curl::curl
    nlohmann_json::nlohmann_json
    spdlog::spdlog
    yaml-cpp::yaml-cpp
)