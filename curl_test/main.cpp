#include <iostream>
#include <fstream>
#include <spdlog/spdlog.h>
#include <yaml-cpp/yaml.h>
#include "curl_client.hpp"

int main()
{
    // 初始化 spdlog
    spdlog::set_level(spdlog::level::info); // 设置日志级别为 info
    spdlog::info("Starting application...");
    try
    {
        // 读取 YAML 文件
        YAML::Node config = YAML::LoadFile("config.yaml");

        // 初始化 CurlClient
        CurlClient client;

        // 设置 URL
        client.setUrl(config["url"].as<std::string>());

        // 设置查询参数
        for (auto it : config["query_params"])
        {
            client.addQueryParam(it.first.as<std::string>(), it.second.as<std::string>());
        }

        // 设置 HTTP 头部
        for (const auto &header : config["headers"].as<std::vector<std::string>>())
        {
            client.addHeader(header);
        }

        // 发起 GET 请求
        std::string response = client.get();

        // 输出响应
        spdlog::info("Response: {}", response);
    }
    catch (const std::exception &e)
    {
        spdlog::info("Error: {}", e.what());
        return 1;
    }

    return 0;
}
