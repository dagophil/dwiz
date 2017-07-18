#include <client/client_login_page.h>
#include <common/protocols/login_protocol_interface.h>
#include <QApplication>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace dwiz;

class MockLoginProtocol : public LoginProtocolInterface
{
public:
    virtual ~MockLoginProtocol() = default;
    MOCK_METHOD3(
            login,
            std::future<LoginResult>(std::string const&, std::string const&, std::string const&)
    );
};

TEST(ClientLoginPage, TestLoginCallsProtocol)
{
    int argc = 0;
    char** argv = nullptr;
    QApplication app(argc, argv);
    DWIZ_UNUSED(app);

    ClientLoginPage login_page;

    auto login_protocol = std::make_unique<MockLoginProtocol>();
    EXPECT_CALL(*login_protocol, login("", "", "")).Times(1);
    login_page.setLoginProtocol(std::move(login_protocol));

    login_page.login();
}
