#include "eul/logger.hpp"
#include "hal/gpio.hpp"
#include "hal/time/sleep.hpp"
#include "hal/time/time.hpp"
#include "hal/usart.hpp"

#include <chrono>

extern "C"
{
    void _init()
    {
    }
}

int main()
{
    constexpr hal::gpio::PB12 pin;

    hal::time::Time::init();
    // constexpr hal::gpio::PA1 pin2;
    pin.init(hal::gpio::Output::OutputPushPull, hal::gpio::Speed::Low);
    //pin.setHigh();
    hal::interfaces::Usart1::init(9600);
    hal::interfaces::Usart1::write("aaa");
    // eul::Logger<hal::usart::Usart1> logger("main");
    while (true)
    {

        // logger.info() << "working...";
        hal::time::sleep(std::chrono::seconds(1));
        pin.setHigh();
        hal::time::sleep(std::chrono::seconds(1));
        pin.setLow();
        hal::interfaces::Usart1::write("bv");
    }

    return 0;
}
