#define BOOST_TEST_MODULE ip_filter_test_module
#include "lib.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ip_filter_test_suite)
BOOST_AUTO_TEST_CASE(ip_filter_test_version) {
    BOOST_CHECK(ip_filter::version::versionMajor() >= 0);
    BOOST_CHECK(ip_filter::version::versionMinor() >= 0);
    BOOST_CHECK(ip_filter::version::versionPatch() > 0);
    std::string _version = std::to_string(ip_filter::version::versionMajor()) + "." +
        std::to_string(ip_filter::version::versionMinor()) + "." +
        std::to_string(ip_filter::version::versionPatch());
    BOOST_CHECK(ip_filter::version::version().compare(_version) == 0);
}
BOOST_AUTO_TEST_SUITE_END()
