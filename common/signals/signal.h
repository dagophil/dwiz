#ifndef DWIZ_COMMON_SIGNALS_SIGNAL_H
#define DWIZ_COMMON_SIGNALS_SIGNAL_H

#include <common/dwiz_std.h>
#include <common/signals/connection.h>
#include <functional>
#include <memory>
#include <set>

namespace dwiz
{
template <typename... Args>
class Signal
{
public:
    using ConnectionType = Connection<Args...>;
    using SlotType = typename ConnectionType::SlotType;

    void connect(SlotType const& f_slot, ConnectionType& f_connection);

    void emit(Args... args);

private:
    std::set<std::shared_ptr<SlotType>> m_slots;
}; // class Signal

template <typename... Args>
void Signal<Args...>::connect(SlotType const& f_slot, ConnectionType& f_connection)
{
    auto slot_ptr = std::make_shared<SlotType>(f_slot);
    m_slots.insert(slot_ptr);
    f_connection.set_slot(slot_ptr);
}

template <typename... Args>
void Signal<Args...>::emit(Args... args)
{
    for (auto slot_it = m_slots.begin(); slot_it != m_slots.end();)
    {
        if (slot_it->use_count() > 1)
        {
            (**slot_it)(args...);
            ++slot_it;
        }
        else
        {
            slot_it = m_slots.erase(slot_it);
        }
    }
}

} // namespace dwiz

#endif
