#ifndef DWIZ_COMMON_PROTOCOLS_PROTOCOL_FACTORY_INTERFACE_H
#define DWIZ_COMMON_PROTOCOLS_PROTOCOL_FACTORY_INTERFACE_H

#include <common/dwiz_std.h>
#include <memory>

namespace dwiz
{
class LoginProtocolInterface;
class NetworkConnectorInterface;

class ProtocolFactoryInterface
{
public:
    virtual ~ProtocolFactoryInterface() = default;
    virtual std::unique_ptr<LoginProtocolInterface>
    createLoginProtocol(std::shared_ptr<NetworkConnectorInterface> const& f_networkConnector) = 0;

}; // class ProtocolFactoryInterface
} // namespace dwiz

#endif
