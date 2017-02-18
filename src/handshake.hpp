#pragma once

class Handshake
{
  public:
    void perform();

  private:
    void waitForClient();

    void send();
};