#include "usart_downloader.hpp"

using usart = hw::USART<hw::USARTS::USART1_PP1>;

UsartDownloader::UsartDownloader(const Logger& logger) : logger_(logger) 
{

}

void UsartDownloader::waitForProvider()
{
    char downloadCommand[4] = "DWN";
    char buffer[10];
    bool connection = false;
    int index = 0;
    logger_ << Level::INFO << "Waiting for connection\n";
    while (!connection) 
    {
        if (usart::getUsart().getBuffer().size()) 
        {
            char data = usart::getUsart().getBuffer().getByte();
            logger_ << Level::INFO << "Received byte: " << (int)data << "\n";
            if (data == '\n')
            {
                if (strcmp(buffer, downloadCommand) == 0)
                {
                    logger_ << Level::INFO << "Received " << buffer << " command\n";
                }
                index = 0;
                
            }
            else
            {
                buffer[index++] = data;
                buffer[index] = 0;
                logger_ << Level::INFO << "Current  " << buffer << " command\n";
                
            }
        }
    }
    
}