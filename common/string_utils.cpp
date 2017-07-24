#include "string_utils.h"
#include <stdexcept>

namespace dwiz
{
std::pair<std::string, unsigned int> splitHostAndPort(std::string const& f_hostAndPort)
{
    auto const colon_index = f_hostAndPort.find_last_of(':');
    if (colon_index == std::string::npos)
    {
        throw std::runtime_error("Host name \"" + f_hostAndPort + "\" does not contain \":\".");
    }
    if (colon_index == 0)
    {
        throw std::runtime_error("Host name is empty.");
    }
    if (colon_index + 1 == f_hostAndPort.size())
    {
        throw std::runtime_error("Port name is empty.");
    }
    auto const host = f_hostAndPort.substr(0, colon_index);
    auto const port_string = f_hostAndPort.substr(colon_index + 1);
    int port = 0;
    size_t number_of_processed_characters = 0;
    try
    {
        port = std::stoi(port_string, &number_of_processed_characters);
    }
    catch (std::exception const&)
    {
        throw std::runtime_error("Failed to parse port string \"" + port_string + "\" as number.");
    }
    if (number_of_processed_characters != port_string.size())
    {
        throw std::runtime_error(
            "Parsed port string \"" + port_string
            + "\" to number, but there were remaining characters.");
    }
    if (port < 0)
    {
        throw std::runtime_error("Port must not be negative, received " + port_string + ".");
    }
    return {host, port};
}
} // namespace dwiz
