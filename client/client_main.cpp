#include <common/dwiz_std.h>
#include <client/client_main_window.h>
#include <QApplication>


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    dwiz::ClientMainWindow window;
    QObject::connect(
        &window, &dwiz::ClientMainWindow::closed,
        qApp, &QApplication::quit
    );
    window.show();
    int const return_value = app.exec();
    return return_value;
}
