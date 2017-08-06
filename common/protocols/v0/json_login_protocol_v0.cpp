#include "json_login_protocol_v0.h"
#include <common/dwiz_assert.h>
#include <common/log/logger.h>
#include <common/network/network_connector_interface.h>
#include <common/string_utils.h>
#include <exception>
#include <tuple>

DWIZ_DEFINE_LOGGER("common.protocols.json_login_protocol_v0");

namespace dwiz
{
std::future<LoginResult> JsonLoginProtocolV0::login(
    NetworkConnectorInterface& f_networkConnector,
    std::string const& f_username,
    std::string const& f_password)
{
    DWIZ_LOG_ERROR("JsonLoginProtocolV0::login(): TODO: Finish implementation.");
    DWIZ_ABORT;
    return std::future<LoginResult>();
}
} // namespace dwiz
