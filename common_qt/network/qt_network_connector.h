#ifndef DWIZ_COMMON_QT_NETWORK_QT_NETWORK_CONNECTOR_H
#define DWIZ_COMMON_QT_NETWORK_QT_NETWORK_CONNECTOR_H

#include <common/dwiz_std.h>
#include <common/network/network_connector_interface.h>

namespace dwiz
{
class NetworkMessageNotifierInterface;

class QtNetworkConnector : public NetworkConnectorInterface
{
public:
    QtNetworkConnector(std::unique_ptr<NetworkMessageNotifierInterface> f_messageNotifier);
    ~QtNetworkConnector();

    virtual std::future<ConnectResult>
    connect(std::string const& f_host_name, unsigned int const f_port) override;

    virtual void send(std::string const& f_message) override;

    virtual std::future<NetworkMessage> send(std::string const& f_message, AwaitReplyT) override;

private:
    std::unique_ptr<NetworkMessageNotifierInterface> m_messageNotifier;
}; // class QtNetworkConnector
} // namespace dwiz

#endif
