cmake_minimum_required(VERSION 3.2)
set(MAJOR_VERSION 0)
set(MINOR_VERSION 2)
set(PATCH_VERSION 999)
if($ENV{MAJOR_VERSION})
    set(MAJOR_VERSION $ENV{MAJOR_VERSION})
endif()
if($ENV{MINOR_VERSION})
    set(MINOR_VERSION $ENV{MINOR_VERSION})
endif()
if($ENV{TRAVIS_BUILD_NUMBER})
    set(PATCH_VERSION $ENV{TRAVIS_BUILD_NUMBER})
endif()
project(ip_filter VERSION ${MAJOR_VERSION}.${MAJOR_VERSION}.${PATCH_VERSION})
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
configure_file(version.h.in ${PROJECT_SOURCE_DIR}/version.h)
add_executable(ip_filter main.cpp)
add_library(ipfilter 
    lib.cpp
    ip_item.cpp
    ip_pool.cpp
)
add_executable(test_version test_version.cpp)
add_executable(test_item test_ip_item.cpp)
add_executable(test_pool test_ip_pool.cpp)
set_target_properties(ip_filter ipfilter test_version test_item test_pool PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)
set_target_properties(test_version test_item test_pool PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)
target_link_libraries(ip_filter
    ipfilter
)
target_link_libraries(test_item
    ${Boost_LIBRARIES}
    ipfilter
)
target_link_libraries(test_version
    ${Boost_LIBRARIES}
    ipfilter
)
target_link_libraries(test_pool
    ${Boost_LIBRARIES}
    ipfilter
)
install(TARGETS ip_filter RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT podshivalov.ilya@yandex.ru)
include(CPack)
enable_testing()
add_test(ipfilter_tests_version test_version)
add_test(ipfilter_tests_item test_item)
add_test(ipfilter_tests_pool test_pool)
