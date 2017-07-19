#ifndef DWIZ_COMMON_PROTOCOLS_JSON_LOGIN_PROTOCOL_H
#define DWIZ_COMMON_PROTOCOLS_JSON_LOGIN_PROTOCOL_H

#include <common/dwiz_std.h>
#include <common/protocols/login_protocol_interface.h>
#include <memory>

namespace dwiz
{
class NetworkConnectorInterface;

class JsonLoginProtocol : public LoginProtocolInterface
{
public:
    JsonLoginProtocol(std::shared_ptr<NetworkConnectorInterface> const& f_networkConnector);
    ~JsonLoginProtocol();

    virtual std::future<LoginResult> login(
        std::string const& f_host_name,
        std::string const& f_user_name,
        std::string const& f_password) override;

private:
    std::shared_ptr<NetworkConnectorInterface> m_networkConnector;

}; // class JsonLoginProtocol
} // namespace dwiz

#endif
