#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <yaml-cpp/yaml.h>

// 回调函数：处理 curl 返回数据
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output)
{
    size_t totalSize = size * nmemb;
    output->append((char *)contents, totalSize);
    return totalSize;
}
// 递归将 YAML::Node 转换成 nlohmann::json
nlohmann::json yamlToJson(const YAML::Node& node) {
    if (node.IsScalar()) { // 处理标量
        return node.as<std::string>();
    } 
    else if (node.IsSequence()) { // 处理数组
        nlohmann::json arr = nlohmann::json::array();
        for (const auto& element : node) {
            arr.push_back(yamlToJson(element));
        }
        return arr;
    } 
    else if (node.IsMap()) { // 处理映射
        nlohmann::json obj;
        for (const auto& pair : node) {
            obj[pair.first.as<std::string>()] = yamlToJson(pair.second);
        }
        return obj;
    }
    return nullptr; // 如果 node 为空
}
int main()
{
    try
    {
        spdlog::info("Starting application...");

        // 1. 读取 YAML 配置文件
        YAML::Node config = YAML::LoadFile("config.yaml");
        std::string url = config["url"].as<std::string>();
        auto json_data = config["post_data"];
        std::cout << json_data << std::endl;

        spdlog::info("Loaded configuration. Target URL: {}", url);

        nlohmann::json post_data = yamlToJson(json_data);

        spdlog::info("Loaded configuration. Target URL: {}", url);

        // 2. 初始化 CURL
        CURL *curl = curl_easy_init();
        if (!curl)
        {
            spdlog::error("Failed to initialize CURL.");
            return 1;
        }

        std::string response; // 存储响应数据
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.dump().c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // 3. 执行请求
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            spdlog::error("CURL request failed: {}", curl_easy_strerror(res));
        }
        else
        {
            spdlog::info("CURL request successful. Response: {}", response);

            // 4. 解析 JSON 响应
            auto json_response = nlohmann::json::parse(response);
            spdlog::info("Parsed JSON response: {}", json_response.dump(4));
        }

        // 5. 清理
        curl_easy_cleanup(curl);
        spdlog::info("Application finished successfully.");
    }
    catch (const std::exception &e)
    {
        spdlog::error("Exception: {}", e.what());
        return 1;
    }

    return 0;
}