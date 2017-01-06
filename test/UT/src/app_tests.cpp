#include <functional>
#include <string>

#include "cpp_free_mock.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "lcd.hpp"
#include "app.hpp"
#include "rtc.hpp"

class AppTests : public ::testing::Test
{
    virtual void SetUp() {}
    virtual void TearDown()
    {
        CLEAR_MOCKER();
    }
};

TEST_F(AppTests, LoopShouldPrintTime)
{
    App app;
    Rtc rtcMock;

    const u8 NR_OF_SECONDS = 12;
    const u8 NR_OF_MINUTES = 2;
    const u8 NR_OF_HOURS = 15;

    auto printMock = MOCKER(LCD::print);
    auto clearMock = MOCKER(LCD::clear);

    auto getSecondsMock = MOCKER(&Rtc::getSeconds);
    auto getHoursMock = MOCKER(&Rtc::getHours);
    auto getMinutesMock = MOCKER(&Rtc::getMinutes);

    EXPECT_CALL(*clearMock, MOCK_FUNCTION())
        .Times(testing::Exactly(1));

    EXPECT_CALL(*getHoursMock, MOCK_FUNCTION(&app.getRtc()))
        .Times(testing::Exactly(1))
        .WillOnce(testing::Return(NR_OF_HOURS));

    EXPECT_CALL(*getMinutesMock, MOCK_FUNCTION(&app.getRtc()))
        .Times(testing::Exactly(1))
        .WillOnce(testing::Return(NR_OF_MINUTES));

    EXPECT_CALL(*getSecondsMock, MOCK_FUNCTION(&app.getRtc()))
        .Times(testing::Exactly(1))
        .WillOnce(testing::Return(NR_OF_SECONDS));

    EXPECT_CALL(*printMock, MOCK_FUNCTION(1, 1, testing::StrEq("15:02:12")))
        .Times(testing::Exactly(1));

    app.loop();
}