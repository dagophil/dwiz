#include "json_login_protocol_v0.h"
#include <common/log/logging.h>
#include <common/network/network_connector_interface.h>
#include <common/string_utils.h>
#include <exception>
#include <tuple>

namespace dwiz
{
std::future<LoginResult> JsonLoginProtocolV0::login(
    NetworkConnectorInterface& f_networkConnector,
    std::string const& f_username,
    std::string const& f_password)
{
    logerr << "JsonLoginProtocolV0::login(): TODO: Allow to chain futures." << endlog;
    logerr << "JsonLoginProtocolV0::login(): TODO: Finish implementation." << endlog;
    logerr << "JsonLoginProtocolV0::login(): TODO: Test this function." << endlog;
    return std::future<LoginResult>();
}
} // namespace dwiz
