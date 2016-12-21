#include "kernel.hpp"
#include "lcd.h"
#include "sdram.h"
#include "usart.hpp"
#include "usb.h"

void hardwareInitialize() {
    // sdram initalization
    GPIO_FMC_init();
    USART_GPIO_init();

    FMC_init();

    // video initalzation
    SettingsInitialize();

    LCD_init();

    LCD_layerInit();
    // usb initalization
    USBInit();

    USART_NVIC_init();
    USART_init();
    USART_SendData(USART1, ' ');
    USART_SendData(USART1, ' ');
}
