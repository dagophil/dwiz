#include "mapped_network_message_notifier.h"
#include <common/dwiz_assert.h>
#include <common/log/logger.h>

DWIZ_DEFINE_LOGGER("common.network.mapped_network_message_notifier");

namespace dwiz
{
std::pair<MappedNetworkMessageNotifier::MessageId, std::future<NetworkMessage>>
MappedNetworkMessageNotifier::registerForNotification()
{
    DWIZ_LOG_ERROR(
        "MappedNetworkMessageNotifier::registerForNotification(): TODO: Implement this.");
    DWIZ_ABORT;
    return std::make_pair(0, std::future<NetworkMessage>());
}

void MappedNetworkMessageNotifier::setMessage(
    MessageId const f_messageId, const NetworkMessage& f_message)
{
    DWIZ_LOG_ERROR("MappedNetworkMessageNotifier::setMessage(): TODO: Implement this.");
    DWIZ_ABORT;
}
} // namespace dwiz
