#ifndef COMMON_QT_QT_FUTURE_UTILS_H
#define COMMON_QT_QT_FUTURE_UTILS_H

#include <common/dwiz_std.h>
#include <common/future_utils.h>
#include <QThread>
#include <future>

namespace dwiz
{
namespace detail
{
/// The InvokeWhenFinishedWorker is needed because a QThread always needs a QObject worker. Also it
/// can store the future object.
template <typename T>
class InvokeWhenFinishedWorker : public QObject
{
public:
    InvokeWhenFinishedWorker(std::future<T> f_future)
        : QObject()
        , m_future(std::move(f_future))
    {
    }
    std::future<T> m_future;
};
}

/// Asynchronously calls f_future.wait() and then invokes f_slot(f_future) in the thread of the
/// context object f_context.
template <typename T, typename SLOT>
void invokeWhenFinished(std::future<T> f_future, QObject* const f_context, SLOT f_slot)
{
    if (isReady(f_future))
    {
        f_slot(std::move(f_future));
    }
    else
    {
        auto* const t = new QThread(f_context);
        auto* const worker = new detail::InvokeWhenFinishedWorker<T>(std::move(f_future));
        worker->moveToThread(t);
        QObject::connect(t, &QThread::started, worker, [=]() {
            worker->m_future.wait();
            t->quit();
        });
        QObject::connect(t, &QThread::finished, f_context, [=]() {
            std::future<T> future = std::move(worker->m_future);
            delete worker;
            delete t;
            f_slot(std::move(future));
        });
        t->start();
    }
}

/// Asynchronously calls f_future.wait() and then invokes the member function f_slot on f_context in
/// the thread of the context object f_context.
template <typename T, typename CONTEXT>
void invokeWhenFinished(
    std::future<T> f_future, CONTEXT* const f_context, void (CONTEXT::*f_slot)(std::future<T>))
{
    auto functor = [=](std::future<T> f_future_param) {
        (f_context->*f_slot)(std::move(f_future_param));
    };
    invokeWhenFinished(std::move(f_future), f_context, functor);
}
} // namespace dwiz

#endif
