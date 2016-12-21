#include "lcd.h"
#include "font.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_ltdc.h"
#include "rgb_colors.h"
#include <string.h>


lcd_settings global_lcd_setting;

uint16_t *video_memory = (uint16_t *)VIDEO_MEMORY_START;

static font *use_font;

lcd_settings* getLCDsettings() {
	return &global_lcd_setting;
}

u16* setVideoMemoryAddress(u16 *newVideoMemoryAddress) {
    video_memory = newVideoMemoryAddress;
}

void SettingsInitialize(void) {
	global_lcd_setting.cursor_position_offset_x = 2;
	global_lcd_setting.cursor_position_offset_y = 2;
	global_lcd_setting.cursor_position_x = 0;
	global_lcd_setting.cursor_position_y = use_font->height + global_lcd_setting.cursor_position_offset_y;

	use_font =  &font_5x8;
}

void LCD_init(void) {
	LTDC_InitTypeDef LTDC_init;
	LCD_GPIO_init();

	RCC_PLLSAIConfig(402, 7, 2);
	RCC_LTDCCLKDivConfig(RCC_PLLSAIDivR_Div8);
	RCC_PLLSAICmd(ENABLE);

	while(RCC_GetFlagStatus(RCC_FLAG_PLLSAIRDY) == RESET) {
	}

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_LTDC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2D, ENABLE);

	LTDC_init.LTDC_AccumulatedActiveH 	= ACTIVE_H;
	LTDC_init.LTDC_AccumulatedActiveW 	= ACTIVE_W;
	LTDC_init.LTDC_AccumulatedHBP		= HBP;
	LTDC_init.LTDC_AccumulatedVBP		= VBP;
	LTDC_init.LTDC_BackgroundBlueValue	= 0;
	LTDC_init.LTDC_BackgroundGreenValue = 0;
	LTDC_init.LTDC_BackgroundRedValue	= 0;
	LTDC_init.LTDC_DEPolarity			= LTDC_DEPolarity_AL;
	LTDC_init.LTDC_HSPolarity			= LTDC_HSPolarity_AL;
	LTDC_init.LTDC_HorizontalSync		= HSYNC;
	LTDC_init.LTDC_PCPolarity			= LTDC_PCPolarity_IPC;
	LTDC_init.LTDC_TotalHeigh			= TOTAL_HEIGHT;
	LTDC_init.LTDC_TotalWidth			= TOTAL_WIDTH;
	LTDC_init.LTDC_VSPolarity			= LTDC_VSPolarity_AL;
	LTDC_init.LTDC_VerticalSync			= VSYNC;

	LTDC_Init(&LTDC_init);

}


void LCD_layerInit(void) {
	LTDC_Layer_InitTypeDef LTDC_Layer_InitStruct;

	LTDC_Layer_InitStruct.LTDC_HorizontalStart 		= HSYNC + HBP;
	LTDC_Layer_InitStruct.LTDC_HorizontalStop 		= HSYNC + HBP + LCD_WIDTH - 1;
	LTDC_Layer_InitStruct.LTDC_VerticalStart	 	= VSYNC + VBP;
	LTDC_Layer_InitStruct.LTDC_VerticalStop	 		= VSYNC + VBP + LCD_HEIGHT - 1;
    LTDC_Layer_InitStruct.LTDC_PixelFormat 			= LTDC_Pixelformat_RGB565;
    LTDC_Layer_InitStruct.LTDC_ConstantAlpha 		= 0xFF;
    LTDC_Layer_InitStruct.LTDC_DefaultColorBlue 	= 0;
    LTDC_Layer_InitStruct.LTDC_DefaultColorGreen 	= 0;
    LTDC_Layer_InitStruct.LTDC_DefaultColorRed 		= 0;
    LTDC_Layer_InitStruct.LTDC_DefaultColorAlpha 	= 0;
    LTDC_Layer_InitStruct.LTDC_BlendingFactor_1 	= LTDC_BlendingFactor1_CA;
    LTDC_Layer_InitStruct.LTDC_BlendingFactor_2 	= LTDC_BlendingFactor2_CA;

	LTDC_Layer_InitStruct.LTDC_CFBLineLength 		= LCD_WIDTH * BYTES_PER_PIXEL + 3;
	LTDC_Layer_InitStruct.LTDC_CFBPitch 			= LCD_WIDTH * BYTES_PER_PIXEL;
	LTDC_Layer_InitStruct.LTDC_CFBLineNumber 		= LCD_HEIGHT;
	LTDC_Layer_InitStruct.LTDC_CFBStartAdress 		= VIDEO_MEMORY_START;
	LTDC_LayerInit(LTDC_Layer1, &LTDC_Layer_InitStruct);

	LTDC_Layer_InitStruct.LTDC_CFBStartAdress 		= VIDEO_MEMORY_START+VIDEO_FRAME_OFFSET;

	LTDC_LayerInit(LTDC_Layer2, &LTDC_Layer_InitStruct);

	LTDC_ReloadConfig(LTDC_IMReload);
	LTDC_LayerCmd(LTDC_Layer1, ENABLE);
	LTDC_LayerCmd(LTDC_Layer2, ENABLE);
	LTDC_ReloadConfig(LTDC_IMReload);
	//LTDC_DitherCmd(ENABLE);
	LTDC_Cmd(ENABLE);
	LTDC_LayerAlpha(LTDC_Layer1, 255);
	LTDC_LayerAlpha(LTDC_Layer2, 0);
	LTDC_ReloadConfig(LTDC_IMReload);
}

void LCD_GPIO_init(void){

	GPIO_InitTypeDef GPIO_init;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB |
			RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOG |
			RCC_AHB1Periph_GPIOF, ENABLE);

	GPIO_init.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_init.GPIO_OType	= GPIO_OType_PP;
	GPIO_init.GPIO_Mode		= GPIO_Mode_AF;
	GPIO_init.GPIO_PuPd		= GPIO_PuPd_NOPULL;

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_LTDC);
	GPIO_init.GPIO_Pin = GPIO_Pin_3  | GPIO_Pin_4 | GPIO_Pin_6
						|GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_Init(GPIOA, &GPIO_init);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF9_LTDC);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF9_LTDC);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_LTDC);
	GPIO_init.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1  | GPIO_Pin_8
						|GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_Init(GPIOB, &GPIO_init);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource2, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_LTDC);

	GPIO_init.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_6
					    |GPIO_Pin_7 | GPIO_Pin_10;
	GPIO_Init(GPIOC, &GPIO_init);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource3, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_LTDC);

	GPIO_init.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_6;
	GPIO_Init(GPIOD, &GPIO_init);

	GPIO_PinAFConfig(GPIOG, GPIO_PinSource6, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource7, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource10, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource11, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource12, GPIO_AF_LTDC);
	GPIO_init.GPIO_Pin = GPIO_Pin_6  | GPIO_Pin_7 | GPIO_Pin_10
						|GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_Init(GPIOG, &GPIO_init);

	GPIO_PinAFConfig(GPIOF, GPIO_PinSource10, GPIO_AF_LTDC);
	GPIO_init.GPIO_Pin = GPIO_Pin_10;

	GPIO_Init(GPIOF, &GPIO_init);
}

void DrawChar(uint16_t color, char c) {

	uint16_t *video = video_memory;
	int i, j;
	if(c == 0xA) {
		global_lcd_setting.cursor_position_x=0;
		global_lcd_setting.cursor_position_y+=use_font->height+2;
		return;
	}
	else if(c == 0x08) {
		global_lcd_setting.cursor_position_x-=(use_font->width+2);
		c = ' ';
	}
	uint8_t *font_ptr = &use_font->array[(c-32)+(c-32)*(use_font->height-1)];
	if(global_lcd_setting.cursor_position_x + use_font->width >= LCD_WIDTH) {
		global_lcd_setting.cursor_position_y += use_font->height+2;
		global_lcd_setting.cursor_position_x = 0;
	}
	if(global_lcd_setting.cursor_position_y + use_font->height >= LCD_HEIGHT) {
		global_lcd_setting.cursor_position_y = use_font->height+2;
		global_lcd_setting.cursor_position_x = 0;
        memset(video_memory, 0xFF, LCD_PIXELS*2);
	}
	video+= global_lcd_setting.cursor_position_x + global_lcd_setting.cursor_position_y*LCD_WIDTH;
	for(i=0; i < use_font->height; i++) {
		for(j=7; j >= 0; j--) {
			if((*font_ptr >> j) & 0x01){
				*(video++) = color;
			}
			else {
				video++;
			}
		}
		video+= LCD_WIDTH - 8;
		font_ptr++;

	}
	global_lcd_setting.cursor_position_x+=use_font->width+2;
}

void Print(char *string, uint16_t color) {
	for(uint32_t i=0; i < strlen(string); i++) {
		DrawChar(color, string[i]);
	}
}

void ClearScreen(void) {
	FillScreen(RGB_565_COLOR_WHITE);
}

void FillScreen(u16 color) {
	u16 *video_ptr = video_memory;
	for (int i = 0; i < LCD_HEIGHT; ++i) {
		for (int j = 0; j < LCD_WIDTH; ++j) {
			*(video_ptr++) = color;
		}
	}
}