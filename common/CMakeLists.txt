add_library(DwizCommon STATIC
    dwiz_assert.cpp
    dwiz_assert.h
    dwiz_std.h
    log/logging.cpp
    log/logging.h
    log/ostream_logger.cpp
    log/ostream_logger.h
    network/network_connector_interface.h
    protocols/json_login_protocol.cpp
    protocols/json_login_protocol.h
    protocols/login_protocol_interface.h
)
