#ifndef DWIZ_COMMON_NETWORK_NETWORK_CONNECTOR_INTERFACE_MOCK_H
#define DWIZ_COMMON_NETWORK_NETWORK_CONNECTOR_INTERFACE_MOCK_H

#include <common/dwiz_std.h>
#include <common/network/network_connector_interface.h>
#include <gmock/gmock.h>

namespace dwiz
{
class NetworkConnectorInterfaceMock : public NetworkConnectorInterface
{
public:
    MOCK_METHOD2(connect, std::future<ConnectResult>(std::string const&, unsigned int const));
}; // class NetworkConnectorInterfaceMock
} // namespace dwiz

#endif
