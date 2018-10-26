#pragma once
#include <string>
#include "ip_pool.h"

namespace ip_filter {
namespace version {
std::string version();
int versionMajor();
int versionMinor();
int versionPatch();
} // namespace version
} // namespace ip_filter
