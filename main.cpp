#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include "json.hpp"

using json = nlohmann::json;

int main() {
    // 获取当前日期
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* date = std::localtime(&now_c);

    // 生成新的端口号
    //int newPort = (date->tm_year % 10) * 10000 + (date->tm_mon + 1) * 100 + date->tm_mday;

    std::string newPort= std::to_string(date->tm_year % 10)+std::to_string(date->tm_mon + 1)+std::to_string(date->tm_mday);
    

    // 读取 JSON 文件
    std::ifstream file("/root/trojan-go/server.json");
    json data;
    file >> data;

    // 替换 local_port 的值为新的端口号
    data["local_port"] = newPort;

    // 将修改后的 JSON 写回文件
    std::ofstream outFile("/root/trojan-go/server.json");
    outFile << data.dump(4); // 4 是缩进的空格数，可根据需要调整

    std::cout << "local_port 已替换为 " << newPort << "。" << std::endl;

    //执行shell脚本 重启trojan-go
    system("systemctl restart trojan-go");
    return 0;
}