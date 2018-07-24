#include "hal/gpio.hpp"
#include "hal/time/sleep.hpp"

#include <chrono>


int main()
{
    constexpr PA0 pin;
    constexpr PA1 pin2;
    pin.init(hal::gpio::GpioSpeed::Low,
             hal::gpio::GpioMode::OutputPushPull);

    pin.setLow();
    pin.setHigh();

    while (true)
    {
        hal::time::sleep(std::chrono::seconds(1));
        pin2.setHigh();
        hal::time::sleep(std::chrono::seconds(1));
        pin2.setLow();
    }

    return 0;
}
