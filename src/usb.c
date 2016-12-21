#include "usb.h"

extern USB_OTG_CORE_HANDLE				USB_OTG_Core;
extern USBH_HOST						USB_Host;

keyboardDevice keyboardInternalState = {
	key_released,
	0
};

usbStatus currentUsbStatus = {
	usbDevice_disconnected,
	usb_uninitialized,
	{0}
};

void USBInit(void) {
	USBH_Init(&USB_OTG_Core, USB_OTG_HS_CORE_ID, &USB_Host, &HID_cb, &USR_Callbacks);
	currentUsbStatus.status = usb_initialized;
	currentUsbStatus.settings.cleanStatusAfterRead = 1;
}

void USBProcess(void) {
	if(currentUsbStatus.status != usb_initialized) {
		return;
	}
	USBH_Process(&USB_OTG_Core, &USB_Host);
}

usbStatus* getUsbStatus(void) {
	return &currentUsbStatus;
}
keyboardDevice* getKeyboard() {
	return &keyboardInternalState;
}
usbDeviceStatus readKeyboardData(keyboardDevice* keyboard) {
	if(currentUsbStatus.deviceStatus != usbDevice_connected) {
		return usbDevice_disconnected;
	}
	keyboard->key_status = keyboardInternalState.key_status;
	keyboard->data = keyboardInternalState.data;
	if(currentUsbStatus.settings.cleanStatusAfterRead == 1) {
		keyboardInternalState.key_status = key_released;
		keyboardInternalState.data = 0;
	}
	return usbDevice_connected;
}
