qt5_wrap_ui(UI_HDRS
    client_main_window.ui
    client_login_page.ui
)
add_library(DwizClient STATIC
    client_game_page.cpp
    client_game_page.h
    client_login_page.cpp
    client_login_page.h
    client_main_window.cpp
    client_main_window.h
    ${UI_HDRS}
)
target_link_libraries(DwizClient
    DwizCommon
    DwizCommonQt
    ${LOG4CXX_LIBRARY}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    ${CMAKE_THREAD_LIBS_INIT}
)
dwiz_add_executable(dwizclient client_main.cpp)
target_link_libraries(dwizclient DwizClient)
copy_qt_lib(dwizclient Qt5::Core)
copy_qt_lib(dwizclient Qt5::Gui)
copy_qt_lib(dwizclient Qt5::Widgets)

copy_file(".log-config")

add_test_files(
    client_login_page_test.cpp
)
