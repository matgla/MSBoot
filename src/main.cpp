#include "eul/logger.hpp"
#include "hal/gpio.hpp"
#include "hal/time/sleep.hpp"
#include "hal/usart.hpp"

#include <chrono>


int main()
{
    constexpr hal::gpio::PA0 pin;
    constexpr hal::gpio::PA1 pin2;
    pin.init(hal::gpio::GpioSpeed::Low,
             hal::gpio::GpioMode::OutputPushPull);

    pin.setLow();
    pin.setHigh();
    hal::usart::USART1::init();
    eul::Logger<hal::usart::USART1> logger("main");
    while (true)
    {
        logger.info() << "working...";
        hal::time::sleep(std::chrono::seconds(1));
        pin2.setHigh();
        hal::time::sleep(std::chrono::seconds(1));
        pin2.setLow();
    }

    return 0;
}
