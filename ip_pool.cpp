#include "ip_pool.h"
#include "version.h"

namespace ip_filter {
IpPool::IpPool(std::vector<IpItem> &&pool)
    : mIpPool(pool) {
}

IpPool::IpPool(std::vector<std::string> &&rawPool) {
    mIpPool.reserve(rawPool.size());
    for (auto rawItem : rawPool) {
        mIpPool.emplace_back(IpItem(rawItem));
    }
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

const std::vector<IpItem>& IpPool::items() const {
    return mIpPool;
}


} // namespace ip_filter
