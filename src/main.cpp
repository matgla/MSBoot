#include "eul/logger.hpp"
#include "hal/gpio.hpp"
#include "hal/time/sleep.hpp"
// #include "hal/usart.hpp"

#include <chrono>

extern "C"
{
    void _init()
    {
    }
}

int main()
{
    constexpr hal::gpio::PA5 pin;
    // constexpr hal::gpio::PA1 pin2;
    pin.init(hal::gpio::GpioSpeed::Low,
             hal::gpio::GpioMode::OutputPushPull);
    pin.setHigh();
    //pin.setHigh();
    // hal::usart::USART1::init();
    // eul::Logger<hal::usart::USART1> logger("main");
    while (true)
    {
        // logger.info() << "working...";
        // hal::time::sleep(std::chrono::seconds(1));
        // pin2.setHigh();
        // hal::time::sleep(std::chrono::seconds(1));
        // pin2.setLow();
    }

    return 0;
}
