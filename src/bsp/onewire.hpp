#pragma once

namespace bsp
{

enum class OneWires
{
    OneWire1,
    OneWire2,
    OneWire3
};

enum class BusState
{
    Low,
    High
};


template <OneWires oneWire>
class OneWire
{
public:
    OneWire();

    void setAsInput();
    void setAsOutput();

    BusState getState();
    void setState(BusState state);
};

} // namespace bsp
