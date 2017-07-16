#include "client_main_window.h"
#include "ui_client_main_window.h"
#include <QCloseEvent>
#include <QLabel>
#include <QStackedWidget>
#include <iostream>

namespace dwiz
{
    ClientMainWindow::ClientMainWindow(
            QWidget* f_parent,
            Qt::WindowFlags f_flags
    )   :
        QMainWindow(f_parent, f_flags),
        m_ui(new Ui::ClientMainWindowUi())/*,
        m_stackedWidget(new QStackedWidget())*/
    {
        m_ui->setupUi(this);

        setCentralWidget(m_ui->stackedWidget);

        m_ui->stackedWidget->addWidget(new QLabel("test"));

//        auto* l = new QLabel("test", m_ui->stackedWidget);
//        auto* l2 = new QLabel("xx", m_ui->stackedWidget);
//        setCentralWidget(m_stackedWidget.get());

//        auto* l = new QLabel("test", m_stackedWidget.get());
//        m_stackedWidget =
//        m_stackedWidget->addWidget(l);
    }

    ClientMainWindow::~ClientMainWindow() = default;

    void ClientMainWindow::closeEvent(QCloseEvent* f_event)
    {
        f_event->accept();
        emit closed();
    }
}  // namespace dwiz
