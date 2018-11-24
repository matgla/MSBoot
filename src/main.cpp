#include <chrono>
#include <cstdint>

#include <gsl/span>

#include "eul/logger.hpp"
#include "hal/gpio.hpp"
#include "hal/time/sleep.hpp"
#include "hal/time/time.hpp"
#include "hal/usart.hpp"

int main()
{
    constexpr hal::gpio::PB12 pin;
    constexpr hal::interfaces::Usart1 usart;
    hal::time::Time::init();
    // constexpr hal::gpio::PA1 pin2;
    pin.init(hal::gpio::Output::OutputPushPull, hal::gpio::Speed::Low);
    //pin.setHigh();
    usart.init(9600);
    usart.write("aaa");
    // eul::Logger<hal::usart::Usart1> logger("main");
    usart.onData([&usart](const uint8_t data) { usart.write(data); });
    while (true)
    {

        // logger.info() << "working...";
        hal::time::sleep(std::chrono::seconds(1));
        pin.setHigh();
        hal::time::sleep(std::chrono::seconds(1));
        pin.setLow();
        // usart.write("bv");
    }

    return 0;
}
