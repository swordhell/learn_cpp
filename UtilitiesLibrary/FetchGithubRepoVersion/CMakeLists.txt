cmake_minimum_required (VERSION 3.29)

project (FetchGithubRepoVersion LANGUAGES CXX)
# 打印编译器信息
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ compiler version: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "C++ compiler ID: ${CMAKE_CXX_COMPILER_ID}")

find_package(nlohmann_json CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
find_package(yaml-cpp REQUIRED)
# Find Boost libraries
find_package(Boost REQUIRED COMPONENTS system thread)
# Find Boost.Beast and Boost.Asio
find_package(Boost REQUIRED COMPONENTS beast asio)
find_package(OpenSSL REQUIRED)


set(CMAKE_CXX_STANDARD 17)


add_executable(fgrv main.cpp Fetcher.cpp )

target_link_libraries(fgrv PRIVATE Boost::system)
target_link_libraries(fgrv PRIVATE yaml-cpp::yaml-cpp)
target_link_libraries(fgrv PRIVATE Boost::beast)
target_link_libraries(fgrv PRIVATE Boost::asio)
target_link_libraries(fgrv PRIVATE Boost::system)
target_link_libraries(fgrv PRIVATE pthread)
target_link_libraries(fgrv PRIVATE OpenSSL::SSL)

add_executable(http_client_sync http_client_sync.cpp )

target_link_libraries(http_client_sync PRIVATE Boost::system)
target_link_libraries(http_client_sync PRIVATE yaml-cpp::yaml-cpp)
target_link_libraries(http_client_sync PRIVATE Boost::beast)
target_link_libraries(http_client_sync PRIVATE Boost::asio)
target_link_libraries(http_client_sync PRIVATE Boost::system)
target_link_libraries(http_client_sync PRIVATE pthread)
target_link_libraries(http_client_sync PRIVATE OpenSSL::SSL)


add_executable(chatGPT_sample chatGPT_sample.cpp )

target_link_libraries(chatGPT_sample PRIVATE Boost::system)
target_link_libraries(chatGPT_sample PRIVATE yaml-cpp::yaml-cpp)
target_link_libraries(chatGPT_sample PRIVATE Boost::beast)
target_link_libraries(chatGPT_sample PRIVATE Boost::asio)
target_link_libraries(chatGPT_sample PRIVATE Boost::system)
target_link_libraries(chatGPT_sample PRIVATE pthread)
target_link_libraries(chatGPT_sample PRIVATE OpenSSL::SSL)

