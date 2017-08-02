#ifndef DWIZ_COMMON_NETWORK_MAPPED_NETWORK_MESSAGE_NOTIFIER_H
#define DWIZ_COMMON_NETWORK_MAPPED_NETWORK_MESSAGE_NOTIFIER_H

#include <common/dwiz_std.h>
#include <common/network/network_message_notifier_interface.h>

namespace dwiz
{
class MappedNetworkMessageNotifier : public NetworkMessageNotifierInterface
{
public:
    virtual std::pair<MessageId, std::future<NetworkMessage>> registerForNotification() override;

    virtual void setMessage(MessageId const f_messageId, NetworkMessage const& f_message) override;

}; // class MappedNetworkMessageNotifier
} // namespace dwiz

#endif
