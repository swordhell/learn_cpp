# 概述

需要尝试一下如何使用vcpkg来初始化一个项目。

## 记录一下两件事情

项目名称只能支持字符串‘-’这两种；
    "name": "wood-curl-test",

这个需要读取本地机器上的vcpkg目录下面， git log最新的 hash值；
    "builtin-baseline": "b322364f06308bdd24823f9d8f03fe0cc86fd46f",

## 使用到的命令行

```bash
vcpkg install
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=/Users/abel/vcpkg/scripts/buildsystems/vcpkg.cmake \
-DCMAKE_VERBOSE_MAKEFILE=ON \
-DCMAKE_OSX_SYSROOT=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.1.sdk \
-DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
-DCMAKE_C_COMPILER:FILEPATH=/usr/bin/clang -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++ 
mkdir build && cd build && cmake .. && make
```

下面是一个完整示例，满足你所需的 C++ 项目：
	1.	使用 CMake 管理项目。
	2.	使用 vcpkg 管理三方库依赖（curl、nlohmann-json、spdlog、yaml-cpp）。
	3.	实现功能：
	•	读取 YAML 配置文件（包括 URL 和 POST 数据）。
	•	使用 curl 发送 HTTP POST 请求。
	•	解析 JSON 返回数据。
	•	使用 spdlog 记录日志。

项目结构

my_project/
│
├── CMakeLists.txt          # CMake 配置文件
├── vcpkg.json              # vcpkg 依赖管理
├── config.yaml             # 配置文件
└── main.cpp                # 主程序

1. vcpkg.json

管理依赖库：

{
    "name": "my-project",
    "version": "1.0.0",
    "builtin-baseline": "09a2b4f8c8c1529d3aee160e9dfd1167bbffdf5b",
    "dependencies": [
        "curl",
        "nlohmann-json",
        "spdlog",
        "yaml-cpp"
    ]
}

	注意： 请替换 builtin-baseline 为你当前 vcpkg 的有效 commit hash。

2. CMakeLists.txt

配置 CMake 项目，集成 vcpkg 和所需依赖：

cmake_minimum_required(VERSION 3.15)
project(my_project VERSION 1.0.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

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
add_executable(my_project main.cpp)

# 链接依赖库
target_link_libraries(my_project
    CURL::libcurl
    nlohmann_json::nlohmann_json
    spdlog::spdlog
    yaml-cpp
)

3. config.yaml

配置文件，包含请求 URL 和 POST 数据：

url: "https://example.com/api/endpoint"
post_data:
  orderId: "20241216150452189615"
  receiveAddress: "TEvTSnwL2MaYn4ucVT7xdnB8KjfCKkK6Ro"
  hashCode: "e7a70543c319b1420885dfeb0c02990af8261c382868ecea6c6f6f550c73f570"
  autoType: 0
  sign: "ab5113e1b70778eb77ce8f040992113f"
  payment: 1
  state: 1
  residue: 9
  triggerTransactionId: ""

4. main.cpp

程序逻辑，包含 YAML 读取、HTTP POST 请求、JSON 解析和日志记录：

#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <yaml-cpp/yaml.h>

// 回调函数：处理 curl 返回数据
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

int main() {
    try {
        spdlog::info("Starting application...");

        // 1. 读取 YAML 配置文件
        YAML::Node config = YAML::LoadFile("config.yaml");
        std::string url = config["url"].as<std::string>();
        nlohmann::json post_data = config["post_data"];

        spdlog::info("Loaded configuration. Target URL: {}", url);

        // 2. 初始化 CURL
        CURL* curl = curl_easy_init();
        if (!curl) {
            spdlog::error("Failed to initialize CURL.");
            return 1;
        }

        std::string response;  // 存储响应数据
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.dump().c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // 3. 执行请求
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            spdlog::error("CURL request failed: {}", curl_easy_strerror(res));
        } else {
            spdlog::info("CURL request successful. Response: {}", response);

            // 4. 解析 JSON 响应
            auto json_response = nlohmann::json::parse(response);
            spdlog::info("Parsed JSON response: {}", json_response.dump(4));
        }

        // 5. 清理
        curl_easy_cleanup(curl);
        spdlog::info("Application finished successfully.");
    } catch (const std::exception& e) {
        spdlog::error("Exception: {}", e.what());
        return 1;
    }

    return 0;
}

5. 构建项目

1. 安装依赖

使用 vcpkg 安装所需库：

vcpkg install curl nlohmann-json spdlog yaml-cpp

2. 生成构建目录并编译

mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake ..
cmake --build .

3. 运行程序

将 config.yaml 放在可执行文件目录下，然后运行程序：

./my_project

输出示例
	1.	读取配置：

Loaded configuration. Target URL: https://example.com/api/endpoint


	2.	CURL 请求成功：

CURL request successful. Response: {"status":"success","data":{"key":"value"}}


	3.	JSON 解析：

Parsed JSON response:
{
    "status": "success",
    "data": {
        "key": "value"
    }
}


	4.	日志记录：

[info] Starting application...
[info] Loaded configuration. Target URL: https://example.com/api/endpoint
[info] CURL request successful. Response: {"status":"success","data":{"key":"value"}}
[info] Application finished successfully.

总结

这个项目通过 CMake 和 vcpkg 完整管理依赖，实现了以下功能：
	1.	读取 YAML 配置文件。
	2.	使用 curl 发送 HTTP POST 请求。
	3.	使用 nlohmann-json 解析返回的 JSON 数据。
	4.	使用 spdlog 进行日志记录。

现在，你可以根据需求进一步扩展功能。
