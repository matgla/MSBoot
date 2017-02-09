#include "gtest/gtest.h"

#include "messages.hpp"
#include "usart_downloader.hpp"

#include "gpio_mock.hpp"
#include "misc_mock.hpp"
#include "rcc_mock.hpp"
#include "usart_mock.hpp"

class UsartDownloaderShould : public ::testing::Test
{
  public:
    MOCK_TYPE(RCC_AHB1PeriphClockCmd)
    rccMock(GET_MOCK(RCC_AHB1PeriphClockCmd));
    UsartDownloaderShould()
    {
    }

    virtual void SetUp()
    {
        // if (!hw::USART<hw::USARTS::USART1_PP1>::initialized())
        // {
        //     expectInitialization();
        // }
    }

    virtual void TearDown()
    {
        VERIFY_MOCK(RCC_AHB1PeriphClockCmd);
        VERIFY_MOCK(RCC_APB2PeriphClockCmd);
        VERIFY_MOCK(GPIO_PinAFConfig);
        VERIFY_MOCK(GPIO_Init);
        VERIFY_MOCK(NVIC_Init);
        VERIFY_MOCK(USART_SendData);
        VERIFY_MOCK(USART_GetFlagStatus);
        VERIFY_MOCK(USART_GetITStatus);
    }
};

TEST_F(UsartDownloaderShould, WaitForSoftwareProvider)
{
    Logger logger;
    UsartDownloader downloader(logger);
}
TEST_F(UsartDownloaderShould, secondTest)
{
    Logger logger;
    UsartDownloader downloader(logger);
}