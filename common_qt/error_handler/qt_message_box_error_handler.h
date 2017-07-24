#ifndef COMMON_QT_ERROR_HANDLER_QT_MESSAGE_BOX_ERROR_HANDLER_H
#define COMMON_QT_ERROR_HANDLER_QT_MESSAGE_BOX_ERROR_HANDLER_H

#include <common/dwiz_std.h>
#include <common_qt/error_handler/qt_error_handler_interface.h>

namespace dwiz
{
class QtMessageBoxErrorHandler : public QtErrorHandlerInterface
{
public:
    virtual void showErrorMessage(
        QWidget* const f_parent, std::string const& f_title, std::string const& f_message) override;
}; // class QtMessageBoxErrorHandler
} // namespace dwiz

#endif
