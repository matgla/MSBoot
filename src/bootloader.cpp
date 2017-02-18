#include "bootloader.hpp"
#include "messages.hpp"
#include "usart.hpp"
#include "usart_downloader.hpp"

BootLoader::BootLoader(Logger& logger)
    : logger_(logger)
{
    hw::USART<hw::USARTS::USART1_PP1>::getUsart().setReceiveCallback(&BootLoader::handleEvent);
}

BootLoader::~BootLoader()
{
    hw::USART<hw::USARTS::USART1_PP1>::getUsart().setDefaultReceiver();
}

void BootLoader::handleEvent(void* event)
{
    Logger logger("EV_HAN\0");
    u8* payload = static_cast<u8*>(event);
    Messages id = static_cast<Messages>(payload[1]);
    switch (id)
    {
        case Messages::CLIENT_INFO:
        {
            ClientInfo info;
            memcpy(&info, event, sizeof(ClientInfo));
            logger << Level::INFO << "Received handshake from: " << info.name_ << "\n";
        }
        break;
        default:
        {
        }
    }
}

bool BootLoader::specialMode()
{
    return true; // TODO: implement based on system flags
}

void BootLoader::bootSpecialMode()
{
    //Handshake
}

void BootLoader::bootFW()
{
    // TODO: implement
}

void BootLoader::bootDFU()
{
    UsartDownloader dwnl(logger_);
    dwnl.waitForProvider();
    dwnl.writeToMemory();
}