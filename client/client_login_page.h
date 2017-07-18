#ifndef DWIZ_CLIENT_LOGIN_PAGE_H
#define DWIZ_CLIENT_LOGIN_PAGE_H

#include <common/dwiz_std.h>
#include <QWidget>
#include <memory>

namespace Ui { class ClientLoginPageUi; }

namespace dwiz
{
    class LoginProtocolInterface;

    class ClientLoginPage : public QWidget
    {
    public:

        ClientLoginPage(
                QWidget* const f_parent = nullptr,
                Qt::WindowFlags const f_flags = Qt::WindowFlags()
        );
        ~ClientLoginPage();

        void setLoginProtocol(
                std::unique_ptr<LoginProtocolInterface>&& f_login_protocol
        );

        void login();

    private:

        std::unique_ptr<Ui::ClientLoginPageUi> m_ui;
        std::unique_ptr<LoginProtocolInterface> m_login_protocol;

    };  // class ClientLoginPage
}  // namespace dwiz

#endif
