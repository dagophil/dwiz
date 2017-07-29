#ifndef DWIZ_QT_COMMON_ERROR_HANDLER_QT_ERROR_HANDLER_INTERFACE_MOCK_H
#define DWIZ_QT_COMMON_ERROR_HANDLER_QT_ERROR_HANDLER_INTERFACE_MOCK_H

#include <common/dwiz_std.h>
#include <common_qt/error_handler/qt_error_handler_interface.h>
#include <gmock/gmock.h>

namespace dwiz
{
class QtErrorHandlerInterfaceMock : public QtErrorHandlerInterface
{
public:
    MOCK_METHOD3(showErrorMessage, void(QWidget* const, std::string const&, std::string const&));
}; // class QtErrorHandlerInterfaceMock
} // namespace dwiz

#endif
