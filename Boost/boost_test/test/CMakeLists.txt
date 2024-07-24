# 添加测试可执行文件
add_executable(test_main test_main.cpp)

# 链接 Boost.Test 库
target_link_libraries(test_main Boost::test)

# 添加测试
add_test(NAME MyTest COMMAND test_main)