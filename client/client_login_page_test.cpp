#include <client/client_login_page.h>
#include <common/future_utils.h>
#include <common/network/network_connector_interface_mock.h>
#include <common/protocols/login_protocol_interface_mock.h>
#include <QApplication>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using namespace dwiz;
using testing::DefaultValue;
using testing::InSequence;
using testing::Ref;
using testing::Return;

class ClientLoginPageTest : public testing::Test
{
public:
    QApplication& app() const
    {
        return *m_app;
    }

private:
    virtual void SetUp()
    {
        int argc = 0;
        char** argv = nullptr;
        m_app = std::make_unique<QApplication>(argc, argv);
    }
    virtual void TearDown()
    {
        m_app.reset();
    }
    std::unique_ptr<QApplication> m_app;
}; // class ClientLoginPageTest

TEST_F(ClientLoginPageTest, ConnectAndLoginCallsNetworkAndProtocol)
{
    auto make_connect_result = []() { return make_ready_future<ConnectResult>(ConnectResult{}); };
    DefaultValue<std::future<ConnectResult>>::SetFactory(make_connect_result);
    auto make_login_result = []() { return make_ready_future<LoginResult>(LoginResult{}); };
    DefaultValue<std::future<LoginResult>>::SetFactory(make_login_result);
    auto network_connector = std::make_unique<NetworkConnectorInterfaceMock>();
    auto login_protocol = std::make_unique<LoginProtocolInterfaceMock>();
    {
        InSequence dummy;
        EXPECT_CALL(*network_connector, connect("localhost", 80));
        EXPECT_CALL(*login_protocol, login(Ref(*network_connector), "myUsername", "myPassword"));
    }

    ClientLoginPage login_page;
    login_page.setNetworkConnector(std::move(network_connector));
    login_page.setLoginProtocol(std::move(login_protocol));
    login_page.setHostName("localhost:80");
    login_page.setUserName("myUsername");
    login_page.setPassword("myPassword");

    login_page.connectAndLogin();
}
