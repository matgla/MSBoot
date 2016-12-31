#include "usart_downloader.hpp"

UsartDownloader::UsartDownloader(const Logger& logger) : logger_(logger) 
{

}

void UsartDownloader::waitForProvider()
{
    char downloadCommand[3] = {'D', 'W', 'N'};
    bool connection = false;
    int index = 0;
    logger_ << Level::INFO << "Waiting for connection\n";
    while (!connection) 
    {
        if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE)) 
        {
            u16 data = USART_ReceiveData(USART1);
            char c = data & 0xff;
            char c2 = data & 0x00ff;
            logger_ << Level::INFO << "Received data: " << c << c2 << "\n";

            if (c == downloadCommand[index++])
            {
                if (index == 3)
                {
                   logger_ << Level::INFO << "Received connection to programmer\n";
                 //   writeToMemory();
                }
            }
            else
            {
                index = 0;
            }
        }
    }
    
}