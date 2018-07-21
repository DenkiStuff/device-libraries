#ifndef __oled_H
#define __oled_H

#include "stm32f3xx_hal.h"


#define OLED_COL_WIDTH 96U
#define OLED_ROW_HEIGHT 64U

#define CMD_SETCOLUMNADDRESS                0x15
#define CMD_SETROWADDRESS                   0x75


typedef enum {
	Enabled   = 0x00, /*scale 0-255 to 0-31 for Red/Blue | 0-63 for Green */
	Disabled  = 0x01, /*no scale, expect 0-31 for Red/Blue | 0-63 for green. Anything over 31/63 will truncated to 31/63 */
} RGB565Scaling;

void oled_init();
void oled_clearscreen();
void oled_drawline (uint8_t col_start, uint8_t row_start, uint8_t col_end, uint8_t row_end, uint8_t red, uint8_t green, uint8_t blue);
void oled_rawpixeldata(uint8_t col_start, uint8_t row_start, uint8_t col_end, uint8_t row_end, uint16_t * pixel_data_Array);



#endif /*__oled_H */