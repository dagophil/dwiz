#ifndef DWIZ_COMMON_LOG_LOGGER_H
#define DWIZ_COMMON_LOG_LOGGER_H

#include <common/dwiz_std.h>
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>

#define DWIZ_DEFINE_LOGGER(name)                                                                   \
    namespace                                                                                      \
    {                                                                                              \
    log4cxx::LoggerPtr& logger()                                                                   \
    {                                                                                              \
        static log4cxx::LoggerPtr l = log4cxx::Logger::getLogger(name);                            \
        return l;                                                                                  \
    }                                                                                              \
    }

#define DWIZ_LOG_DEBUG(msg) LOG4CXX_DEBUG(logger(), msg);

#define DWIZ_LOG_INFO(msg) LOG4CXX_INFO(logger(), msg);

#define DWIZ_LOG_WARN(msg) LOG4CXX_WARN(logger(), msg);

#define DWIZ_LOG_ERROR(msg) LOG4CXX_ERROR(logger(), msg);

#define DWIZ_INIT_LOG(logfile) log4cxx::PropertyConfigurator::configure(logfile);

#endif
