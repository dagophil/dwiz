#ifndef DWIZ_COMMON_SIGNALS_CONNECTION_H
#define DWIZ_COMMON_SIGNALS_CONNECTION_H

#include <common/dwiz_std.h>
#include <functional>
#include <memory>

namespace dwiz
{
template <typename... Args>
class Connection
{
public:
    using SlotType = std::function<void(Args...)>;

    Connection(std::shared_ptr<SlotType> const& f_slot = nullptr);

    std::shared_ptr<SlotType> const& get_slot() const;

    void set_slot(std::shared_ptr<SlotType> const& f_slot);

    void disconnect();

private:
    std::shared_ptr<SlotType> m_slot;

}; // class Connection

template <typename... Args>
inline Connection<Args...>::Connection(std::shared_ptr<SlotType> const& f_slot)
    : m_slot(f_slot)
{
}

template <typename... Args>
inline std::shared_ptr<typename Connection<Args...>::SlotType> const&
Connection<Args...>::get_slot() const
{
    return m_slot;
}

template <typename... Args>
inline void Connection<Args...>::set_slot(std::shared_ptr<SlotType> const& f_slot)
{
    m_slot = f_slot;
}

template <typename... Args>
inline void Connection<Args...>::disconnect()
{
    m_slot.reset();
}

} // namespace dwiz

#endif
