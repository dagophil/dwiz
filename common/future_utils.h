#ifndef DWIZ_COMMON_FUTURE_UTILS_H
#define DWIZ_COMMON_FUTURE_UTILS_H

#include <common/dwiz_std.h>
#include <chrono>
#include <future>

namespace dwiz
{
/// Returns a ready future whose value is set to f_value.
template <typename T>
std::future<T> makeReadyFuture(T const& f_value)
{
    std::promise<T> promise;
    promise.set_value(f_value);
    return promise.get_future();
}

/// Returns a ready future whose value is set to f_value.
template <typename T>
std::future<T> makeReadyFuture(T&& f_value)
{
    std::promise<T> promise;
    promise.set_value(std::forward<T>(f_value));
    return promise.get_future();
}

/// Returns a ready future whose value is set to f_value.
/// This overload makes sure that C-arrays (and C-strings) are accepted.
template <typename T>
std::future<T*> makeReadyFuture(T* const f_value)
{
    std::promise<T*> promise;
    promise.set_value(f_value);
    return promise.get_future();
}

/// Returns true if the given future is valid and ready, so that get will not block.
template <typename T>
bool isReady(std::future<T> const& f_future)
{
    return f_future.valid()
           && f_future.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
}
} // namespace dwiz

#endif
