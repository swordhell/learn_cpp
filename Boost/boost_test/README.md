Boost 提供了强大的单元测试库 Boost.Test，能够方便地进行单元测试。下面是一个示例，展示如何使用 Boost.Test 进行单元测试，并使用 CMake 构建项目。

### 项目结构
```
my_project/
├── CMakeLists.txt
├── src/
│   └── main.cpp
└── test/
    ├── CMakeLists.txt
    └── test_main.cpp
```

### `CMakeLists.txt`（根目录）
```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 查找 Boost 库
find_package(Boost 1.65.1 REQUIRED COMPONENTS system test)

# 添加源文件
add_executable(my_app src/main.cpp)
target_link_libraries(my_app Boost::system)

# 添加测试子目录
add_subdirectory(test)
```

### `src/main.cpp`
```cpp
#include <iostream>

int add(int a, int b) {
    return a + b;
}

int main() {
    std::cout << "3 + 4 = " << add(3, 4) << std::endl;
    return 0;
}
```

### `test/CMakeLists.txt`
```cmake
# 添加测试可执行文件
add_executable(test_main test_main.cpp)

# 链接 Boost.Test 库
target_link_libraries(test_main Boost::test)

# 添加测试
add_test(NAME MyTest COMMAND test_main)
```

### `test/test_main.cpp`
```cpp
#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>

int add(int a, int b) {
    return a + b;
}

BOOST_AUTO_TEST_CASE(addition_test) {
    BOOST_CHECK(add(2, 2) == 4);
    BOOST_CHECK(add(2, 3) == 5);
    BOOST_CHECK(add(-1, 1) == 0);
    BOOST_CHECK(add(-1, -1) == -2);
}
```

### 解释

1. **根目录 `CMakeLists.txt`**：
   - 设置项目名称和 C++ 标准。
   - 查找所需的 Boost 组件（`system` 和 `test`）。
   - 创建主可执行文件 `my_app`，并链接 Boost.System 库。
   - 添加测试子目录。

2. **`src/main.cpp`**：
   - 简单的 `add` 函数和一个 `main` 函数，演示如何使用该函数。

3. **测试目录 `CMakeLists.txt`**：
   - 创建测试可执行文件 `test_main`。
   - 链接 Boost.Test 库。
   - 使用 `add_test` 命令注册测试。

4. **`test/test_main.cpp`**：
   - 包含 Boost.Test 的头文件。
   - 使用 `BOOST_AUTO_TEST_CASE` 定义测试用例。
   - 在测试用例中，使用 `BOOST_CHECK` 断言测试结果。

### 构建和运行

1. 创建构建目录并进入该目录：
   ```sh
   mkdir build
   cd build
   ```

2. 运行 CMake 以生成构建文件：
   ```sh
   cmake ..
   ```

3. 构建项目：
   ```sh
   make
   ```

4. 运行测试：
   ```sh
   ctest
   ```

这个示例展示了如何使用 Boost.Test 进行单元测试，并使用 CMake 构建和运行测试。你可以根据需要扩展和修改此项目结构和代码。

```bash
rm -rf ./build/
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/clang -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++
```

## 解决问题

首先这个问题还找不到答案。最后我搞清楚了cmake里面的还的自己去 ${VCPKG_ROOT}/packages/ 目录去找一下 cmake 文件。
