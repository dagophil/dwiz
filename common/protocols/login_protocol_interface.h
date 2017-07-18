#ifndef DWIZ_COMMON_PROTOCOLS_LOGIN_PROTOCOL_INTERFACE_H
#define DWIZ_COMMON_PROTOCOLS_LOGIN_PROTOCOL_INTERFACE_H

#include <common/dwiz_std.h>
#include <future>
#include <string>

namespace dwiz
{
    class LoginResult
    {};

    class LoginProtocolInterface
    {
    public:
        virtual ~LoginProtocolInterface() = default;
        virtual std::future<LoginResult> login(
                std::string const& f_host_name,
                std::string const& f_user_name,
                std::string const& f_password
        ) = 0;
    };  // class LoginProtocolInterface
}  // namespace dwiz

#endif
