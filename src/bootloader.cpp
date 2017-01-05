#include "bootloader.hpp"
#include "usart_downloader.hpp"

bool BootLoader::specialMode()
{
    return true; // implement based on system flags 
}

void BootLoader::bootSpecialMode()
{
    bootDFU();
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