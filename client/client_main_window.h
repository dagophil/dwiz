#ifndef DWIZ_MAIN_WINDOW_H
#define DWIZ_MAIN_WINDOW_H

#include <common/dwiz_std.h>
#include <QMainWindow>
#include <memory>

namespace Ui { class ClientMainWindowUi; }

namespace dwiz
{
    class ClientMainWindow : public QMainWindow
    {
        Q_OBJECT
    public:
        ClientMainWindow(QWidget* f_parent = nullptr, Qt::WindowFlags f_flags = Qt::WindowFlags());
        ~ClientMainWindow();
    signals:
        void closed();
    private:
        virtual void closeEvent(QCloseEvent* f_event) override;
        std::unique_ptr<Ui::ClientMainWindowUi> m_ui;
    };
}  // namespace dwiz

#endif
