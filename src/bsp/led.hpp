#pragma once

namespace bsp
{

enum class Leds
{
    Led1,
    LcdBacklight
};

template <Leds led>
class Led
{
  public:
    Led();

    void on();
    void off();
};


} // namespace bsp
