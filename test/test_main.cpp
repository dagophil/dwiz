#include <common/dwiz_std.h>
#include <common/log/logger.h>
#include <gtest/gtest.h>

int main(int argc, char** argv)
{
    DWIZ_INIT_LOG(".log-config");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
