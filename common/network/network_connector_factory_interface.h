#ifndef DWIZ_COMMON_NETWORK_NETWORK_CONNECTOR_FACTORY_INTERFACE_H
#define DWIZ_COMMON_NETWORK_NETWORK_CONNECTOR_FACTORY_INTERFACE_H

#include <common/network/network_connector_interface.h>
#include <memory>

namespace dwiz
{
class NetworkConnectorFactoryInterface
{
public:
    virtual ~NetworkConnectorFactoryInterface() = default;
    virtual std::unique_ptr<NetworkConnectorInterface> createNetworkConnector() = 0;
}; // class NetworkConnectorFactoryInterface
} // namespace dwiz

#endif
