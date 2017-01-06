#include <functional>
#include <string>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

class AppTests : public ::testing::Test
{
    virtual void SetUp() {}
    virtual void TearDown()
    {
    }
};

TEST_F(AppTests, LoopShouldPrintTime)
{
    EXPECT_EQ(0, 0);
}