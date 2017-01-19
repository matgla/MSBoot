#include "gtest/gtest.h"

#include "messages.hpp"
#include "usart_downloader.hpp"

#include "usart_mock.hpp"

class UsartDownloaderShould : public ::testing::Test
{
  public:
    UsartDownloaderShould()
    {
        if (!hw::USART<hw::USARTS::USART1_PP1>::initialized())
        {
            expectInitialization();
        }
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(UsartDownloaderShould, WaitForSoftwareProvider)
{
    Logger logger;
    UsartDownloader downloader(logger);
}