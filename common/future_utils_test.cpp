#include <common/future_utils.h>
#include <exception>
#include <gtest/gtest.h>
#include <string>

using namespace dwiz;

// isReady() tests:

TEST(isReadyTest, InvalidIntFutureIsNotReady)
{
    std::future<int> future;
    ASSERT_FALSE(future.valid());
    EXPECT_FALSE(isReady(future));
}

TEST(isReadyTest, InvalidStringFutureIsNotReady)
{
    std::future<std::string> future;
    ASSERT_FALSE(future.valid());
    EXPECT_FALSE(isReady(future));
}

TEST(isReadyTest, ValidNonReadyIntFutureIsNotReady)
{
    std::promise<int> promise;
    std::future<int> future = promise.get_future();
    ASSERT_TRUE(future.valid());
    EXPECT_FALSE(isReady(future));
}

TEST(isReadyTest, ValidNonReadyStringFutureIsNotReady)
{
    std::promise<std::string> promise;
    std::future<std::string> future = promise.get_future();
    ASSERT_TRUE(future.valid());
    EXPECT_FALSE(isReady(future));
}

TEST(isReadyTest, ValidReadyIntFutureIsReady)
{
    std::promise<int> promise;
    std::future<int> future = promise.get_future();
    EXPECT_FALSE(isReady(future));
    promise.set_value(0);
    EXPECT_TRUE(isReady(future));
}

TEST(isReadyTest, ValidReadyStringFutureIsReady)
{
    std::promise<std::string> promise;
    std::future<std::string> future = promise.get_future();
    EXPECT_FALSE(isReady(future));
    promise.set_value("foo");
    EXPECT_TRUE(isReady(future));
}

TEST(isReadyTest, ValidIntFutureWithExceptionIsReady)
{
    std::promise<int> promise;
    std::future<int> future = promise.get_future();
    EXPECT_FALSE(isReady(future));
    promise.set_exception(std::make_exception_ptr(std::exception()));
    EXPECT_TRUE(isReady(future));
    EXPECT_THROW(future.get(), std::exception);
}

TEST(isReadyTest, ValidStringFutureWithExceptionIsReady)
{
    std::promise<std::string> promise;
    std::future<std::string> future = promise.get_future();
    EXPECT_FALSE(isReady(future));
    promise.set_exception(std::make_exception_ptr(std::exception()));
    EXPECT_TRUE(isReady(future));
    EXPECT_THROW(future.get(), std::exception);
}

// makeReadyFuture tests:

TEST(makeReadyFutureTest, CreatesReadyIntFuture)
{
    int const x = 10;
    std::future<int> future = makeReadyFuture(x);
    EXPECT_TRUE(isReady(future));
    EXPECT_EQ(future.get(), x);
}

TEST(makeReadyFutureTest, CreatesReadyStdStringFuture)
{
    std::string const s = "foo";
    std::future<std::string> future = makeReadyFuture(s);
    EXPECT_TRUE(isReady(future));
    EXPECT_EQ(future.get(), s);
}

TEST(makeReadyFutureTest, CreatesReadyCStringFuture)
{
    char const* const s = "foo";
    std::future<char const*> future = makeReadyFuture(s);
    EXPECT_TRUE(isReady(future));
    EXPECT_EQ(future.get(), "foo");
}

TEST(makeReadyFutureTest, CreatesReadyFutureOfNonCopyable)
{
    std::unique_ptr<int> p = std::make_unique<int>(10);
    std::future<std::unique_ptr<int>> future = makeReadyFuture(std::move(p));
    EXPECT_TRUE(isReady(future));
    std::unique_ptr<int> q = future.get();
    EXPECT_EQ(*q, 10);
}
