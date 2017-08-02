#include "mapped_network_message_notifier.h"
#include <common/dwiz_assert.h>
#include <common/log/logging.h>

namespace dwiz
{
std::pair<MappedNetworkMessageNotifier::MessageId, std::future<NetworkMessage>>
MappedNetworkMessageNotifier::registerForNotification()
{
    logerr << "MappedNetworkMessageNotifier::registerForNotification(): TODO: Implement this."
           << endlog;
    DWIZ_ABORT;
    return std::make_pair(0, std::future<NetworkMessage>());
}

void MappedNetworkMessageNotifier::setMessage(
    MessageId const f_messageId, const NetworkMessage& f_message)
{
    logerr << "MappedNetworkMessageNotifier::setMessage(): TODO: Implement this." << endlog;
    DWIZ_ABORT;
}
} // namespace dwiz
