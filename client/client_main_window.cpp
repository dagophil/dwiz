#include "client_main_window.h"
#include "ui_client_main_window.h"
#include <common/protocols/json_login_protocol.h>
#include <common_qt/network/qt_network_connector.h>
#include <QCloseEvent>

namespace dwiz
{
    ClientMainWindow::ClientMainWindow(
            QWidget* const f_parent,
            Qt::WindowFlags const f_flags
    )   :
        QMainWindow(f_parent, f_flags),
        m_ui(new Ui::ClientMainWindowUi())
    {
        m_ui->setupUi(this);
        setCentralWidget(m_ui->stackedWidget);

        auto network_connector = std::make_shared<QtNetworkConnector>();
        auto login_protocol = std::make_unique<JsonLoginProtocol>(network_connector);
        m_ui->loginPage->setLoginProtocol(std::move(login_protocol));
    }

    ClientMainWindow::~ClientMainWindow() = default;

    void ClientMainWindow::closeEvent(QCloseEvent* f_event)
    {
        f_event->accept();
        emit closed();
    }
}  // namespace dwiz
