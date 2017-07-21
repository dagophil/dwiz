add_library(DwizCommonQt STATIC
    catch_all_application.cpp
    catch_all_application.h
    network/qt_network_connector.cpp
    network/qt_network_connector.h
    network/qt_network_connector_factory.cpp
    network/qt_network_connector_factory.h
)
target_link_libraries(DwizCommonQt
    DwizCommon
    Qt5::Widgets
)
