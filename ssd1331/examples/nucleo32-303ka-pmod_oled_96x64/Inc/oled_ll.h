#ifndef __oled_ll_H
#define __oled_ll_H


#include "main.h"
#include "stm32f3xx_hal.h"

	// ----- TFT Control Pins
	// PA2(A7)-Data(H)/Command(L)
	// PA7(A6)-MOSI
	// PA6(A5)-NSS
	// PA5(A6)-SCK
	// PA4(A3)-Reset
	// PA3(A2)-VCC Enable
	// PA1(A1)-PMod Enable
	// PA6() - Chip Select	

#define oled_handle hspi1

extern SPI_HandleTypeDef oled_handle;

void oled_ll_set_command_mode();
void oled_ll_set_data_mode();
void oled_ll_select_oled();
void oled_ll_deselect_oled();
void oled_ll_spi_senddata8(uint8_t data);
void oled_ll_reset();
void oled_ll_clear_reset();
void oled_ll_vccen_set();
void oled_ll_vccen_clear();
void oled_ll_pmoden_set();
void oled_ll_pmoden_clear();

#endif /*__oled_ll_H */