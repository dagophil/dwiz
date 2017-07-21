#ifndef DWIZ_COMMON_QT_NETWORK_QT_NETWORK_CONNECTOR_FACTORY_H
#define DWIZ_COMMON_QT_NETWORK_QT_NETWORK_CONNECTOR_FACTORY_H

#include <common/dwiz_std.h>
#include <common/network/network_connector_factory_interface.h>

namespace dwiz
{
class QtNetworkConnectorFactory : public NetworkConnectorFactoryInterface
{
public:
    virtual std::unique_ptr<NetworkConnectorInterface> createNetworkConnector() override;
}; // class QtNetworkConnectorFactory
} // namespace dwiz

#endif
