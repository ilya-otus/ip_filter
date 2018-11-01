#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <array>

namespace ip_filter {
using IpItem = std::vector<int>;

template <typename ... Args>
std::vector<IpItem> _filter(const std::vector<IpItem> &pool, Args ... args) {
    if (pool.size() == 0)
        return {};
    std::vector<IpItem> result;
    std::copy_if(pool.begin(), pool.end(), std::back_inserter(result), [&](const IpItem &item) {
        constexpr size_t argSize = sizeof...(args);
        std::array<int, argSize> filterValues = {(args)...};
        bool match = true;
        for (size_t i = 0; i < std::min(argSize, item.size()); ++i) {
            match = match && (filterValues[i] == item[i]);
        }
        return match;
    });
    return result;
}
class IpPool {
public:
    IpPool() = default;
    IpPool(std::vector<IpItem> &&pool);
    IpPool(std::vector<std::string> &&rawPool);
    friend std::istream& operator>>(std::istream &is, IpPool &pool);
    friend std::ostream& operator<<(std::ostream &os, const IpPool &pool);
    template <typename ... Args>
    IpPool filter(Args ... args) {
        return _filter(mIpPool, args...);
    }
    IpPool filter_any(int f) const;
    void rsort();
    const std::vector<IpItem>& items() const;
private:
    std::vector<IpItem> mIpPool;
};
std::istream& operator>>(std::istream &is, IpPool &pool);
std::ostream& operator<<(std::ostream &os, const IpPool &pool);
std::ostream& operator<<(std::ostream &os, const IpItem &item);
} // namespace ip_filter
