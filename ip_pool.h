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
    auto filterPredicate = [&] (int item, int pos) {
        std::array<int, sizeof...(args)> filterValues = {(args)...};
        return filterValues[pos] == item;
    };

    std::vector<IpItem> result;
    for (const auto &item : pool) {
        bool match = true;
        if (sizeof...(args) > item.size()) {
            for (size_t i = 0; i < item.size(); ++i) {
                match = match && filterPredicate(item[i], i);
            }
        } else {
            for (size_t i = 0; i < sizeof...(args); ++i) {
                match = match && filterPredicate(item[i], i);
            }
        }
        if (match) {
            result.emplace_back(item);
        }
    }
    return result;
}

template <typename T>
std::vector<IpItem> _filter_any(const std::vector<IpItem> &pool, T t) {
    if (pool.size() == 0)
        return {};
    auto filterAnyPredicate = [&] (int item) {
        return t == item;
    };

    std::vector<IpItem> result;
    for (const auto &item : pool) {
        bool match = false;
        for (size_t i = 0; i < item.size(); ++i) {
            match = match || filterAnyPredicate(item[i]);
        }
        if (match) {
            result.emplace_back(item);
        }
    }
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

    template <typename T>
    IpPool filter_any(T t) {
        return _filter_any(mIpPool, t);
    }

    void rsort();
    const std::vector<IpItem>& items() const;
private:
    std::vector<IpItem> mIpPool;
};
std::istream& operator>>(std::istream &is, IpPool &pool);
std::ostream& operator<<(std::ostream &os, const IpPool &pool);
std::ostream& operator<<(std::ostream &os, const IpItem &item);
} // namespace ip_filter
