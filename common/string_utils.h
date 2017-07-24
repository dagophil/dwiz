#ifndef DWIZ_COMMON_STRING_UTILS_H
#define DWIZ_COMMON_STRING_UTILS_H

#include <common/dwiz_std.h>
#include <string>
#include <utility>

namespace dwiz
{
/// Splits a string of the format "host:port" into host and port.
/// Throws std::runtime_error if the string could not be parsed.
std::pair<std::string, unsigned int> splitHostAndPort(std::string const& f_hostAndPort);
} // namespace dwiz

#endif
