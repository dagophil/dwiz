#include "qt_network_connector_factory.h"
#include <common/network/mapped_network_message_notifier.h>
#include <common_qt/network/qt_network_connector.h>

namespace dwiz
{
std::unique_ptr<NetworkConnectorInterface> QtNetworkConnectorFactory::createNetworkConnector()
{
    return std::make_unique<QtNetworkConnector>(std::make_unique<MappedNetworkMessageNotifier>());
}
} // namespace dwiz
