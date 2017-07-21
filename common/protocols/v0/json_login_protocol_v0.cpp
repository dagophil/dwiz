#include "json_login_protocol_v0.h"
#include <common/log/logging.h>

namespace dwiz
{
JsonLoginProtocolV0::JsonLoginProtocolV0(
    const std::shared_ptr<NetworkConnectorInterface>& f_networkConnector)
    : m_networkConnector(f_networkConnector)
{
}

JsonLoginProtocolV0::~JsonLoginProtocolV0() = default;

std::future<LoginResult> JsonLoginProtocolV0::login(
    std::string const& f_host_name, std::string const& f_user_name, std::string const& f_password)
{
    loginfo << "JsonLoginProtocolV0::login()" << endlog;
    return std::future<LoginResult>();
}
} // namespace dwiz
