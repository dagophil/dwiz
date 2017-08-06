#include "client_login_page.h"
#include "ui_client_login_page.h"
#include <common/dwiz_assert.h>
#include <common/future_utils.h>
#include <common/log/logger.h>
#include <common/network/network_connector_interface.h>
#include <common/protocols/login_protocol_interface.h>
#include <common/string_utils.h>
#include <common_qt/error_handler/qt_error_handler_interface.h>
#include <common_qt/qt_future_utils.h>

DWIZ_DEFINE_LOGGER("client.client_login_page");

namespace dwiz
{
ClientLoginPage::ClientLoginPage(QWidget* const f_parent, Qt::WindowFlags const f_flags)
    : QWidget(f_parent, f_flags)
    , m_ui(new Ui::ClientLoginPageUi())
    , m_error_handler()
    , m_network_connector()
    , m_login_protocol()
{
    m_ui->setupUi(this);
    QObject::connect(
        m_ui->btnLogin, &QPushButton::clicked, this, &ClientLoginPage::onLoginButtonClicked);
}

ClientLoginPage::~ClientLoginPage() = default;

void ClientLoginPage::setErrorHandler(
    std::shared_ptr<QtErrorHandlerInterface> const& f_error_handler)
{
    m_error_handler = f_error_handler;
}

void ClientLoginPage::setNetworkConnector(
    std::shared_ptr<NetworkConnectorInterface> const& f_network_connector)
{
    m_network_connector = f_network_connector;
}

void ClientLoginPage::setLoginProtocol(std::unique_ptr<LoginProtocolInterface> f_login_protocol)
{
    m_login_protocol = std::move(f_login_protocol);
}

QLineEdit& ClientLoginPage::getHostNameInputField()
{
    return *m_ui->inputHost;
}

QLineEdit const& ClientLoginPage::getHostNameInputField() const
{
    return *m_ui->inputHost;
}

QLineEdit& ClientLoginPage::getUserNameInputField()
{
    return *m_ui->inputUsername;
}

QLineEdit const& ClientLoginPage::getUserNameInputField() const
{
    return *m_ui->inputUsername;
}

QLineEdit& ClientLoginPage::getPasswordInputField()
{
    return *m_ui->inputPassword;
}

QLineEdit const& ClientLoginPage::getPasswordInputField() const
{
    return *m_ui->inputPassword;
}

QPushButton& ClientLoginPage::getLoginButton()
{
    return *m_ui->btnLogin;
}

QPushButton const& ClientLoginPage::getLoginButton() const
{
    return *m_ui->btnLogin;
}

void ClientLoginPage::onLoginButtonClicked()
{
    DWIZ_ASSERT(m_network_connector != nullptr);
    DWIZ_ASSERT(m_login_protocol != nullptr);
    auto const hostAndPort = m_ui->inputHost->text().toStdString();
    std::string host;
    unsigned int port = 0;
    try
    {
        std::tie(host, port) = splitHostAndPort(hostAndPort);
    }
    catch (std::runtime_error const& ex)
    {
        DWIZ_LOG_DEBUG("Failed to split host and port: " << ex.what());
        if (m_error_handler)
        {
            m_error_handler->showErrorMessage(
                this,
                "Input error",
                "Hostname must have the format \"domain:port\", e.g. \"127.0.0.1:80\".");
        }
        return;
    }

    std::future<ConnectResult> connectResult;
    try
    {
        connectResult = m_network_connector->connect(host, port);
    }
    catch (NetworkConnectorError const& ex)
    {
        DWIZ_LOG_DEBUG("Network connector could not connect: " << ex.what());
        if (m_error_handler)
        {
            m_error_handler->showErrorMessage(
                this, "Connection error", "Could not connect to \"" + host + "\".");
        }
        return;
    }
    DWIZ_ASSERT(connectResult.valid());
    invokeWhenFinished(std::move(connectResult), this, &ClientLoginPage::onConnectResult);
}

void ClientLoginPage::onConnectResult(std::future<ConnectResult> f_future)
{
    DWIZ_ASSERT(isReady(f_future));
    auto const connect_result = f_future.get();
    DWIZ_LOG_WARN(
        "ClientLoginPage::onConnectResult(): TODO: Do something with the connect result.");
    auto const user_name = m_ui->inputUsername->text().toStdString();
    auto const password = m_ui->inputPassword->text().toStdString();
    std::future<LoginResult> loginResult;
    try
    {
        loginResult = m_login_protocol->login(*m_network_connector, user_name, password);
    }
    catch (LoginProtocolError const& ex)
    {
        DWIZ_LOG_DEBUG("Login protocol could not login: " << ex.what());
        if (m_error_handler)
        {
            m_error_handler->showErrorMessage(this, "Login error", "Could not login.");
        }
        return;
    }
    DWIZ_ASSERT(loginResult.valid());
    invokeWhenFinished(std::move(loginResult), this, &ClientLoginPage::onLoginResult);
}

void ClientLoginPage::onLoginResult(std::future<LoginResult> f_future)
{
    DWIZ_ASSERT(isReady(f_future));
    auto const login_result = f_future.get();
    DWIZ_LOG_WARN("ClientLoginPage::onLoginResult(): TODO: Do something with the login result.");
    emit signalLoginSuccess(login_result);
}
} // namespace dwiz
