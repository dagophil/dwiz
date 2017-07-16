qt5_wrap_ui(UI_HDRS
    client_main_window.ui
)
add_executable(dwizclient
    client_main.cpp
    client_main_window.cpp
    client_login_page.cpp
    client_game_page.cpp
    ${UI_HDRS}
)
set_target_properties(dwizclient
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${DWIZ_OUTPUT_DIRECTORY}/client"
)
target_link_libraries(dwizclient
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)
copy_qt_lib(dwizclient Qt5::Core)
copy_qt_lib(dwizclient Qt5::Gui)
copy_qt_lib(dwizclient Qt5::Widgets)
