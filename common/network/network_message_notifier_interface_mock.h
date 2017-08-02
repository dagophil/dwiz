#ifndef DWIZ_COMMON_NETWORK_NETWORK_MAILBOX_INTERFACE_MOCK_H
#define DWIZ_COMMON_NETWORK_NETWORK_MAILBOX_INTERFACE_MOCK_H

#include <common/dwiz_std.h>
#include <common/network/network_message_notifier_interface.h>
#include <gmock/gmock.h>

namespace dwiz
{
class NetworkMessageNotifierInterfaceMock : public NetworkMessageNotifierInterface
{
public:
    MOCK_METHOD0(registerForNotification, std::pair<MessageId, std::future<std::string>>());
}; // NetworkMessageNotifierInterfaceMock
} // namespace dwiz

#endif
