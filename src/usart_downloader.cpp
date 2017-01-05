#include "usart_downloader.hpp"

using usart = hw::USART<hw::USARTS::USART1_PP1>;

UsartDownloader::UsartDownloader(const Logger& logger) : logger_(logger) 
{

}

void UsartDownloader::writeToMemory()
{
    logger_ << Level::INFO << "Waiting for soft\n";
    u32 softwareSize = 0;
    usart::getUsart().send(10, 2);
    auto msg = usart::getUsart().getMessage();
    logger_ << Level::INFO << "Received message: " << msg.payload[0] << ":" << msg.payload[1] << ":" << msg.payload[2] << ":" << msg.payload[3] << ":"  << "\r\n";
    softwareSize = msg.payload[0] << 12;
    softwareSize += msg.payload[1] << 8;
    softwareSize += msg.payload[2] << 4;
    softwareSize += msg.payload[3];
    logger_ << Level::INFO << "Received soft size: " << softwareSize << "\r\n";
}

void UsartDownloader::waitForProvider()
{
    char downloadCommand[4] = "DWN";
    char buffer[10];
    bool connection = false;
    int index = 0;
    logger_ << Level::INFO << "Waiting for connection \r\n";
    while (!connection) 
    {
        usart::getUsart().send(10, 1);

        logger_ << Level::INFO << "Waiting for message!\r\n";
        auto msg = usart::getUsart().getMessage();
        logger_ << Level::INFO << "Received message with: " << msg.fd << "\r\n";
        if (msg.fd == 10 && msg.payload[0] == 1)
        {
            logger_ << Level::INFO << "Connected to device\r\n";
            connection = true;
        }

        //     logger_ << Level::INFO << "Received byte: " << (int)data << "\n";
        //     if (data == '\n')
        //     {
        //         if (strcmp(buffer, downloadCommand) == 0)
        //         {
        //             logger_ << Level::INFO << "Received " << buffer << " command\n";
        //         }
        //         index = 0;
                
        //     }
        //     else
        //     {
        //         buffer[index++] = data;
        //         buffer[index] = 0;
        //         logger_ << Level::INFO << "Current  " << buffer << " command\n";
                
        //     }
        
    }
     logger_ << Level::INFO << "Exit form func\r\n";
    
}