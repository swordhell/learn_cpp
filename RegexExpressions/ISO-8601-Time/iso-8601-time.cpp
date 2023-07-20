// 这种字符串是一种ISO 8601格式的时间字符串，包含了日期和时间，并以"T"分隔日期和时间部分，
// 以"Z"表示时区为UTC。ISO 8601是国际标准时间表示法，是一种常用的时间表示方式。在这种格式
// 中，日期部分使用"-"分隔年、月和日，时间部分使用冒号分隔小时、分钟、秒和毫秒，最后一位数字
// 表示百分之一秒。
#include <iostream>
#include <ctime>
#include <chrono>
#include <regex>
#include <iomanip>
#include <sstream>

int main()
{
    std::string time_str = "2023-07-18T19:45:07.823454864Z";

    // 定义正则表达式模式匹配日期和时间部分
    std::regex date_time_regex(R"(\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}.\d+Z)");

    // 提取日期和时间部分
    std::smatch date_time_match;
    if (std::regex_search(time_str, date_time_match, date_time_regex))
    {
        // 拆分日期和时间部分
        std::string date_str = date_time_match[0].str();
        std::string time_str = date_time_match[0].str();

        // 将日期部分转换为本地时间
        std::tm tm;
        std::istringstream iss(date_str);
        iss >> std::get_time(&tm, "%Y-%m-%d");
        std::chrono::system_clock::time_point date_time = std::chrono::system_clock::from_time_t(std::mktime(&tm));

        // 将时间部分转换为本地时间
        std::tm time_tm;
        std::istringstream iss2(time_str);
        iss2 >> std::get_time(&time_tm, "%H:%M:%S");
        std::chrono::system_clock::time_point time = std::chrono::system_clock::from_time_t(std::mktime(&time_tm));

        // 将日期和时间合并为单个时间点
        std::chrono::system_clock::duration diff = date_time - time;
        std::chrono::system_clock::time_point full_date_time = std::chrono::system_clock::now() + diff;

        // 输出结果
        std::time_t full_time = std::chrono::system_clock::to_time_t(full_date_time);
        std::cout << "Full time: " << std::ctime(&full_time) << std::endl;
    }

    return 0;
}
