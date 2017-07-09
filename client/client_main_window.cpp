#include "client_main_window.h"
#include "ui_client_main_window.h"
#include <QCloseEvent>

namespace dwiz
{
    ClientMainWindow::ClientMainWindow(
            QWidget* f_parent,
            Qt::WindowFlags f_flags
    )   :
        QMainWindow(f_parent, f_flags),
        m_ui(new Ui::ClientMainWindowUi())
    {
        m_ui->setupUi(this);
    }

    ClientMainWindow::~ClientMainWindow() = default;

    void ClientMainWindow::closeEvent(QCloseEvent* f_event)
    {
        f_event->accept();
        emit closed();
    }
}  // namespace dwiz
