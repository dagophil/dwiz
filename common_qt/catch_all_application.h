#ifndef DWIZ_COMMON_CATCH_ALL_APPLICATION_H
#define DWIZ_COMMON_CATCH_ALL_APPLICATION_H

#include <common/dwiz_std.h>
#include <QApplication>

namespace dwiz
{
class CatchAllApplication : public QApplication
{
public:
    using QApplication::QApplication;
    bool hasException() const;
    std::string const& getExceptionMessage() const;

private:
    virtual bool notify(QObject* f_obj, QEvent* f_event) override;
    std::string m_exceptionMessage;

}; // CatchAllApplication
} // namespace dwiz

#endif
