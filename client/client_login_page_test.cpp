#include <client/client_login_page.h>
#include <common/future_utils.h>
#include <common/network/network_connector_interface_mock.h>
#include <common/protocols/login_protocol_interface_mock.h>
#include <common_qt/error_handler/qt_error_handler_interface_mock.h>
#include <QApplication>
#include <QLineEdit>
#include <QPushButton>
#include <QSignalSpy>
#include <QTest>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using namespace dwiz;
using testing::_;
using testing::ByMove;
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

TEST_F(ClientLoginPageTest, ValidInputCallsNetworkAndProtocolAndSuccessSignal)
{
    auto error_handler = std::make_unique<QtErrorHandlerInterfaceMock>();
    EXPECT_CALL(*error_handler, showErrorMessage(_, _, _)).Times(0);
    auto network_connector = std::make_unique<NetworkConnectorInterfaceMock>();
    auto login_protocol = std::make_unique<LoginProtocolInterfaceMock>();
    {
        InSequence dummy;
        EXPECT_CALL(*network_connector, connect("localhost", 80))
            .WillOnce(Return(ByMove(makeReadyFuture(ConnectResult{}))));
        EXPECT_CALL(*login_protocol, login(Ref(*network_connector), "myUsername", "myPassword"))
            .WillOnce(Return(ByMove(makeReadyFuture(LoginResult{}))));
    }

    ClientLoginPage login_page;
    QSignalSpy signal_spy(&login_page, &ClientLoginPage::signalLoginSuccess);
    login_page.setErrorHandler(std::move(error_handler));
    login_page.setNetworkConnector(std::move(network_connector));
    login_page.setLoginProtocol(std::move(login_protocol));
    QTest::keyClicks(&login_page.getHostNameInputField(), "localhost:80");
    QTest::keyClicks(&login_page.getUserNameInputField(), "myUsername");
    QTest::keyClicks(&login_page.getPasswordInputField(), "myPassword");
    QTest::mouseClick(&login_page.getLoginButton(), Qt::LeftButton);
    EXPECT_EQ(signal_spy.count(), 1);
}
