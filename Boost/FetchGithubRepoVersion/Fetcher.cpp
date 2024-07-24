#include "Fetcher.hpp"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp> // For JSON parsing

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
namespace ssl = asio::ssl;
using tcp = asio::ip::tcp;
using json = nlohmann::json;

int FetcherObj::get_http(std::string const host, std::string const target, std::string const port)
{
    try
    {

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

        // 提取 JSON 响应体
        auto body = beast::buffers_to_string(res.body().data());

        // 解析 JSON
        json j = json::parse(body);
        std::cout << "tag_name: " << j["tag_name"].get<std::string>() << std::endl;
        std::cout << "published_at: " << j["published_at"].get<std::string>() << std::endl;

        // 关闭 SSL 流
        beast::error_code ec;
        stream.shutdown(ec);
        if (ec == asio::error::eof)
        {
            ec = {};
        }
        if (ec)
            throw beast::system_error{ec};
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
