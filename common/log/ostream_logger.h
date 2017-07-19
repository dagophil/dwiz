#ifndef DWIZ_COMMON_LOG_OSTREAM_LOGGER_H
#define DWIZ_COMMON_LOG_OSTREAM_LOGGER_H

#include <common/dwiz_std.h>
#include <sstream>

namespace dwiz
{
class OStreamLogger : public std::stringbuf
{
public:
    OStreamLogger(std::ostream& f_stream);

private:
    virtual int sync() override;

    std::ostream& m_stream;

}; // OStreamLogger
} // namespace dwiz

#endif
