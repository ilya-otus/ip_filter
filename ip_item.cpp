#include "ip_item.h"

namespace ip_filter {

namespace {
const auto defaultFieldDelimiter = '\t';
const auto defaultIpDelimiter = '.';
} // namespace


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

IpItem::IpItem(const std::string &string) {
    std::vector<std::string> v = split<std::string>(string, defaultFieldDelimiter);
    mIpItem = split<int>(v.at(0), defaultIpDelimiter);
}

bool IpItem::isEmpty() const {
    return mIpItem.empty();
}

size_t IpItem::size() const {
    return mIpItem.size();
}

const std::vector<int>& IpItem::fields() const {
    return mIpItem;
}

std::ostream& operator<<(std::ostream &os, const IpItem &item) {
    for (auto fieldIt = item.mIpItem.begin(); fieldIt != item.mIpItem.end();  ++fieldIt) {
        if (fieldIt != item.mIpItem.begin()) {
            os << ".";
        }
        os << *fieldIt;
    }
    return os;
}
} // namespace ip_filter
