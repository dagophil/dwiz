#include <common/dwiz_std.h>
#include <client/client_main_window.h>
#include <common/dwiz_assert.h>
#include <common/log/logging.h>
#include <common_qt/catch_all_application.h>
#include <exception>

int main(int argc, char* argv[])
{
    using namespace dwiz;

    loginfo << "Application start." << endlog;
    int return_code = 1;
    try
    {
        CatchAllApplication app(argc, argv);
        ClientMainWindow window;
        QObject::connect(&window, &ClientMainWindow::closed, &app, &QApplication::quit);
        window.show();
        int const app_result = app.exec();
        if (!app.hasException())
        {
            return_code = app_result;
        }
        else
        {
            logerr << app.getExceptionMessage() << endlog;
        }
    }
    catch (std::exception const& ex)
    {
        logerr << "Uncaught exception: " << ex.what() << "." << endlog;
    }
    catch (AssertError const& ex)
    {
        logerr << "Assertion error: " << ex.what() << "." << endlog;
    }
    catch (...)
    {
        logerr << "Unknown exception." << endlog;
    }
    loginfo << "Application end, status code " << return_code << "." << endlog;
    return return_code;
}
