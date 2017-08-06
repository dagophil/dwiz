#include "qt_network_connector.h"
#include <common/dwiz_assert.h>
#include <common/future_utils.h>
#include <common/log/logger.h>
#include <common/network/network_message_notifier_interface.h>

DWIZ_DEFINE_LOGGER("common_qt.network.qt_network_connector");

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
    DWIZ_LOG_INFO(
        "QtNetworkConnector::connect(): Connecting to host \"" << f_host_name << "\" at port "
                                                               << f_port
                                                               << ".");
    DWIZ_LOG_ERROR("QtNetworkConnector::connect(): TODO: Implement this.");
    DWIZ_ABORT;
    return std::future<ConnectResult>();
}

void QtNetworkConnector::send(std::string const& f_message)
{
    DWIZ_LOG_ERROR("QtNetworkConnector::send(): TODO: Implement this.");
    DWIZ_ABORT;
}

std::future<NetworkMessage> QtNetworkConnector::send(std::string const& f_message, AwaitReplyT)
{
    DWIZ_LOG_ERROR("QtNetworkConnector::send(): TODO: Implement this.");
    DWIZ_ABORT;
    return std::future<NetworkMessage>();
}
} // namespace dwiz
