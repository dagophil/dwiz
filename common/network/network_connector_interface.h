#ifndef DWIZ_COMMON_NETWORK_NETWORK_CONNECTOR_INTERFACE_H
#define DWIZ_COMMON_NETWORK_NETWORK_CONNECTOR_INTERFACE_H

#include <common/dwiz_std.h>
#include <future>
#include <stdexcept>

namespace dwiz
{
class NetworkMessage;

class ConnectResult
{
};

typedef struct AwaitReplyT
{
} AwaitReply;

class NetworkConnectorInterface
{
public:
    virtual ~NetworkConnectorInterface() = default;

    /// Connects to f_host_name at port f_port.
    /// The returned future is always valid, but it may not be ready.
    /// Throws a NetworkConnectorError if the request fails.
    virtual std::future<ConnectResult>
    connect(std::string const& f_host_name, unsigned int const f_port) = 0;

    /// Sends the message.
    /// Throws an exception if called before getting a valid ConnectResult from connect().
    virtual void send(std::string const& f_message) = 0;

    /// Sends the message and returns a future on which can be waited for the response.
    /// Throws an exception if called before getting a valid ConnectResult from connect().
    virtual std::future<NetworkMessage> send(std::string const& f_message, AwaitReplyT) = 0;
};

class NetworkConnectorError : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
}; // class NetworkConnectorError

} // namespace dwiz

#endif
