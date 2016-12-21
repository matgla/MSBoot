#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>

#include "defines.h"
#include "sdram.h"
#include "stm32f4xx_conf.h"
#include "system_stm32f4xx.h"

#define LCD_WIDTH 640
#define LCD_HEIGHT 480
#define LCD_PIXELS LCD_WIDTH *LCD_HEIGHT

#define BYTES_PER_PIXEL 2

#define HFP 16
#define HSYNC 96
#define HBP 48

#define VFP 10
#define VSYNC 2
#define VBP 33

#define ACTIVE_W (HSYNC + LCD_WIDTH + HBP - 1)
#define ACTIVE_H (VSYNC + LCD_HEIGHT + VBP - 1)

#define TOTAL_WIDTH (HSYNC + HBP + LCD_WIDTH + HFP - 1)
#define TOTAL_HEIGHT (VSYNC + VBP + LCD_HEIGHT + VFP - 1)

#define VIDEO_MEMORY_START SDRAM_START_ADDRESS
#define VIDEO_FRAME_OFFSET ((u32)LCD_PIXELS)

typedef struct lcd_settings_ {
    u16 cursor_position_x;
    u16 cursor_position_y;
    u16 cursor_position_offset_x;
    u16 cursor_position_offset_y;
} lcd_settings;

void LCD_init(void);
void LCD_GPIO_init(void);
void LCD_layerInit(void);
void SettingsInitialize(void);
void DrawPixel(u8 pos_x, u8 pos_y, u16 color);
void DrawCharAtPosition(u8 pos_x, u8 pos_y, u16 color, char c);
void DrawChar(u16 color, char c);
void ClearScreen(void);
void FillScreen(u16 color);
void Print(char *string, u16 color);
lcd_settings *getLCDsettings();
u16 *setVideoMemoryAddress(u16 *newVideoMemoryAddress);

#ifdef __cplusplus
}
#endif