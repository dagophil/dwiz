#include "logging.h"
#include <common/log/ostream_logger.h>
#include <iostream>
#include <map>

namespace dwiz
{

    std::ostream& operator<<(
            std::ostream& f_stream,
            EndLog const&
    ){
        f_stream << "\n";
        f_stream.flush();
        return f_stream;
    }

    namespace
    {
        OStreamLogger& getLogger(std::ostream& f_stream)
        {
            static std::map<std::ostream*, OStreamLogger> loggers;
            auto const it_logger = loggers.find(&f_stream);
            if (it_logger != loggers.end())
            {
                return it_logger->second;
            }
            auto const insert_result =
                loggers.insert(std::make_pair(
                    &f_stream,
                    OStreamLogger{f_stream}
                )
            );
            return insert_result.first->second;
        }
    }  // namespace

    std::ostream logerr(&getLogger(std::cerr));
    std::ostream logwarn(&getLogger(std::cerr));
    std::ostream loginfo(&getLogger(std::cout));
    namespace detail
    {
        std::ostream logdebug(&getLogger(std::cout));
    }  // namespace detail

    EndLog endlog;

}  // namespace dwiz
