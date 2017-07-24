#include "qt_message_box_error_handler.h"
#include <QMessageBox>

namespace dwiz
{
void QtMessageBoxErrorHandler::showErrorMessage(
    QWidget* const f_parent, std::string const& f_title, std::string const& f_message)
{
    QMessageBox::warning(
        f_parent, QString::fromStdString(f_title), QString::fromStdString(f_message));
}
} // namespace dwiz
