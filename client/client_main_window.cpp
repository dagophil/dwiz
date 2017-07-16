#include "client_main_window.h"
#include "ui_client_main_window.h"
#include <QCloseEvent>
#include <QLabel>
#include <QStackedWidget>
#include <iostream>

namespace dwiz
{
    ClientMainWindow::ClientMainWindow(
            QWidget* const f_parent,
            Qt::WindowFlags const f_flags
    )   :
        QMainWindow(f_parent, f_flags),
        m_ui(new Ui::ClientMainWindowUi())/*,
        m_stackedWidget(new QStackedWidget())*/
    {
        m_ui->setupUi(this);
        setCentralWidget(m_ui->stackedWidget);
    }

    ClientMainWindow::~ClientMainWindow() = default;

    void ClientMainWindow::closeEvent(QCloseEvent* f_event)
    {
        f_event->accept();
        emit closed();
    }
}  // namespace dwiz
