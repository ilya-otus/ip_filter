#pragma once
#include <vector>
#include <string>
#include <iostream>

namespace ip_filter {
std::vector<std::string> split(const std::string &str, char delimiter);
class IpItem
{
public:
    IpItem(const std::string &string);
    bool isEmpty();
    bool operator>(const IpItem &right) const;
    bool operator<(const IpItem &right) const;
    friend std::ostream& operator<<(std::ostream &os, const IpItem &item);
    size_t size() const;
    const std::vector<std::string>& fields() const;
private:
    std::vector<std::string> mIpItem;
};
std::ostream& operator<<(std::ostream &os, const IpItem &item);
} // namespace ip_filter
