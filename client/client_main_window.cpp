#include "client_main_window.h"
#include "ui_client_main_window.h"
#include <common/dwiz_assert.h>
#include <common/network/network_connector_factory_interface.h>
#include <common/protocols/login_protocol_interface.h>
#include <common/protocols/protocol_factory_interface.h>
#include <common_qt/error_handler/qt_error_handler_interface.h>
#include <QCloseEvent>

namespace dwiz
{
ClientMainWindow::ClientMainWindow(QWidget* const f_parent, Qt::WindowFlags const f_flags)
    : QMainWindow(f_parent, f_flags)
    , m_ui(new Ui::ClientMainWindowUi())
{
    m_ui->setupUi(this);
    setCentralWidget(m_ui->stackedWidget);
}

ClientMainWindow::~ClientMainWindow() = default;

void ClientMainWindow::init(
    std::unique_ptr<QtErrorHandlerInterface> f_error_handler,
    std::unique_ptr<NetworkConnectorFactoryInterface> f_networkConnectorFactory,
    std::unique_ptr<ProtocolFactoryInterface> f_protocolFactory)
{
    DWIZ_ASSERT(f_error_handler != nullptr);
    DWIZ_ASSERT(f_networkConnectorFactory != nullptr);
    DWIZ_ASSERT(f_protocolFactory != nullptr);
    m_error_handler = std::move(f_error_handler);
    //    m_networkConnectorFactory = std::move(f_networkConnectorFactory);
    m_networkConnector = f_networkConnectorFactory->createNetworkConnector();
    m_protocolFactory = std::move(f_protocolFactory);
    m_ui->loginPage->setErrorHandler(m_error_handler);
    m_ui->loginPage->setNetworkConnector(m_networkConnector);
    m_ui->loginPage->setLoginProtocol(m_protocolFactory->createLoginProtocol());
}

void ClientMainWindow::closeEvent(QCloseEvent* f_event)
{
    f_event->accept();
    emit closed();
}
} // namespace dwiz
