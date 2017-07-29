#ifndef DWIZ_COMMON_NETWORK_NETWORK_CONNECTOR_INTERFACE_H
#define DWIZ_COMMON_NETWORK_NETWORK_CONNECTOR_INTERFACE_H

#include <common/dwiz_std.h>
#include <future>
#include <stdexcept>

namespace dwiz
{
class ConnectResult
{
};

class NetworkConnectorInterface
{
public:
    virtual ~NetworkConnectorInterface() = default;

    /// Connects to f_host_name at port f_port.
    /// The returned future is always valid, but it may not be ready.
    /// Throws a NetworkConnectorError if the request fails.
    virtual std::future<ConnectResult>
    connect(std::string const& f_host_name, unsigned int const f_port) = 0;
};

class NetworkConnectorError : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
}; // class NetworkConnectorError

} // namespace dwiz

#endif
