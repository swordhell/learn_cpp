#include "spdlog/spdlog.h"
#include "yaml-cpp/yaml.h"
#include <cpr/cpr.h>
#include <string>

int main()
{
    spdlog::info("start test cpr get url");
    YAML::Node config = YAML::LoadFile("../config.yaml");

    cpr::Response r = cpr::Get(cpr::Url{config["url"].as<std::string>()},
                               cpr::Header{{"accept", "application/json"}},
                               cpr::Header{{"content-type", "application/x-www-form-urlencoded"}}
                               );

    spdlog::info(r.url.c_str());
    spdlog::info(r.header["content-type"]); // application/json; charset=utf-8
    spdlog::info(r.text);                   // JSON text string

    return 0;
}
