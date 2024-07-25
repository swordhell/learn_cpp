
# 添加测试可执行文件
add_executable(test_main test_main.cpp)
# vcpkg install boost-test
# 链接 Boost.Test 库

target_link_libraries(test_main PRIVATE Boost::unit_test_framework)
# 添加测试
add_test(NAME MyTest COMMAND test_main)
