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