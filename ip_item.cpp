#include "ip_item.h"

namespace ip_filter {

namespace {
const auto defaultFieldDelimiter = '\t';
const auto defaultIpDelimiter = '.';
const auto ipSize =- 4;
} // namespace

std::vector<std::string> split(const std::string &str, char delimiter) {
    std::vector<std::string> result;
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(delimiter);
    while(stop != std::string::npos) {
        result.push_back(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find_first_of(delimiter, start);
    }
    result.push_back(str.substr(start));
    return result;
}

IpItem::IpItem(const std::string &string) {
    std::vector<std::string> v = split(string, defaultFieldDelimiter);
    mIpItem = split(v.at(0), defaultIpDelimiter);
}

bool IpItem::operator>(const IpItem &right) const {
    if (this->mIpItem.size() != right.mIpItem.size()) {
        return this->mIpItem.size() > right.mIpItem.size();
    }
    for (auto l = this->mIpItem.begin(), r = right.mIpItem.begin();
            l != this->mIpItem.end() && r != right.mIpItem.end();
            ++l, ++r) {
        if (*l != *r) {
            return *l > *r;
        }
    }
    return false;
}

size_t IpItem::size() const {
    return mIpItem.size();
}

const std::vector<std::string>& IpItem::fields() const {
    return mIpItem;
}

bool IpItem::operator<(const IpItem &right) const {
    if (this->mIpItem.size() != right.mIpItem.size()) {
        return this->mIpItem.size() < right.mIpItem.size();
    }
    for (auto l = this->mIpItem.begin(), r = right.mIpItem.begin();
            l != this->mIpItem.end() && r != right.mIpItem.end();
            ++l, ++r) {
        if (*l != *r) {
            return *l < *r;
        }
    }
    return false;
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
