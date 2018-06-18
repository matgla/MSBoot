#include "bsp/onewire.hpp"

#include <stm32f10x.h>
#include <stm32f10x_gpio.h>

#include "bsp/stm32f1_common/helpers.hpp"

#define ONE_WIRE_PORT GPIOB
#define ONE_WIRE_PIN GPIO_Pin_14
#define RCC_ONE_WIRE RCC_APB2Periph_GPIOB

#define ONE_WIRE_PORT_2 GPIOB
#define ONE_WIRE_PIN_2 GPIO_Pin_3
#define RCC_ONE_WIRE_2 RCC_APB2Periph_GPIOB

#define ONE_WIRE_PORT_3 GPIOA
#define ONE_WIRE_PIN_3 GPIO_Pin_15
#define RCC_ONE_WIRE_3 RCC_APB2Periph_GPIOA

namespace bsp
{

template <>
OneWire<OneWires::OneWire1>::OneWire()
{
    RCC_APB2PeriphClockCmd(RCC_ONE_WIRE, ENABLE);
    Helper::configureGpio(ONE_WIRE_PORT, ONE_WIRE_PIN, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
}

template <>
void OneWire<OneWires::OneWire1>::setAsInput()
{
    Helper::configureGpio(ONE_WIRE_PORT, ONE_WIRE_PIN, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
}

template <>
void OneWire<OneWires::OneWire1>::setAsOutput()
{
    Helper::configureGpio(ONE_WIRE_PORT, ONE_WIRE_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
}

template <>
BusState OneWire<OneWires::OneWire1>::getState()
{
    if (GPIO_ReadInputDataBit(ONE_WIRE_PORT, ONE_WIRE_PIN))
    {
        return BusState::High;
    }
    return BusState::Low;
}

template <>
void OneWire<OneWires::OneWire1>::setState(BusState state)
{
    if (state == BusState::High)
    {
        GPIO_SetBits(ONE_WIRE_PORT, ONE_WIRE_PIN);
    }
    else
    {
        GPIO_ResetBits(ONE_WIRE_PORT, ONE_WIRE_PIN);
    }
}

// 2

template <>
OneWire<OneWires::OneWire2>::OneWire()
{
    RCC_APB2PeriphClockCmd(RCC_ONE_WIRE_2, ENABLE);
    Helper::configureGpio(ONE_WIRE_PORT_2, ONE_WIRE_PIN_2, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
}

template <>
void OneWire<OneWires::OneWire2>::setAsInput()
{
    Helper::configureGpio(ONE_WIRE_PORT_2, ONE_WIRE_PIN_2, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
}

template <>
void OneWire<OneWires::OneWire2>::setAsOutput()
{
    Helper::configureGpio(ONE_WIRE_PORT_2, ONE_WIRE_PIN_2, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
}

template <>
BusState OneWire<OneWires::OneWire2>::getState()
{
    if (GPIO_ReadInputDataBit(ONE_WIRE_PORT_2, ONE_WIRE_PIN_2))
    {
        return BusState::High;
    }
    return BusState::Low;
}

template <>
void OneWire<OneWires::OneWire2>::setState(BusState state)
{
    if (state == BusState::High)
    {
        GPIO_SetBits(ONE_WIRE_PORT_2, ONE_WIRE_PIN_2);
    }
    else
    {
        GPIO_ResetBits(ONE_WIRE_PORT_2, ONE_WIRE_PIN_2);
    }
}


// 3

template <>
OneWire<OneWires::OneWire3>::OneWire()
{
    RCC_APB2PeriphClockCmd(RCC_ONE_WIRE_3, ENABLE);
    Helper::configureGpio(ONE_WIRE_PORT_3, ONE_WIRE_PIN_3, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
}

template <>
void OneWire<OneWires::OneWire3>::setAsInput()
{
    Helper::configureGpio(ONE_WIRE_PORT_3, ONE_WIRE_PIN_3, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
}

template <>
void OneWire<OneWires::OneWire3>::setAsOutput()
{
    Helper::configureGpio(ONE_WIRE_PORT_3, ONE_WIRE_PIN_3, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
}

template <>
BusState OneWire<OneWires::OneWire3>::getState()
{
    if (GPIO_ReadInputDataBit(ONE_WIRE_PORT_3, ONE_WIRE_PIN_3))
    {
        return BusState::High;
    }
    return BusState::Low;
}

template <>
void OneWire<OneWires::OneWire3>::setState(BusState state)
{
    if (state == BusState::High)
    {
        GPIO_SetBits(ONE_WIRE_PORT_3, ONE_WIRE_PIN_3);
    }
    else
    {
        GPIO_ResetBits(ONE_WIRE_PORT_3, ONE_WIRE_PIN_3);
    }
}


} // namespace bsp