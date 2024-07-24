#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class FetcherObj
{
public:
    FetcherObj() = default;

    int real_process()
    {

        try
        {
            std::cout << "current path:"
                      << std::filesystem::current_path() << "\n";
            YAML::Node config = YAML::LoadFile("../config.yaml");
            std::vector<std::string> paths = config["paths"].as<std::vector<std::string>>();
            std::string host = config["host"].as<std::string>();
            for (auto const &path : paths)
            {
                std::cout << "host " << host << " path " << path << "\n";
                get_http(std::string(host), std::string(path),"443");
            }
        }
        catch (std::exception const &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

private:
    int get_http(std::string const host, std::string const path, std::string const port);
};
