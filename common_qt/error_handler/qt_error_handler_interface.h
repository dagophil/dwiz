#ifndef COMMON_QT_ERROR_HANDLER_QT_ERROR_HANDLER_INTERFACE_H
#define COMMON_QT_ERROR_HANDLER_QT_ERROR_HANDLER_INTERFACE_H

#include <common/dwiz_std.h>
#include <string>

class QWidget;

namespace dwiz
{
class QtErrorHandlerInterface
{
public:
    virtual ~QtErrorHandlerInterface() = default;
    virtual void showErrorMessage(
        QWidget* const f_parent, std::string const& f_title, std::string const& f_message) = 0;
};
} // namespace dwiz

#endif
