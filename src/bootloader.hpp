#pragma once

#include "logger.hpp"

class BootLoader
{
public:
    BootLoader(const Logger& logger) : logger_(logger) {}
    bool specialMode();
    void bootSpecialMode();
    void bootFW();
private:
    void bootRecovery();
    void bootDFU();
    
    const Logger& logger_;
};