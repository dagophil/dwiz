#ifndef DWIZ_COMMON_PROTOCOLS_LOGIN_PROTOCOL_INTERFACE_MOCK_H
#define DWIZ_COMMON_PROTOCOLS_LOGIN_PROTOCOL_INTERFACE_MOCK_H

#include <common/dwiz_std.h>
#include <common/protocols/login_protocol_interface.h>
#include <gmock/gmock.h>

namespace dwiz
{
class LoginProtocolInterfaceMock : public LoginProtocolInterface
{
public:
    MOCK_METHOD3(
        login,
        std::future<LoginResult>(
            NetworkConnectorInterface&, std::string const&, std::string const&));
}; // class LoginProtocolInterfaceMock
} // namespace dwiz

#endif
