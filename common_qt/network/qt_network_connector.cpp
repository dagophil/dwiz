#include "qt_network_connector.h"
#include <common/dwiz_assert.h>
#include <common/future_utils.h>
#include <common/log/logging.h>
#include <common/network/network_message_notifier_interface.h>

namespace dwiz
{
QtNetworkConnector::QtNetworkConnector(
    std::unique_ptr<NetworkMessageNotifierInterface> f_messageNotifier)
    : m_messageNotifier(std::move(f_messageNotifier))
{
}

QtNetworkConnector::~QtNetworkConnector() = default;

std::future<ConnectResult>
QtNetworkConnector::connect(std::string const& f_host_name, unsigned int const f_port)
{
    loginfo << "QtNetworkConnector::connect(): Connecting to host \"" << f_host_name
            << "\" at port " << f_port << "." << endlog;
    logerr << "QtNetworkConnector::connect(): TODO: Implement this." << endlog;
    DWIZ_ABORT;
    return std::future<ConnectResult>();
}

void QtNetworkConnector::send(std::string const& f_message)
{
    logerr << "QtNetworkConnector::send(): TODO: Implement this." << endlog;
    DWIZ_ABORT;
}

std::future<NetworkMessage> QtNetworkConnector::send(std::string const& f_message, AwaitReplyT)
{
    logerr << "QtNetworkConnector::send(): TODO: Implement this." << endlog;
    DWIZ_ABORT;
    return std::future<NetworkMessage>();
}
} // namespace dwiz
