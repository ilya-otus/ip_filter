#pragma once
#include <vector>
#include <string>
#include <iostream>

namespace ip_filter {
class IpItem
{
public:
    IpItem(const std::string &string);
    bool isEmpty() const;
    friend std::ostream& operator<<(std::ostream &os, const IpItem &item);
    size_t size() const;
    const std::vector<int>& fields() const;
private:
    std::vector<int> mIpItem;
};
std::ostream& operator<<(std::ostream &os, const IpItem &item);
} // namespace ip_filter
