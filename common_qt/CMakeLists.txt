add_library(DwizCommonQt STATIC
    catch_all_application.cpp
    catch_all_application.h
    network/qt_network_connector.cpp
    network/qt_network_connector.h
)
target_link_libraries(DwizCommonQt
    DwizCommon
    Qt5::Widgets
)
