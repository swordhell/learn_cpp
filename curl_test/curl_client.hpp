#pragma once
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <curl/curl.h>

// 回调函数：用于接收服务器响应数据
size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *response);

// Curl封装类
class CurlClient
{
public:
    /// @brief
    CurlClient();

    ~CurlClient();

    // 设置请求URL
    void setUrl(const std::string &url);

    // 添加查询参数
    void addQueryParam(const std::string &key, const std::string &value);

    // 添加HTTP头部
    void addHeader(const std::string &header);

    // 发起GET请求
    std::string get();

private:
    CURL *curl;
    struct curl_slist *headers = nullptr;
    std::string url;
    std::map<std::string, std::string> queryParams;

    // 构造完整的URL
    std::string constructURL() const;
};
