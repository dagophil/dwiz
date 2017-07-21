#include "client_login_page.h"
#include "ui_client_login_page.h"
#include <common/dwiz_assert.h>
#include <common/log/logging.h>
#include <common/protocols/login_protocol_interface.h>

namespace dwiz
{
ClientLoginPage::ClientLoginPage(QWidget* const f_parent, Qt::WindowFlags const f_flags)
    : QWidget(f_parent, f_flags)
    , m_ui(new Ui::ClientLoginPageUi())
{
    m_ui->setupUi(this);
    QObject::connect(m_ui->btnLogin, &QPushButton::clicked, this, &ClientLoginPage::login);
}

ClientLoginPage::~ClientLoginPage() = default;

void ClientLoginPage::setLoginProtocol(std::unique_ptr<LoginProtocolInterface> f_login_protocol)
{
    m_login_protocol = std::move(f_login_protocol);
}

void ClientLoginPage::login()
{
    DWIZASSERT(m_login_protocol != nullptr);
    auto const host_name = m_ui->inputHost->text().toStdString();
    auto const user_name = m_ui->inputUsername->text().toStdString();
    auto const password = m_ui->inputPassword->text().toStdString();
    LOGDEBUG("Try login at \"" << host_name << "\" as \"" << user_name << "\"." << endlog);
    m_login_protocol->login(host_name, user_name, password);
}
} // namespace dwiz
