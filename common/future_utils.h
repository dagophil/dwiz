#ifndef DWIZ_COMMON_FUTURE_UTILS_H
#define DWIZ_COMMON_FUTURE_UTILS_H

#include <common/dwiz_std.h>
#include <future>

namespace dwiz
{
template <typename T>
std::future<T> make_ready_future(T const& f_value)
{
    std::promise<T> promise;
    promise.set_value(f_value);
    return promise.get_future();
}
} // namespace dwiz

#endif
