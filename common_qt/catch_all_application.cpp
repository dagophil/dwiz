#include "catch_all_application.h"
#include <common/dwiz_assert.h>

namespace dwiz
{
bool CatchAllApplication::hasException() const
{
    return !m_exceptionMessage.empty();
}

std::string const& CatchAllApplication::getExceptionMessage() const
{
    return m_exceptionMessage;
}

bool CatchAllApplication::notify(QObject* f_obj, QEvent* f_event)
{
    try
    {
        return QApplication::notify(f_obj, f_event);
    }
    catch (std::exception const& ex)
    {
        m_exceptionMessage = std::string("Uncaught exception: ") + ex.what();
    }
    catch (AssertError const& ex)
    {
        m_exceptionMessage = "Assertion error: " + ex.what();
    }
    catch (...)
    {
        m_exceptionMessage = "Unknown exception.";
    }
    quit();
    return false;
}
} // namespace dwiz
