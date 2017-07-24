#ifndef DWIZ_COMMON_PROTOCOLS_LOGIN_PROTOCOL_INTERFACE_H
#define DWIZ_COMMON_PROTOCOLS_LOGIN_PROTOCOL_INTERFACE_H

#include <common/dwiz_std.h>
#include <future>
#include <stdexcept>
#include <string>

namespace dwiz
{
class NetworkConnectorInterface;

class LoginResult
{
};

class LoginProtocolInterface
{
public:
    virtual ~LoginProtocolInterface() = default;

    /// Establishes a connection on the network connector and exchanges login data.
    virtual std::future<LoginResult> login(
        NetworkConnectorInterface& f_networkConnector,
        std::string const& f_user_name,
        std::string const& f_password) = 0;
}; // class LoginProtocolInterface

class LoginError : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
}; // class LoginError

} // namespace dwiz

#endif
