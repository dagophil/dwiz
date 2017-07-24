#ifndef DWIZ_COMMON_PROTOCOLS_V0_JSON_LOGIN_PROTOCOL_H
#define DWIZ_COMMON_PROTOCOLS_V0_JSON_LOGIN_PROTOCOL_H

#include <common/dwiz_std.h>
#include <common/protocols/login_protocol_interface.h>
#include <memory>

namespace dwiz
{
class NetworkConnectorInterface;

class JsonLoginProtocolV0 : public LoginProtocolInterface
{
public:
    virtual std::future<LoginResult> login(
        NetworkConnectorInterface& f_networkConnector,
        std::string const& f_user_name,
        std::string const& f_password) override;

}; // class JsonLoginProtocol
} // namespace dwiz

#endif
