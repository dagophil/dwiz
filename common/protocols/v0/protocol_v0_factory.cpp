#include "protocol_v0_factory.h"
#include <common/protocols/v0/json_login_protocol_v0.h>

namespace dwiz
{
std::unique_ptr<dwiz::LoginProtocolInterface> dwiz::ProtocolV0Factory::createLoginProtocol(
    std::shared_ptr<dwiz::NetworkConnectorInterface> const& f_networkConnector)
{
    return std::make_unique<JsonLoginProtocolV0>(f_networkConnector);
}
} // namespace dwiz
