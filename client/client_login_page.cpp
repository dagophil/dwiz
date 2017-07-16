#include "client_login_page.h"
#include "ui_client_login_page.h"
#include <common/log/logging.h>

namespace dwiz
{

    ClientLoginPage::ClientLoginPage(
            QWidget* const f_parent,
            Qt::WindowFlags const f_flags
    )   :
        QWidget(f_parent, f_flags),
        m_ui(new Ui::ClientLoginPageUi())
    {
        m_ui->setupUi(this);
        QObject::connect(
            m_ui->btnLogin, &QPushButton::clicked,
            this, &ClientLoginPage::tryLogin
        );
    }

    ClientLoginPage::~ClientLoginPage() = default;

    void ClientLoginPage::tryLogin()
    {
        auto const host_name = m_ui->inputHost->text().toStdString();
        auto const user_name = m_ui->inputUsername->text().toStdString();
        LOGDEBUG("Try login at \"" << host_name << "\" as \""
            << user_name << "\"." << endlog);
    }

}  // namespace dwiz
