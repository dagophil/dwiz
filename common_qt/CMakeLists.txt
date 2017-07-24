add_library(DwizCommonQt STATIC
    catch_all_application.cpp
    catch_all_application.h
    error_handler/qt_error_handler_interface.h
    error_handler/qt_message_box_error_handler.cpp
    error_handler/qt_message_box_error_handler.h
    network/qt_network_connector.cpp
    network/qt_network_connector.h
    network/qt_network_connector_factory.cpp
    network/qt_network_connector_factory.h
    qt_future_utils.h
)
target_link_libraries(DwizCommonQt
    DwizCommon
    Qt5::Widgets
)
