#include "bootloader.hpp"

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