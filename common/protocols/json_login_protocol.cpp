#include "json_login_protocol.h"
#include <common/log/logging.h>

namespace dwiz
{
JsonLoginProtocol::JsonLoginProtocol(
    const std::shared_ptr<NetworkConnectorInterface>& f_networkConnector)
    : m_networkConnector(f_networkConnector)
{
}

JsonLoginProtocol::~JsonLoginProtocol() = default;

std::future<LoginResult> JsonLoginProtocol::login(
    std::string const& f_host_name, std::string const& f_user_name, std::string const& f_password)
{
    loginfo << "JsonLoginProtocol::login()" << endlog;
    return std::future<LoginResult>();
}
} // namespace dwiz
