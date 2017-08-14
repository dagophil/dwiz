#include <common/signals/connection.h>
#include <gtest/gtest.h>
#include <functional>
#include <memory>

using Connection = dwiz::Connection<int&>;
using Slot = Connection::SlotType;

TEST(connectionTest, ConstructorAndGetterWork)
{
    auto slot = std::make_shared<Slot>();
    Connection conn(slot);
    ASSERT_EQ(slot, conn.get_slot());
}

TEST(connectionTest, DefaultConstructorHasEmptySlot)
{
    Connection conn;
    ASSERT_FALSE(conn.get_slot());
}

TEST(connectionTest, SetterWorks)
{
    Connection conn;
    auto slot = std::make_shared<Slot>();
    conn.set_slot(slot);
    ASSERT_EQ(slot, conn.get_slot());
}

TEST(connectionTest, DisconnectMakesEmptySlot)
{
    auto slot = std::make_shared<Slot>();
    Connection conn(slot);
    ASSERT_EQ(slot, conn.get_slot());
    conn.disconnect();
    ASSERT_NE(slot, conn.get_slot());
    ASSERT_FALSE(conn.get_slot());
}
