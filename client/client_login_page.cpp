#include "client_login_page.h"
#include "ui_client_login_page.h"
#include <common/dwiz_assert.h>
#include <common/future_utils.h>
#include <common/log/logging.h>
#include <common/network/network_connector_interface.h>
#include <common/protocols/login_protocol_interface.h>
#include <common/string_utils.h>
#include <common_qt/error_handler/qt_error_handler_interface.h>
#include <common_qt/qt_future_utils.h>

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
        m_ui->btnLogin, &QPushButton::clicked, this, &ClientLoginPage::connectAndLogin);
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

void ClientLoginPage::setHostName(const std::string& f_host_name)
{
    m_ui->inputHost->setText(QString::fromStdString(f_host_name));
}

void ClientLoginPage::setUserName(const std::string& f_user_name)
{
    m_ui->inputUsername->setText(QString::fromStdString(f_user_name));
}

void ClientLoginPage::setPassword(const std::string& f_password)
{
    m_ui->inputPassword->setText(QString::fromStdString(f_password));
}

void ClientLoginPage::connectAndLogin()
{
    DWIZASSERT(m_network_connector != nullptr);
    DWIZASSERT(m_login_protocol != nullptr);
    auto const hostAndPort = m_ui->inputHost->text().toStdString();
    std::string host;
    unsigned int port = 0;
    try
    {
        std::tie(host, port) = splitHostAndPort(hostAndPort);
    }
    catch (std::runtime_error const& ex)
    {
        LOGDEBUG("Failed to split host and port: " << ex.what() << endlog);
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
    catch (std::runtime_error const& ex)
    {
        LOGDEBUG("Network connector could not connect: " << ex.what() << endlog);
        if (m_error_handler)
        {
            m_error_handler->showErrorMessage(
                this, "Connection error", "Could not connect to \"" + host + "\".");
        }
        return;
    }
    if (!connectResult.valid())
    {
        logwarn << "Network connector returned invalid future." << endlog;
        if (m_error_handler)
        {
            m_error_handler->showErrorMessage(
                this, "Connection error", "Could not connect to \"" + host + "\".");
        }
        return;
    }
    invokeWhenFinished(std::move(connectResult), this, &ClientLoginPage::onConnectResult);
}

void ClientLoginPage::onConnectResult(std::future<ConnectResult> f_future)
{
    DWIZASSERT(isReady(f_future));
    auto const connect_result = f_future.get();
    logwarn << "ClientLoginPage::onConnectResult(): TODO: Do something with the connect result."
            << endlog;
    auto const user_name = m_ui->inputUsername->text().toStdString();
    auto const password = m_ui->inputPassword->text().toStdString();
    std::future<LoginResult> loginResult;
    try
    {
        loginResult = m_login_protocol->login(*m_network_connector, user_name, password);
    }
    catch (std::runtime_error const& ex)
    {
        LOGDEBUG("Login protocol could not login: " << ex.what() << endlog);
        if (m_error_handler)
        {
            m_error_handler->showErrorMessage(this, "Login error", "Could not login.");
        }
        return;
    }
    if (!loginResult.valid())
    {
        logwarn << "Login protocol returned invalid future." << endlog;
        if (m_error_handler)
        {
            m_error_handler->showErrorMessage(this, "Login error", "Could not login.");
        }
        return;
    }
    invokeWhenFinished(std::move(loginResult), this, &ClientLoginPage::onLoginResult);
}

void ClientLoginPage::onLoginResult(std::future<LoginResult> f_future)
{
    DWIZASSERT(isReady(f_future));
    auto const login_result = f_future.get();
    logwarn << "ClientLoginPage::onLoginResult(): TODO: Do something with the login result."
            << endlog;
}
} // namespace dwiz
