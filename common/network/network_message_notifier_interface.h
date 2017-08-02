#ifndef DWIZ_COMMON_NETWORK_MESSAGE_NOTIFIER_INTERFACE_H
#define DWIZ_COMMON_NETWORK_MESSAGE_NOTIFIER_INTERFACE_H

#include <common/dwiz_std.h>
#include <cstdint>
#include <future>
#include <string>
#include <utility>

namespace dwiz
{
class NetworkMessage;

class NetworkMessageNotifierInterface
{
public:
    using MessageId = int;

    virtual ~NetworkMessageNotifierInterface() = default;

    /// Registers a notifier and returns the message id that can be used to set the notification and
    /// the future that contains the set value.
    virtual std::pair<MessageId, std::future<NetworkMessage>> registerForNotification() = 0;

    /// Sets the value of the future with id f_messageId to f_message.
    virtual void setMessage(MessageId const f_messageId, NetworkMessage const& f_message) = 0;

}; // class NetworkMessageNotifierInterface
} // namespace dwiz

#endif
