#include <common/dwiz_std.h>
#include <client/client_main_window.h>
#include <common/log/logging.h>
#include <QApplication>
#include <exception>

int main(int argc, char* argv[])
{
    using namespace dwiz;

    loginfo << "Application start." << endlog;
    int return_code = 1;
    try
    {
        QApplication app(argc, argv);
        ClientMainWindow window;
        QObject::connect(
            &window, &ClientMainWindow::closed,
            qApp, &QApplication::quit
        );
        window.show();
        return_code = app.exec();
    }
    catch (std::exception const& ex)
    {
        logerr << "Uncaught exception: \"" << ex.what() << "\"." << endlog;
    }
    catch (...)
    {
        logerr << "Uncaught unknown exception." << endlog;
    }

    loginfo << "Application end." << endlog;
    return return_code;
}
