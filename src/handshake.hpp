#pragma once

#include "messages.hpp"

class Handshake
{
  public:
    Handshake();
    void perform();
    void registerClient(const ClientInfo& clientInfo);

  private:
    void waitForClient();
    void sendDeviceIdData();
    void send();
    bool connectedToClient_;
};