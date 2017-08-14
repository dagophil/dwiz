#include <common/signals/signal.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::Ref;
using testing::SetArgReferee;

using std::placeholders::_1;
using std::placeholders::_2;

using VoidSignal = dwiz::Signal<>;
using VoidConnection = VoidSignal::ConnectionType;

class VoidSlotMock
{
public:
    MOCK_METHOD0(func, void());
}; // class VoidSlotMock

TEST(signalTest, EmitCallsSlot)
{
    VoidSlotMock slot;
    EXPECT_CALL(slot, func()).Times(1);
    VoidSignal signal;
    VoidConnection connection;
    signal.connect(std::bind(&VoidSlotMock::func, &slot), connection);
    signal.emit();
}

TEST(signalTest, EmitThreeTimesCallsSlotThreeTimes)
{
    VoidSlotMock slot;
    EXPECT_CALL(slot, func()).Times(3);
    VoidSignal signal;
    VoidConnection connection;
    signal.connect(std::bind(&VoidSlotMock::func, &slot), connection);
    signal.emit();
    signal.emit();
    signal.emit();
}

TEST(signalTest, EmitAfterDisconnectDoesNotCallSlot)
{
    VoidSlotMock slot;
    EXPECT_CALL(slot, func()).Times(0);
    VoidSignal signal;
    VoidConnection connection;
    signal.connect(std::bind(&VoidSlotMock::func, &slot), connection);
    connection.disconnect();
    signal.emit();
}

TEST(signalTest, EmitAfterDeletingConnectionDoesNotCallSlot)
{
    VoidSlotMock slot;
    EXPECT_CALL(slot, func()).Times(0);
    VoidSignal signal;
    auto connection = std::make_unique<VoidConnection>();
    signal.connect(std::bind(&VoidSlotMock::func, &slot), *connection);
    connection.reset();
    signal.emit();
}

TEST(signalTest, EmitCallsTwoConnectedSlots)
{
    VoidSlotMock slot0;
    VoidSlotMock slot1;
    EXPECT_CALL(slot0, func()).Times(1);
    EXPECT_CALL(slot1, func()).Times(1);
    VoidSignal signal;
    VoidConnection connection0;
    signal.connect(std::bind(&VoidSlotMock::func, &slot0), connection0);
    VoidConnection connection1;
    signal.connect(std::bind(&VoidSlotMock::func, &slot1), connection1);
    signal.emit();
}

TEST(signalTest, EmitAfterConnectTwoAndDisconnectOneCallsRemainingSlot)
{
    VoidSlotMock slot0;
    VoidSlotMock slot1;
    EXPECT_CALL(slot0, func()).Times(1);
    EXPECT_CALL(slot1, func()).Times(2);
    VoidSignal signal;
    VoidConnection connection0;
    signal.connect(std::bind(&VoidSlotMock::func, &slot0), connection0);
    VoidConnection connection1;
    signal.connect(std::bind(&VoidSlotMock::func, &slot1), connection1);
    signal.emit();
    connection0.disconnect();
    signal.emit();
}

TEST(signalTest, ConnectSameSlotMultipleTimesCallsSlotMultipleTimes)
{
    VoidSlotMock slot;
    EXPECT_CALL(slot, func()).Times(2);
    VoidSignal signal;
    VoidConnection connection0;
    signal.connect(std::bind(&VoidSlotMock::func, &slot), connection0);
    VoidConnection connection1;
    signal.connect(std::bind(&VoidSlotMock::func, &slot), connection1);
    signal.emit();
}

using IntDoubleSignal = dwiz::Signal<int, double>;
using IntDoubleConnection = IntDoubleSignal::ConnectionType;

class IntDoubleSlotMock
{
public:
    MOCK_METHOD2(func, void(int, double));
}; // class IntDoubleSlotMock

TEST(signalTest, PassingArgumentsToSlotViaLambda)
{
    IntDoubleSlotMock slot;
    EXPECT_CALL(slot, func(5, 1.14)).Times(1);
    IntDoubleSignal signal;
    IntDoubleConnection connection;
    signal.connect([&](int const a, double const b) { slot.func(a, b); }, connection);
    signal.emit(5, 1.14);
}

using StringReferenceSignal = dwiz::Signal<std::string&>;
using StringReferenceConnection = StringReferenceSignal::ConnectionType;

class StringReferenceSlotMock
{
public:
    MOCK_METHOD1(func, void(std::string&));
}; // class StringReferenceSlotMock

TEST(signalTest, PassingReferenceToSlot)
{
    std::string str;
    StringReferenceSlotMock slot;
    StringReferenceSignal signal;
    StringReferenceConnection connection;
    signal.connect(std::bind(&StringReferenceSlotMock::func, &slot, _1), connection);
    EXPECT_CALL(slot, func(Ref(str))).Times(1).WillOnce(SetArgReferee<0>("foo"));
    signal.emit(str);
    ASSERT_EQ(str, "foo");
    EXPECT_CALL(slot, func(Ref(str))).Times(1).WillOnce(SetArgReferee<0>("bar"));
    signal.emit(str);
    ASSERT_EQ(str, "bar");
}
