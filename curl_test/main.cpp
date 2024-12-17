#include <iostream>
#include <fstream>
#include <sstream>
#include <curl/curl.h>
#include "nlohmann/json.hpp"
#include "spdlog/spdlog.h"
#include "yaml-cpp/yaml.h"

// 用于接收 curl 写入的数据的结构体
struct MemoryStruct {
    char* memory;
    size_t size;
};

// curl 写入回调函数，将接收到的数据存储到 MemoryStruct 中
size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    MemoryStruct* mem = (MemoryStruct*)userp;

    char* ptr = (char*)realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) {
        // 内存分配失败处理
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

int main() {
    // 1. 读取配置文件（以 yaml-cpp 为例，简单示意读取配置）
    YAML::Node config = YAML::LoadFile("config.yaml");
    std::string url = config["url"].as<std::string>();
    std::string post_data = config["post_data"].as<std::string>();

    // 2. 使用 curl 进行 POST 访问
    CURL* curl = curl_easy_init();
    if (curl) {
        CURLcode res;
        MemoryStruct chunk;
        chunk.memory = (char*)malloc(1);
        chunk.size = 0;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);

        res = curl_easy_perform(curl);
        if (res!= CURLE_OK) {
            spdlog::error("curl_easy_perform() failed: {}", curl_easy_strerror(res));
        } else {
            // 3. 解析返回的 JSON（以 nlohmann-json 为例）
            try {
                nlohmann::json j = nlohmann::json::parse(chunk.memory);
                // 在这里可以根据具体返回的 JSON 结构进行进一步处理，比如提取数据等
                std::cout << j.dump(4) << std::endl;
            } catch (const nlohmann::json::parse_error& e) {
                spdlog::error("JSON parsing error: {}", e.what());
            }
        }

        free(chunk.memory);
        curl_easy_cleanup(curl);
    }

    return 0;
}