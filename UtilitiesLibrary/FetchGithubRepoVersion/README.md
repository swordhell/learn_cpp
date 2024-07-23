要使用 Boost.Beast 库实现 HTTPS GET 方法并获取 JSON 格式的数据，可以参考以下示例代码，该代码演示了如何访问 GitHub API 的最新 Geth 发布信息：

### 示例代码

```cpp
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>
#include <iostream>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
namespace ssl = asio::ssl;
using tcp = asio::ip::tcp;

int main() {
    try {
        // 要连接的主机和目标页面
        const std::string host = "api.github.com";
        const std::string port = "443";
        const std::string target = "/repos/ethereum/go-ethereum/releases/latest";

        // 创建 IO 上下文
        asio::io_context ioc;

        // 创建 SSL 上下文
        ssl::context ctx(ssl::context::sslv23_client);

        // 设置 SSL 验证选项
        ctx.set_verify_mode(ssl::verify_peer);
        ctx.set_default_verify_paths();

        // 创建 TCP 套接字
        tcp::resolver resolver(ioc);
        beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx);

        // 解析主机名
        auto const results = resolver.resolve(host, port);

        // 连接到远程端点
        beast::get_lowest_layer(stream).connect(results);

        // 执行 SSL 握手
        stream.handshake(ssl::stream_base::client);

        // 设置 HTTP GET 请求报文
        http::request<http::string_body> req{http::verb::get, target, 11};
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        req.set(http::field::accept, "application/vnd.github.v3+json");

        // 发送 HTTP 请求
        http::write(stream, req);

        // 接收 HTTP 响应
        beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(stream, buffer, res);

        // 打印响应
        std::cout << res << std::endl;

        // 关闭 SSL 流
        beast::error_code ec;
        stream.shutdown(ec);
        if(ec == asio::error::eof) {
            ec = {};
        }
        if(ec)
            throw beast::system_error{ec};

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
```

### 说明
1. **主机名和目标 URL**：设置访问的 GitHub API 主机名和目标 URL。
2. **SSL 验证**：配置 SSL 验证选项以确保安全连接。
3. **HTTP 请求设置**：
    - `http::field::host`：设置主机名。
    - `http::field::user_agent`：设置用户代理。
    - `http::field::accept`：指定接受的内容类型为 GitHub API 的 JSON 响应。
4. **发送和接收 HTTP 请求**：使用 Boost.Beast 库发送 HTTP GET 请求并读取响应。
5. **打印响应**：将响应内容打印到标准输出。

此代码实现了使用 Boost.Beast 库访问 HTTPS URL，并获取 JSON 响应。你可以根据需要进一步处理或解析响应数据。