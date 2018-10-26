#define BOOST_TEST_MODULE ip_pool_test_module
#include "ip_pool.h"
#include <boost/test/unit_test.hpp>
#include <string>

using namespace std::string_literals;

BOOST_AUTO_TEST_SUITE(ip_filter_test_suite)

auto stringifyItem(const ip_filter::IpItem &item) -> std::string {
    std::string result;
    for (auto field = item.fields().begin();
            field != item.fields().end();
            ++field) {
        if (field != item.fields().begin()) {
            result += "."s;
        }
        result += *field;
    }
    return result;
}

BOOST_AUTO_TEST_CASE(ip_pool_sort_test) {
    std::vector<std::string> orderedData({
            "9.7.5.2"s,
            "8.6.4.3"s,
            "3.4.6.8"s,
            "2.5.7.9"s,
            "1.3.5.7"s,
            });
    std::vector<std::string> unorderedData({
            "2.5.7.9"s,
            "3.4.6.8"s,
            "1.3.5.7"s,
            "9.7.5.2"s,
            "8.6.4.3"s,
            });
    ip_filter::IpPool pool(std::move(unorderedData));
    BOOST_CHECK(!pool.items().empty());
    BOOST_CHECK_EQUAL(pool.items().size(), orderedData.size());
    pool.rsort();
    BOOST_CHECK(!pool.items().empty());
    BOOST_CHECK_EQUAL(pool.items().size(), orderedData.size());
    for (size_t i = 0; i < pool.items().size(); ++i) {
        BOOST_CHECK_EQUAL(orderedData[i], stringifyItem(pool.items().at(i)));
    }
}

BOOST_AUTO_TEST_CASE(ip_pool_filter_1_test) {
    std::vector<std::string> testData({
            "9.7.5.2"s,
            "8.6.4.3"s,
            "8.1.4.3"s,
            "3.4.6.8"s,
            "3.4.1.8"s,
            "2.5.7.9"s,
            "2.5.7.1"s,
            "1.1.1.1"s,
            "1.1.1.7"s,
            "1.1.5.7"s,
            "1.3.5.7"s,
            });
    std::vector<std::string> testResult({
            "1.1.1.1"s,
            "1.1.1.7"s,
            "1.1.5.7"s,
            "1.3.5.7"s,
            });
    auto size = testData.size();
    ip_filter::IpPool pool(std::move(testData));
    BOOST_CHECK(!pool.items().empty());
    BOOST_CHECK_EQUAL(pool.items().size(), size);
    auto result = pool.filter(1);
    BOOST_CHECK(!result.items().empty());
    BOOST_CHECK_EQUAL(result.items().size(), testResult.size());
    for (size_t i = 0; i < result.items().size(); ++i) {
        BOOST_CHECK_EQUAL(testResult[i], stringifyItem(result.items().at(i)));
    }
}

BOOST_AUTO_TEST_CASE(ip_pool_filter_2_test) {
    std::vector<std::string> testData({
            "9.7.5.2"s,
            "8.6.4.3"s,
            "8.1.4.3"s,
            "3.4.6.8"s,
            "3.4.1.8"s,
            "2.5.7.9"s,
            "2.5.7.1"s,
            "1.1.1.1"s,
            "1.1.1.7"s,
            "1.1.5.7"s,
            "1.3.5.7"s,
            });
    std::vector<std::string> testResult({
            "1.1.1.1"s,
            "1.1.1.7"s,
            "1.1.5.7"s,
            });
    auto size = testData.size();
    ip_filter::IpPool pool(std::move(testData));
    BOOST_CHECK(!pool.items().empty());
    BOOST_CHECK_EQUAL(pool.items().size(), size);
    auto result = pool.filter(1, 1);
    BOOST_CHECK(!result.items().empty());
    BOOST_CHECK_EQUAL(result.items().size(), testResult.size());
    for (size_t i = 0; i < result.items().size(); ++i) {
        BOOST_CHECK_EQUAL(testResult[i], stringifyItem(result.items().at(i)));
    }
}

BOOST_AUTO_TEST_CASE(ip_pool_filter_3_test) {
    std::vector<std::string> testData({
            "9.7.5.2"s,
            "8.6.4.3"s,
            "8.1.4.3"s,
            "3.4.6.8"s,
            "3.4.1.8"s,
            "2.5.7.9"s,
            "2.5.7.1"s,
            "1.1.1.1"s,
            "1.1.1.7"s,
            "1.1.5.7"s,
            "1.3.5.7"s,
            });
    std::vector<std::string> testResult({
            "1.1.1.1"s,
            "1.1.1.7"s,
            });
    auto size = testData.size();
    ip_filter::IpPool pool(std::move(testData));
    BOOST_CHECK(!pool.items().empty());
    BOOST_CHECK_EQUAL(pool.items().size(), size);
    auto result = pool.filter(1, 1, 1);
    BOOST_CHECK(!result.items().empty());
    BOOST_CHECK_EQUAL(result.items().size(), testResult.size());
    for (size_t i = 0; i < result.items().size(); ++i) {
        BOOST_CHECK_EQUAL(testResult[i], stringifyItem(result.items().at(i)));
    }
}

BOOST_AUTO_TEST_CASE(ip_pool_filter_4_test) {
    std::vector<std::string> testData({
            "9.7.5.2"s,
            "8.6.4.3"s,
            "8.1.4.3"s,
            "3.4.6.8"s,
            "3.4.1.8"s,
            "2.5.7.9"s,
            "2.5.7.1"s,
            "1.1.1.1"s,
            "1.1.1.7"s,
            "1.1.5.7"s,
            "1.3.5.7"s,
            });
    std::vector<std::string> testResult({
            "1.1.1.1"s,
            });
    auto size = testData.size();
    ip_filter::IpPool pool(std::move(testData));
    BOOST_CHECK(!pool.items().empty());
    BOOST_CHECK_EQUAL(pool.items().size(), size);
    auto result = pool.filter(1, 1, 1, 1);
    BOOST_CHECK(!result.items().empty());
    BOOST_CHECK_EQUAL(result.items().size(), testResult.size());
    for (size_t i = 0; i < result.items().size(); ++i) {
        BOOST_CHECK_EQUAL(testResult[i], stringifyItem(result.items().at(i)));
    }
}

BOOST_AUTO_TEST_CASE(ip_pool_filter_any_test) {
    std::vector<std::string> testData({
            "9.7.5.2"s,
            "8.6.4.3"s,
            "8.1.4.3"s,
            "3.4.6.8"s,
            "3.4.1.8"s,
            "2.5.7.9"s,
            "2.5.7.1"s,
            "1.1.1.1"s,
            "1.1.1.7"s,
            "1.1.5.7"s,
            "1.3.5.7"s,
            });
    std::vector<std::string> testResult({
            "8.1.4.3"s,
            "3.4.1.8"s,
            "2.5.7.1"s,
            "1.1.1.1"s,
            "1.1.1.7"s,
            "1.1.5.7"s,
            "1.3.5.7"s,
            });
    auto size = testData.size();
    ip_filter::IpPool pool(std::move(testData));
    BOOST_CHECK(!pool.items().empty());
    BOOST_CHECK_EQUAL(pool.items().size(), size);
    auto result = pool.filter_any(1);
    BOOST_CHECK(!result.items().empty());
    BOOST_CHECK_EQUAL(result.items().size(), testResult.size());
    for (size_t i = 0; i < result.items().size(); ++i) {
        BOOST_CHECK_EQUAL(testResult[i], stringifyItem(result.items().at(i)));
    }
}

BOOST_AUTO_TEST_SUITE_END()
