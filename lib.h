#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "ip_item.h"
#include <array>
#include <functional>

namespace ip_filter {
namespace version {
std::string version();
int versionMajor();
int versionMinor();
int versionPatch();
} // namespace version

template <typename ... Args>
std::vector<IpItem> _filter(const std::vector<IpItem> &pool, Args ... args) {
    if (pool.size() == 0)
        return {};
    auto filterPredicate = [&] (const std::string &item, int pos) {
        std::array<std::string, sizeof...(args)> filterValues = {(std::to_string(args))...};
        return filterValues[pos] == item;
    };

    std::vector<IpItem> result;
    for (const auto &item : pool) {
        bool match = true;
        if (sizeof...(args) > item.size()) {
            for (size_t i = 0; i < item.size(); ++i) {
                match = match && filterPredicate(item.fields()[i], i);
            }
        } else {
            for (size_t i = 0; i < sizeof...(args); ++i) {
                match = match && filterPredicate(item.fields()[i], i);
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
    auto filterAnyPredicate = [&] (const std::string &item) {
        return std::to_string(t) == item;
    };

    std::vector<IpItem> result;
    for (const auto &item : pool) {
        bool match = false;
        for (size_t i = 0; i < item.size(); ++i) {
            match = match || filterAnyPredicate(item.fields()[i]);
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
private:
    std::vector<IpItem> mIpPool;
    //template <typename T, typename ... Args>
    //std::vector<IpItem> _filter(std::vector<IpItem> &buffer, T t, Args ... args);
};
std::istream& operator>>(std::istream &is, IpPool &pool);
std::ostream& operator<<(std::ostream &os, const IpPool &pool);
} // namespace ip_filter
