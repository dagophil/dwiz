#ifndef DWIZ_CLIENT_LOGIN_PAGE_H
#define DWIZ_CLIENT_LOGIN_PAGE_H

#include <common/dwiz_std.h>
#include <QWidget>
#include <memory>

namespace Ui { class ClientLoginPageUi; }

namespace dwiz
{
    class ClientLoginPage : public QWidget
    {
    public:

        ClientLoginPage(
                QWidget* const f_parent = nullptr,
                Qt::WindowFlags const f_flags = Qt::WindowFlags()
        );
        ~ClientLoginPage();

    private:

        std::unique_ptr<Ui::ClientLoginPageUi> m_ui;

    };  // class ClientLoginPage
}  // namespace dwiz

#endif
