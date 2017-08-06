#include <common/dwiz_std.h>
#include <client/client_main_window.h>
#include <common/dwiz_assert.h>
#include <common/log/logger.h>
#include <common/protocols/v0/protocol_v0_factory.h>
#include <common_qt/catch_all_application.h>
#include <common_qt/error_handler/qt_message_box_error_handler.h>
#include <common_qt/network/qt_network_connector_factory.h>
#include <exception>
#include <memory>

DWIZ_DEFINE_LOGGER("client.main");

int main(int argc, char* argv[])
{
    using namespace dwiz;

    DWIZ_INIT_LOG(".log-config");
    DWIZ_LOG_INFO("Application start.");

    int return_code = 1;
    try
    {
        CatchAllApplication app(argc, argv);
        ClientMainWindow window;
        QObject::connect(&window, &ClientMainWindow::closed, &app, &QApplication::quit);
        window.init(
            std::make_unique<QtMessageBoxErrorHandler>(),
            std::make_unique<QtNetworkConnectorFactory>(),
            std::make_unique<ProtocolV0Factory>());
        window.show();
        int const app_result = app.exec();
        if (!app.hasException())
        {
            return_code = app_result;
        }
        else
        {
            DWIZ_LOG_ERROR(app.getExceptionMessage());
        }
    }
    catch (std::exception const& ex)
    {
        DWIZ_LOG_ERROR("Uncaught exception: " << ex.what() << ".");
    }
    catch (AssertError const& ex)
    {
        DWIZ_LOG_ERROR("Assertion error: " << ex.what() << ".");
    }
    catch (...)
    {
        DWIZ_LOG_ERROR("Unknown exception.");
    }

    DWIZ_LOG_INFO("Application end, status code " << return_code << ".");
    return return_code;
}
