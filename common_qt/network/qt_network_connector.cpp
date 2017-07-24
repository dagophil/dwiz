#include "qt_network_connector.h"
#include <common/future_utils.h>
#include <common/log/logging.h>

namespace dwiz
{
std::future<ConnectResult>
QtNetworkConnector::connect(std::string const& f_host_name, unsigned int const f_port)
{
    loginfo << "QtNetworkConnector::connect(): Connecting to host \"" << f_host_name
            << "\" at port " << f_port << "." << endlog;
    logerr << "QtNetworkConnector::connect(): TODO: Finish implementation." << endlog;
    return std::future<ConnectResult>();
}
} // namespace dwiz
