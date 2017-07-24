#ifndef DWIZ_CLIENT_MAIN_WINDOW_H
#define DWIZ_CLIENT_MAIN_WINDOW_H

#include <common/dwiz_std.h>
#include <QMainWindow>
#include <memory>

namespace Ui
{
class ClientMainWindowUi;
}

namespace dwiz
{
class NetworkConnectorFactoryInterface;
class NetworkConnectorInterface;
class ProtocolFactoryInterface;
class QtErrorHandlerInterface;

class ClientMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    ClientMainWindow(
        QWidget* const f_parent = nullptr, Qt::WindowFlags const f_flags = Qt::WindowFlags());
    ~ClientMainWindow();

    void init(
        std::unique_ptr<QtErrorHandlerInterface> f_error_handler,
        std::unique_ptr<NetworkConnectorFactoryInterface> f_networkConnectorFactory,
        std::unique_ptr<ProtocolFactoryInterface> f_protocolFactory);

signals:
    void closed();

private:
    virtual void closeEvent(QCloseEvent* f_event) override;

    std::unique_ptr<Ui::ClientMainWindowUi> m_ui;
    std::shared_ptr<QtErrorHandlerInterface> m_error_handler;
    //    std::unique_ptr<NetworkConnectorFactoryInterface> m_networkConnectorFactory;
    std::shared_ptr<NetworkConnectorInterface> m_networkConnector;
    std::unique_ptr<ProtocolFactoryInterface> m_protocolFactory;

}; // class ClientMainWindow
} // namespace dwiz

#endif
