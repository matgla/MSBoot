#include "hal/gpio/digitalOut.hpp"

int main()
{
    hal::gpio::DigitalOut<hal::gpio::Port::A> led(1);
    led.high();
    led.low();

    while (true)
    {
    }

    return 0;
}
