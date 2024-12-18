#include "curl_client.hpp"

// 回调函数：用于接收服务器响应数据
size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *response)
{
    size_t totalSize = size * nmemb;
    response->append(static_cast<char *>(contents), totalSize);
    return totalSize;
}
CurlClient::CurlClient()
{
    curl = curl_easy_init();
    if (!curl)
    {
        throw std::runtime_error("Failed to initialize CURL");
    }
}
CurlClient::~CurlClient()
{
    if (curl)
    {
        curl_easy_cleanup(curl);
    }
    if (headers)
    {
        curl_slist_free_all(headers);
    }
}
void CurlClient::setUrl(const std::string &url)
{
    this->url = url;
}
void CurlClient::addQueryParam(const std::string &key, const std::string &value)
{
    queryParams[key] = value;
}

void CurlClient::addHeader(const std::string &header)
{
    headers = curl_slist_append(headers, header.c_str());
}
std::string CurlClient::get()
{
    if (url.empty())
    {
        throw std::runtime_error("URL is not set");
    }

    // 构造完整URL
    std::string fullUrl = constructURL();
    curl_easy_setopt(curl, CURLOPT_URL, fullUrl.c_str());

    // 设置HTTP头部
    if (headers)
    {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    }

    // 设置响应回调
    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // 执行请求
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        throw std::runtime_error(curl_easy_strerror(res));
    }

    return response;
}
std::string CurlClient::constructURL() const
{
    std::ostringstream oss;
    oss << url;
    if (!queryParams.empty())
    {
        oss << "?";
        for (auto it = queryParams.begin(); it != queryParams.end(); ++it)
        {
            if (it != queryParams.begin())
            {
                oss << "&";
            }
            oss << it->first << "=" << it->second;
        }
    }
    return oss.str();
}