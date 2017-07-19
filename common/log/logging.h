#ifndef DWIZ_COMMON_LOGGING_H
#define DWIZ_COMMON_LOGGING_H

#include <common/dwiz_std.h>
#include <ostream>

namespace dwiz
{
extern std::ostream logerr;
extern std::ostream logwarn;
extern std::ostream loginfo;

// Hide logdebug in namespace to encourage use of LOGDEBUG macro.
namespace detail
{
extern std::ostream logdebug;
} // namespace detail

extern struct EndLog
{
} endlog;

std::ostream& operator<<(std::ostream& f_stream, EndLog const& f_endlog);

#ifdef DWIZ_DEBUG
#define LOGDEBUG(msg) detail::logdebug << msg
#else
#define LOGDEBUG(msg)
#endif

} // namespace dwiz

#endif
