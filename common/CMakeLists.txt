add_library(DwizCommon STATIC
    dwiz_assert.cpp
    dwiz_assert.h
    dwiz_std.h
    future_utils.h
    log/logging.cpp
    log/logging.h
    log/ostream_logger.cpp
    log/ostream_logger.h
    network/network_connector_factory_interface.h
    network/network_connector_interface.h
    protocols/login_protocol_interface.h
    protocols/protocol_factory_interface.h
    protocols/v0/json_login_protocol_v0.cpp
    protocols/v0/json_login_protocol_v0.h
    protocols/v0/protocol_v0_factory.cpp
    protocols/v0/protocol_v0_factory.h
    string_utils.cpp
    string_utils.h
)

add_test_files(
    future_utils_test.cpp
    network/network_connector_interface_mock.h
    protocols/login_protocol_interface_mock.h
    string_utils_test.cpp
)
