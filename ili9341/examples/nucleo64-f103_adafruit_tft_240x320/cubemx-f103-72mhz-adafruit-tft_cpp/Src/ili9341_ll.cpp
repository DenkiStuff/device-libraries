#include "ili9341_ll.hpp"


void ili9341_ll_set_command_mode()
{
	HAL_GPIO_WritePin(ILI9341_CMD_DATA_GPIO_Port, ILI9341_CMD_DATA_Pin, GPIO_PIN_RESET);
}

void ili9341_ll_set_data_mode()
{
	HAL_GPIO_WritePin(ILI9341_CMD_DATA_GPIO_Port, ILI9341_CMD_DATA_Pin, GPIO_PIN_SET);
}

void ili9341_ll_spi_select()
{
	HAL_GPIO_WritePin(ILI93411_nCS_GPIO_Port, ILI93411_nCS_Pin, GPIO_PIN_RESET);
}

void ili9341_ll_spi_deselect()
{
	HAL_GPIO_WritePin(ILI93411_nCS_GPIO_Port, ILI93411_nCS_Pin, GPIO_PIN_SET);
}

void ili9341_ll_spiWrite(uint8_t b)
{
	HAL_SPI_Transmit(&ILI9341_LL_SPI_HANDLE, &b, 1U, 1000);
}

void ili9341_ll_spiWrite16(uint16_t b)
{
	uint8_t tmp = b >> 8;
	HAL_SPI_Transmit(&ILI9341_LL_SPI_HANDLE, &tmp, 1U, 1000);
	tmp = b & 0xFF;
	HAL_SPI_Transmit(&ILI9341_LL_SPI_HANDLE, &tmp, 1U, 1000);
}

void ili9341_ll_spiWrite32(uint32_t b)
{
	uint8_t tmp = (b >> 24) & 0xFF;
	HAL_SPI_Transmit(&ILI9341_LL_SPI_HANDLE, &tmp, 1U, 1000);
	tmp = (b >> 16) & 0xFF;
	HAL_SPI_Transmit(&ILI9341_LL_SPI_HANDLE, &tmp, 1U, 1000);
	tmp = (b >> 8) & 0xFF;
	HAL_SPI_Transmit(&ILI9341_LL_SPI_HANDLE, &tmp, 1U, 1000);
	tmp = b & 0xFF;
	HAL_SPI_Transmit(&ILI9341_LL_SPI_HANDLE, &tmp, 1U, 1000);
}
