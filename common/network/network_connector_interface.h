#ifndef DWIZ_COMMON_NETWORK_NETWORK_CONNECTOR_INTERFACE_H
#define DWIZ_COMMON_NETWORK_NETWORK_CONNECTOR_INTERFACE_H

#include <common/dwiz_std.h>
#include <future>

namespace dwiz
{
class ConnectResult
{
};

class NetworkConnectorInterface
{
public:
    virtual ~NetworkConnectorInterface() = default;
    virtual std::future<ConnectResult>
    connect(std::string const& f_host_name, unsigned int const f_port) = 0;
};
} // namespace dwiz

#endif
