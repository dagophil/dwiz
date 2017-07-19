#include "ostream_logger.h"
#include <common/log/logging.h>

namespace dwiz
{
OStreamLogger::OStreamLogger(std::ostream& f_stream)
    : m_stream(f_stream)
{
}

int OStreamLogger::sync()
{
    m_stream << str();
    m_stream.flush();
    str("");
    return std::stringbuf::sync();
}
} // namespace dwiz
