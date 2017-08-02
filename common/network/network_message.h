#ifndef DWIZ_COMMON_NETWORK_NETWORK_MESSAGE_H
#define DWIZ_COMMON_NETWORK_NETWORK_MESSAGE_H

#include <common/dwiz_std.h>
#include <cstdint>
#include <string>

namespace dwiz
{
class NetworkMessage
{
public:
    std::uint32_t m_replyToId;
    std::string m_message;
}; // class NetworkMessage
} // namespace dwiz

#endif
