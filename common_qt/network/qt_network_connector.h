#ifndef DWIZ_COMMON_QT_NETWORK_QT_NETWORK_CONNECTOR_H
#define DWIZ_COMMON_QT_NETWORK_QT_NETWORK_CONNECTOR_H

#include <common/dwiz_std.h>
#include <common/network/network_connector_interface.h>

namespace dwiz
{
class QtNetworkConnector : public NetworkConnectorInterface
{
    // NetworkConnectorInterface interface
public:
    virtual std::future<ConnectResult>
    connect(std::string const& f_host_name, unsigned int const f_port) override;
}; // class QtNetworkConnector
} // namespace dwiz

#endif
