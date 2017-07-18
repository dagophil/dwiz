add_library(DwizCommonQt STATIC
    catch_all_application.cpp
)
target_link_libraries(DwizCommonQt
    DwizCommon
    Qt5::Widgets
)
