add_executable(dwizserver server_main.cpp)
set_target_properties(dwizserver
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${DWIZ_OUTPUT_DIRECTORY}/server"
)
