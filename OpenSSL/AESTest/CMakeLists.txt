cmake_minimum_required(VERSION 3.10)
project(YourProjectName)

add_compile_definitions(OPENSSL_NO_DEPRECATED_3_0)

# 查找 OpenSSL 库
find_package(OpenSSL REQUIRED)

# 添加可执行文件
add_executable(AESTest main.cpp openssl_aes.cpp)

# 包含 OpenSSL 头文件路径
target_include_directories(AESTest PRIVATE ${OPENSSL_INCLUDE_DIR})

# 链接 OpenSSL 库
target_link_libraries(AESTest PRIVATE ${OPENSSL_LIBRARIES})
