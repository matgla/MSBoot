#pragma once

#include "logger.hpp"

class BootLoader
{
  public:
    BootLoader(Logger& logger);
    ~BootLoader();
    bool specialMode();
    void bootSpecialMode();
    void bootFW();
    static void handleEvent(void* event);

  private:
    void bootRecovery();
    void bootDFU();

    Logger& logger_;
};