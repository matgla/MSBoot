#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "defines.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"


#include "usb_bsp.h"
#include "usbh_core.h"
#include "usbh_hid_core.h"
#include "usbh_usr.h"


typedef struct { uint8_t cleanStatusAfterRead; } usbSettings;

typedef enum {
    usbDevice_disconnected,
    usbDevice_connected,
    usbDevice_attached,
    usbDevice_reset,
    usbDevice_wrongSpeed,
    usbDevice_notSupported
} usbDeviceStatus;

typedef enum { usb_uninitialized, usb_error, usb_initialized } usbStatusList;

typedef struct {
    usbStatusList status;
    usbDeviceStatus deviceStatus;
    usbSettings settings;
} usbStatus;

typedef enum { key_pressed = 0, key_released } keyStatus;

typedef struct {
    keyStatus key_status;
    uint8_t data;
} keyboardDevice;

usbStatus *getUsbStatus(void);
keyboardDevice *getKeyboard(void);
usbDeviceStatus readKeyboardData(keyboardDevice *keyboard);

void USBInit(void);
void USBProcess(void);

#ifdef __cplusplus
}
#endif
