#ifndef DWIZ_CLIENT_LOGIN_PAGE_H
#define DWIZ_CLIENT_LOGIN_PAGE_H

#include <common/dwiz_std.h>
#include <QWidget>
#include <future>
#include <memory>

class QLineEdit;
class QPushButton;
namespace Ui
{
class ClientLoginPageUi;
}

namespace dwiz
{
class ConnectResult;
class LoginProtocolInterface;
class LoginResult;
class NetworkConnectorInterface;
class QtErrorHandlerInterface;

class ClientLoginPage : public QWidget
{
    Q_OBJECT
public:
    ClientLoginPage(
        QWidget* const f_parent = nullptr, Qt::WindowFlags const f_flags = Qt::WindowFlags());

    ~ClientLoginPage();

    void setErrorHandler(std::shared_ptr<QtErrorHandlerInterface> const& f_error_handler);
    void setNetworkConnector(std::shared_ptr<NetworkConnectorInterface> const& f_network_connector);
    void setLoginProtocol(std::unique_ptr<LoginProtocolInterface> f_login_protocol);

    QLineEdit& getHostNameInputField();
    QLineEdit const& getHostNameInputField() const;

    QLineEdit& getUserNameInputField();
    QLineEdit const& getUserNameInputField() const;

    QLineEdit& getPasswordInputField();
    QLineEdit const& getPasswordInputField() const;

    QPushButton& getLoginButton();
    QPushButton const& getLoginButton() const;

signals:
    void signalLoginSuccess(LoginResult const&);

private:
    void onLoginButtonClicked();
    void onConnectResult(std::future<ConnectResult> f_future);
    void onLoginResult(std::future<LoginResult> f_future);

    std::unique_ptr<Ui::ClientLoginPageUi> m_ui;

    std::shared_ptr<QtErrorHandlerInterface> m_error_handler;
    std::shared_ptr<NetworkConnectorInterface> m_network_connector;
    std::unique_ptr<LoginProtocolInterface> m_login_protocol;

}; // class ClientLoginPage
} // namespace dwiz

#endif
