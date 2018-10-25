#include "lib.h"
#include "version.h"
#include "ip_item.h" 

namespace ip_filter {
namespace version {
std::string version() {
    std::string version = std::to_string(versionMajor()) + "." +
                          std::to_string(versionMinor()) + "." +
                          std::to_string(versionPatch());
    return version;
}

int versionMajor() {
    return PROJECT_VERSION_MAJOR;
}

int versionMinor() {
    return PROJECT_VERSION_MINOR;
}

int versionPatch() {
    return PROJECT_VERSION_PATCH;
}
} // namespace version

IpPool::IpPool(std::vector<IpItem> &&pool)
    : mIpPool(pool) {
}

std::istream& operator>>(std::istream &is, IpPool &pool) {
    for (std::string line; std::getline(is, line);) {
        if (line.empty())
            break;
        IpItem item(line);
        pool.mIpPool.emplace_back(std::move(line));
    }
    return is;
}

std::ostream& operator<<(std::ostream &os, const IpPool &pool) {
    for (auto item : pool.mIpPool) {
        os << item << std::endl;
    }
    return os;
}


void IpPool::rsort() {
    std::sort(mIpPool.begin(), mIpPool.end(), [] (const IpItem &item1, const IpItem &item2) {
        return item1 > item2;
    });
}

} // namespace ip_filter
