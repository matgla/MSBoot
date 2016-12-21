#pragma once

typedef enum {
    memoryInitializationOk,
    memoryInitializationError,
    videoInitializationOk,
    videoInitializationError,
    usbInitializationOk,
    usbInitializationError
} hwInitializeStatus;

void hardwareInitialize();