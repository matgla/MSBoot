#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _colors565 {
    RGB_565_COLOR_WHITE = 0xffff,
    RGB_565_COLOR_GREEN = 0X07e0,
    RGB_565_COLOR_BLACK = 0x0000,
    RGB_565_COLOR_BLUE = 0x002F,
    RGB_565_COLOR_RED = 0xF800,
    RGB_565_COLOR_YELLOW = 0xFFE0
} rgb565Colors;

#ifdef __cplusplus
}
#endif