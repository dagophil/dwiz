#include "qt_network_connector_factory.h"
#include <common_qt/network/qt_network_connector.h>

namespace dwiz
{
std::unique_ptr<NetworkConnectorInterface> QtNetworkConnectorFactory::createNetworkConnector()
{
    return std::make_unique<QtNetworkConnector>();
}
} // namespace dwiz
