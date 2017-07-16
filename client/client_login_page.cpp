#include "client_login_page.h"
#include "ui_client_login_page.h"

namespace dwiz
{

    ClientLoginPage::ClientLoginPage(
            QWidget * const f_parent,
            Qt::WindowFlags const f_flags
    )   :
        QWidget(f_parent, f_flags),
        m_ui(new Ui::ClientLoginPageUi())
    {
        m_ui->setupUi(this);
    }

    ClientLoginPage::~ClientLoginPage() = default;

}  // namespace dwiz
