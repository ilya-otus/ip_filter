#include "lib.h"
#include <iostream>
#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>

int main(int argc, char *argv[])
{
    auto logger = spdlog::stdout_logger_mt("console");
    if (argc > 1) {
        bool isVersionRequired = std::string(argv[1]).compare("-v") == 0;
        if (isVersionRequired) {
            logger->info("version {} was started", ip_filter::version::version());
        }
        return 0;
    }
    std::cin.clear();
    auto ipPool = ip_filter::IpPool();
    std::cin >> ipPool;
    ipPool.rsort();
    std::cout << ipPool << std::endl;
    std::cout << ipPool.filter(1) << std::endl;
    std::cout << ipPool.filter(46, 70) << std::endl;
    std::cout << ipPool.filter_any(46) << std::endl;
    return 0;
}
