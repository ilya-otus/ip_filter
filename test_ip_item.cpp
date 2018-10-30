#define BOOST_TEST_MODULE ip_item_test_module
#include "ip_item.h"
#include <boost/test/unit_test.hpp>
#include <string>
#include <map>

BOOST_AUTO_TEST_SUITE(ip_filter_test_suite)

BOOST_AUTO_TEST_CASE(ip_item_test) {
    std::map<std::string, int> testItemSizeSamples;
    std::string field = "1";
    for (int i = 1; i < 6; ++i) {
        std::string line = field;
        for (int j = 0; j < 4; ++j) {
            testItemSizeSamples[line] = i;
            line += "\t1";
        }
        field += ".1";
    }
    for (auto [test, count] : testItemSizeSamples) {
        auto item = ip_filter::IpItem(test);
        BOOST_CHECK(!item.isEmpty());
        BOOST_CHECK_EQUAL(item.size(), count);
    }
}

BOOST_AUTO_TEST_CASE(ip_item_parsing_test) {
    ip_filter::IpItem item("1.2.3.4\t1\t2");
    std::vector<int> rawItem({1,2,3,4});
    BOOST_CHECK_EQUAL(item.size(), rawItem.size());
    for (size_t i = 0; i < item.size(); ++i) {
        BOOST_CHECK(item.fields()[i] == rawItem[i]);
    }
}

BOOST_AUTO_TEST_SUITE_END()
