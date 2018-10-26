#include "lib.h"
#include "version.h"

namespace ip_filter {
namespace version {
std::string version() {
    std::string version = std::to_string(versionMajor()) + "." +
                          std::to_string(versionMinor()) + "." +
                          std::to_string(versionPatch());
    return version;
}

int versionMajor() {
    return PROJECT_VERSION_MAJOR;
}

int versionMinor() {
    return PROJECT_VERSION_MINOR;
}

int versionPatch() {
    return PROJECT_VERSION_PATCH;
}
} // namespace version
} // namespace ip_filter
