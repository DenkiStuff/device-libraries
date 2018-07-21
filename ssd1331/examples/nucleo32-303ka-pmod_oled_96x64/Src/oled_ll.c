#include "oled_ll.h"


void oled_ll_set_command_mode()
{
	HAL_GPIO_WritePin(oled_cd_GPIO_Port, oled_cd_Pin, GPIO_PIN_RESET);
}

void oled_ll_set_data_mode()
{
	HAL_GPIO_WritePin(oled_cd_GPIO_Port, oled_cd_Pin, GPIO_PIN_SET);
}

void oled_ll_select_oled()
{
	HAL_GPIO_WritePin(oled_cs_GPIO_Port, oled_cs_Pin, GPIO_PIN_RESET);
}

void oled_ll_deselect_oled()
{
	HAL_GPIO_WritePin(oled_cs_GPIO_Port, oled_cs_Pin, GPIO_PIN_SET);
}

void oled_ll_reset()
{
	HAL_GPIO_WritePin(oled_nrst_GPIO_Port, oled_nrst_Pin, GPIO_PIN_RESET);
}

void oled_ll_clear_reset()
{
	HAL_GPIO_WritePin(oled_nrst_GPIO_Port, oled_nrst_Pin, GPIO_PIN_SET);
}

void oled_ll_vccen_set()
{
	HAL_GPIO_WritePin(oled_vccen_GPIO_Port,oled_vccen_Pin, GPIO_PIN_SET);
}

void oled_ll_vccen_clear()
{
	HAL_GPIO_WritePin(oled_vccen_GPIO_Port,oled_vccen_Pin, GPIO_PIN_RESET);
}

void oled_ll_pmoden_set()
{
	HAL_GPIO_WritePin(oled_pmoden_GPIO_Port, oled_pmoden_Pin, GPIO_PIN_SET);
}

void oled_ll_pmoden_clear()
{
	HAL_GPIO_WritePin(oled_pmoden_GPIO_Port, oled_pmoden_Pin, GPIO_PIN_RESET);
}

void oled_ll_spi_senddata8(uint8_t data)
{
	HAL_SPI_Transmit(&oled_handle, &data, 1U, 1000);
}

