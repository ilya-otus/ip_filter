#include "ip_pool.h"

namespace ip_filter {

namespace {
const auto defaultFieldDelimiter = '\t';
const auto defaultIpDelimiter = '.';

template <typename T>
typename std::enable_if<!std::is_integral<T>::value, T>::type transformByType(const std::string &field) {
    return field;
}

template <typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type transformByType(const std::string &field) {
    return std::stoi(field);
}

template <typename T>
std::vector<T> split(const std::string &str, char delimiter) {
    std::vector<T> result;
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(delimiter);
    while(stop != std::string::npos) {
        result.push_back(transformByType<T>(str.substr(start, stop - start)));
        start = stop + 1;
        stop = str.find_first_of(delimiter, start);
    }
    result.push_back(transformByType<T>(str.substr(start)));
    return result;
}

IpItem itemFromString(const std::string &string) {
    auto v = split<std::string>(string, defaultFieldDelimiter);
    auto result = split<int>(v.at(0), defaultIpDelimiter);
    return result;
}
} // namespace

IpPool::IpPool(std::vector<IpItem> &&pool)
    : mIpPool(pool) {
}

IpPool::IpPool(std::vector<std::string> &&rawPool) {
    mIpPool.reserve(rawPool.size());
    for (auto rawItem : rawPool) {
        mIpPool.emplace_back(itemFromString(rawItem));
    }
}

void IpPool::rsort() {
    std::sort(mIpPool.begin(), mIpPool.end(), std::greater<IpItem>());
}

const std::vector<IpItem>& IpPool::items() const {
    return mIpPool;
}

std::istream& operator>>(std::istream &is, IpPool &pool) {
    for (std::string line; std::getline(is, line);) {
        if (line.empty())
            break;
        pool.mIpPool.emplace_back(itemFromString(line));
    }
    return is;
}

std::ostream& operator<<(std::ostream &os, const IpPool &pool) {
    for (auto item : pool.mIpPool) {
        os << item << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream &os, const IpItem &item) {
    for (auto fieldIt = item.begin(); fieldIt != item.end();  ++fieldIt) {
        if (fieldIt != item.begin()) {
            os << ".";
        }
        os << *fieldIt;
    }
    return os;
}
} // namespace ip_filter
