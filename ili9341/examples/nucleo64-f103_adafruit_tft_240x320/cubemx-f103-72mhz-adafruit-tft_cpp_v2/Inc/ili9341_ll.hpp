#ifndef __ili9341_ll_h__
#define __ili9341_ll_h__

#include "main.h"
#include "stm32f1xx_hal.h"

#define ILI9341_LL_SPI_HANDLE hspi1

extern SPI_HandleTypeDef ILI9341_LL_SPI_HANDLE;


void ili9341_ll_set_command_mode();
void ili9341_ll_set_data_mode();
void ili9341_ll_spi_select();
void ili9341_ll_spi_deselect();
void ili9341_ll_spiWrite(uint8_t b);
void ili9341_ll_spiWrite16(uint16_t b);
void ili9341_ll_spiWrite32(uint32_t b);

#endif //__ili9341_ll_h__