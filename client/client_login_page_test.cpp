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
using testing::Throw;

class ClientLoginPageTest : public testing::Test
{
public:
    std::unique_ptr<QtErrorHandlerInterfaceMock> m_error_handler;
    std::unique_ptr<NetworkConnectorInterfaceMock> m_network_connector;
    std::unique_ptr<LoginProtocolInterfaceMock> m_login_protocol;

    void moveHandlersTo(ClientLoginPage& f_login_page)
    {
        f_login_page.setErrorHandler(std::move(m_error_handler));
        f_login_page.setNetworkConnector(std::move(m_network_connector));
        f_login_page.setLoginProtocol(std::move(m_login_protocol));
    }

private:
    virtual void SetUp()
    {
        int argc = 0;
        char** argv = nullptr;
        m_app = std::make_unique<QApplication>(argc, argv);
        m_error_handler = std::make_unique<QtErrorHandlerInterfaceMock>();
        m_network_connector = std::make_unique<NetworkConnectorInterfaceMock>();
        m_login_protocol = std::make_unique<LoginProtocolInterfaceMock>();
    }
    virtual void TearDown()
    {
        m_login_protocol.reset();
        m_network_connector.reset();
        m_error_handler.reset();
        m_app.reset();
    }

    std::unique_ptr<QApplication> m_app;
}; // class ClientLoginPageTest

TEST_F(ClientLoginPageTest, ValidInputCallsNetworkAndProtocolAndSuccessSignal)
{
    EXPECT_CALL(*m_error_handler, showErrorMessage(_, _, _)).Times(0);
    {
        InSequence dummy;
        EXPECT_CALL(*m_network_connector, connect("localhost", 80))
            .WillOnce(Return(ByMove(makeReadyFuture(ConnectResult{}))));
        EXPECT_CALL(*m_login_protocol, login(Ref(*m_network_connector), "myUsername", "myPassword"))
            .WillOnce(Return(ByMove(makeReadyFuture(LoginResult{}))));
    }
    ClientLoginPage login_page;
    moveHandlersTo(login_page);
    QSignalSpy signal_spy(&login_page, &ClientLoginPage::signalLoginSuccess);
    QTest::keyClicks(&login_page.getHostNameInputField(), "localhost:80");
    QTest::keyClicks(&login_page.getUserNameInputField(), "myUsername");
    QTest::keyClicks(&login_page.getPasswordInputField(), "myPassword");
    QTest::mouseClick(&login_page.getLoginButton(), Qt::LeftButton);
    EXPECT_EQ(signal_spy.count(), 1);
}

TEST_F(ClientLoginPageTest, NoPortShowsErrorMessage)
{
    EXPECT_CALL(*m_error_handler, showErrorMessage(_, _, _)).Times(1);
    EXPECT_CALL(*m_network_connector, connect(_, _)).Times(0);
    EXPECT_CALL(*m_login_protocol, login(_, _, _)).Times(0);
    ClientLoginPage login_page;
    moveHandlersTo(login_page);
    QSignalSpy signal_spy(&login_page, &ClientLoginPage::signalLoginSuccess);
    QTest::keyClicks(&login_page.getHostNameInputField(), "localhost");
    QTest::mouseClick(&login_page.getLoginButton(), Qt::LeftButton);
    EXPECT_EQ(signal_spy.count(), 0);
}

TEST_F(ClientLoginPageTest, NoHostShowsErrorMessage)
{
    EXPECT_CALL(*m_error_handler, showErrorMessage(_, _, _)).Times(1);
    EXPECT_CALL(*m_network_connector, connect(_, _)).Times(0);
    EXPECT_CALL(*m_login_protocol, login(_, _, _)).Times(0);
    ClientLoginPage login_page;
    moveHandlersTo(login_page);
    QSignalSpy signal_spy(&login_page, &ClientLoginPage::signalLoginSuccess);
    QTest::keyClicks(&login_page.getHostNameInputField(), "80");
    QTest::mouseClick(&login_page.getLoginButton(), Qt::LeftButton);
    EXPECT_EQ(signal_spy.count(), 0);
}

TEST_F(ClientLoginPageTest, ThrowFromNetworkConnectorShowsErrorMessage)
{
    {
        InSequence dummy;
        EXPECT_CALL(*m_network_connector, connect("localhost", 80))
            .WillOnce(Throw(NetworkConnectorError{"DummyNetworkError"}));
        EXPECT_CALL(*m_error_handler, showErrorMessage(_, _, _)).Times(1);
    }
    EXPECT_CALL(*m_login_protocol, login(_, _, _)).Times(0);
    ClientLoginPage login_page;
    moveHandlersTo(login_page);
    QSignalSpy signal_spy(&login_page, &ClientLoginPage::signalLoginSuccess);
    QTest::keyClicks(&login_page.getHostNameInputField(), "localhost:80");
    QTest::mouseClick(&login_page.getLoginButton(), Qt::LeftButton);
    EXPECT_EQ(signal_spy.count(), 0);
}

TEST_F(ClientLoginPageTest, ThrowFromLoginProtocolShowsErrorMessage)
{
    {
        InSequence dummy;
        EXPECT_CALL(*m_network_connector, connect("localhost", 80))
            .WillOnce(Return(ByMove(makeReadyFuture(ConnectResult{}))));
        EXPECT_CALL(*m_login_protocol, login(Ref(*m_network_connector), "myUsername", "myPassword"))
            .WillOnce(Throw(LoginProtocolError{"DummyLoginProtocolError"}));
        EXPECT_CALL(*m_error_handler, showErrorMessage(_, _, _)).Times(1);
    }
    ClientLoginPage login_page;
    moveHandlersTo(login_page);
    QSignalSpy signal_spy(&login_page, &ClientLoginPage::signalLoginSuccess);
    QTest::keyClicks(&login_page.getHostNameInputField(), "localhost:80");
    QTest::keyClicks(&login_page.getUserNameInputField(), "myUsername");
    QTest::keyClicks(&login_page.getPasswordInputField(), "myPassword");
    QTest::mouseClick(&login_page.getLoginButton(), Qt::LeftButton);
    EXPECT_EQ(signal_spy.count(), 0);
}
