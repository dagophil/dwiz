#include <common/string_utils.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>

using namespace dwiz;

TEST(splitHostAndPort, TestSplitWithDomain)
{
    auto const hostPort = splitHostAndPort("some_dummy_page.com:123");
    EXPECT_EQ(hostPort.first, "some_dummy_page.com");
    EXPECT_EQ(hostPort.second, 123);
}

TEST(splitHostAndPort, TestSplitWithMultipleColons)
{
    auto const hostPort = splitHostAndPort("some:text:12:123");
    EXPECT_EQ(hostPort.first, "some:text:12");
    EXPECT_EQ(hostPort.second, 123);
}

TEST(splitHostAndPort, TestSplitWithHttpDomain)
{
    auto const hostPort = splitHostAndPort("http://some_dummy_page.com:123");
    EXPECT_EQ(hostPort.first, "http://some_dummy_page.com");
    EXPECT_EQ(hostPort.second, 123);
}

TEST(splitHostAndPort, TestSplitWithIP)
{
    auto const hostPort = splitHostAndPort("127.0.0.1:80");
    EXPECT_EQ(hostPort.first, "127.0.0.1");
    EXPECT_EQ(hostPort.second, 80);
}

TEST(splitHostAndPort, TestNoColonThrows)
{
    EXPECT_THROW(splitHostAndPort("some_text_123"), std::runtime_error);
}

TEST(splitHostAndPort, TestNoHostThrows)
{
    EXPECT_THROW(splitHostAndPort(":123"), std::runtime_error);
}

TEST(splitHostAndPort, TestNoPortThrows)
{
    EXPECT_THROW(splitHostAndPort("domain:"), std::runtime_error);
}

TEST(splitHostAndPort, TestPortIsStringThrows)
{
    EXPECT_THROW(splitHostAndPort("a:a"), std::runtime_error);
}

TEST(splitHostAndPort, TestPortIsFloatThrows)
{
    EXPECT_THROW(splitHostAndPort("a:1.5"), std::runtime_error);
}

TEST(splitHostAndPort, TestNegativePortThrows)
{
    EXPECT_THROW(splitHostAndPort("a:-1"), std::runtime_error);
}
