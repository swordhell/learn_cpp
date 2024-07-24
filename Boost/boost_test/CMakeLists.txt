cmake_minimum_required(VERSION 3.10)
project(MyProject)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 查找 Boost 库
find_package(Boost REQUIRED COMPONENTS system test)

# 添加源文件
add_executable(my_app src/main.cpp)
target_link_libraries(my_app Boost::system)

# 添加测试子目录
add_subdirectory(test)
