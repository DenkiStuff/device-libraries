#include "ili9341.hpp"
#include "ili9341_ll.hpp"


ili9341::ili9341() : gfx(ILI9341_WIDTH, ILI9341_HEIGHT) {;}


/**************************************************************************/
/*!
   @brief  Write 8-bit data to command/register (DataCommand line low).
   Does not set up SPI transaction.
   @param  cmd The command/register to transmit
*/
/**************************************************************************/
void ili9341::writeCommand(uint8_t cmd){
    ili9341_ll_set_command_mode();
    spiWrite(cmd);
    ili9341_ll_set_data_mode();
}


void ili9341::writeData(uint8_t c)
{
	ili9341_ll_set_data_mode();
	ili9341_ll_spi_select();
    spiWrite(c);
	ili9341_ll_spi_deselect();
}

void ili9341::writeData16(uint16_t c)
{
	ili9341_ll_set_data_mode();
	ili9341_ll_spi_select();
    spiWrite16(c);
	ili9341_ll_spi_deselect();
}


void ili9341::writeData32(uint32_t c)
{
	ili9341_ll_set_data_mode();
	ili9341_ll_spi_select();
    spiWrite32(c);
	ili9341_ll_spi_deselect();
}


/**************************************************************************/
/*!
   @brief  Begin SPI transaction, for software or hardware SPI
*/
/**************************************************************************/
void ili9341::startWrite(void)
{
	ili9341_ll_spi_select();
}


/**************************************************************************/
/*!
   @brief  End SPI transaction, for software or hardware SPI
*/
/**************************************************************************/
void ili9341::endWrite(void)
{
	ili9341_ll_spi_deselect();
}

/**************************************************************************/
/*!
   @brief  Write 8-bit data via hardware or software SPI. Does not set up SPI transaction.
   @param  b Byte of data to write over SPI
*/
/**************************************************************************/
void ili9341::spiWrite(uint8_t b)
{
	ili9341_ll_spiWrite(b);
}


void ili9341::spiWrite16(uint32_t b)
{
	ili9341_ll_spiWrite16(b);
}

void ili9341::spiWrite32(uint32_t b)
{
	ili9341_ll_spiWrite32(b);
}


void ili9341::init()
{
	// Control Pins
    //digitalWrite(_dc, LOW);
	ili9341_ll_set_command_mode();
    //digitalWrite(_cs, HIGH);
    ili9341_ll_spi_deselect();

    startWrite();

	writeCommand(0xEF);
	spiWrite(0x03);
	spiWrite(0x80);
	spiWrite(0x02);

	writeCommand(0xCF);
	spiWrite(0x00);
	spiWrite(0XC1);
	spiWrite(0X30);

	writeCommand(0xED);
	spiWrite(0x64);
	spiWrite(0x03);
	spiWrite(0X12);
	spiWrite(0X81);

	writeCommand(0xE8);
	spiWrite(0x85);
	spiWrite(0x00);
	spiWrite(0x78);

	writeCommand(0xCB);
	spiWrite(0x39);
	spiWrite(0x2C);
	spiWrite(0x00);
	spiWrite(0x34);
	spiWrite(0x02);

	writeCommand(0xF7);
	spiWrite(0x20);

	writeCommand(0xEA);
	spiWrite(0x00);
	spiWrite(0x00);

	writeCommand(ILI9341_PWCTR1);    //Power control
	spiWrite(0x23);   //VRH[5:0]

	writeCommand(ILI9341_PWCTR2);    //Power control
	spiWrite(0x10);   //SAP[2:0];BT[3:0]

	writeCommand(ILI9341_VMCTR1);    //VCM control
	spiWrite(0x3e);
	spiWrite(0x28);

	writeCommand(ILI9341_VMCTR2);    //VCM control2
	spiWrite(0x86);  //--

	writeCommand(ILI9341_MADCTL);    // Memory Access Control
	spiWrite(0x48);

	writeCommand(ILI9341_VSCRSADD); // Vertical scroll
	spiWrite16(0);                 // Zero

	writeCommand(ILI9341_PIXFMT);
	spiWrite(0x55);

	writeCommand(ILI9341_FRMCTR1);
	spiWrite(0x00);
	spiWrite(0x18);

	writeCommand(ILI9341_DFUNCTR);    // Display Function Control
	spiWrite(0x08);
	spiWrite(0x82);
	spiWrite(0x27);

	writeCommand(0xF2);    // 3Gamma Function Disable
	spiWrite(0x00);

	writeCommand(ILI9341_GAMMASET);    //Gamma curve selected
	spiWrite(0x01);

	writeCommand(ILI9341_GMCTRP1);    //Set Gamma
	spiWrite(0x0F);
	spiWrite(0x31);
	spiWrite(0x2B);
	spiWrite(0x0C);
	spiWrite(0x0E);
	spiWrite(0x08);
	spiWrite(0x4E);
	spiWrite(0xF1);
	spiWrite(0x37);
	spiWrite(0x07);
	spiWrite(0x10);
	spiWrite(0x03);
	spiWrite(0x0E);
	spiWrite(0x09);
	spiWrite(0x00);

	writeCommand(ILI9341_GMCTRN1);    //Set Gamma
	spiWrite(0x00);
	spiWrite(0x0E);
	spiWrite(0x14);
	spiWrite(0x03);
	spiWrite(0x11);
	spiWrite(0x07);
	spiWrite(0x31);
	spiWrite(0xC1);
	spiWrite(0x48);
	spiWrite(0x08);
	spiWrite(0x0F);
	spiWrite(0x0C);
	spiWrite(0x31);
	spiWrite(0x36);
	spiWrite(0x0F);

	writeCommand(ILI9341_SLPOUT);    //Exit Sleep
	HAL_Delay(120);
	writeCommand(ILI9341_DISPON);    //Display on
	HAL_Delay(120);
	endWrite();

	_width  = ILI9341_WIDTH;
	_height = ILI9341_HEIGHT;

}


/**************************************************************************/
/*!
    @brief   Set the "address window" - the rectangle we will write to RAM with the next chunk of SPI data writes. The ILI9341 will automatically wrap the data as each row is filled
    @param   x  TFT memory 'x' origin
    @param   y  TFT memory 'y' origin
    @param   w  Width of rectangle
    @param   h  Height of rectangle
*/
/**************************************************************************/
void ili9341::setAddrWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	uint32_t xa = ((uint32_t)x << 16) | (x+w-1);
	uint32_t ya = ((uint32_t)y << 16) | (y+h-1);
	writeCommand(ILI9341_CASET); // Column addr set
	writeData32(xa);
	writeCommand(ILI9341_PASET); // Row addr set
	writeData32(ya);
	writeCommand(ILI9341_RAMWR); // write to RAM
}


/**************************************************************************/
/*!
    @brief   Blit 1 pixel of color without setting up SPI transaction
    @param   color 16-bits of 5-6-5 color data
*/
/**************************************************************************/
void ili9341::writePixel(uint16_t color)
{
	spiWrite16(color);
}


/**************************************************************************/
/*!
   @brief  Draw a single pixel, DOES NOT set up SPI transaction
    @param    x  TFT X location
    @param    y  TFT Y location
    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void ili9341::writePixel(int16_t x, int16_t y, uint16_t color)
{
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) return;
	setAddrWindow(x,y,1,1);
	writePixel(color);
}


/**************************************************************************/
/*!
	@brief  Draw a single pixel, includes code for SPI transaction
	@param    x  TFT X location
	@param    y  TFT Y location
	@param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void ili9341::drawPixel(int16_t x, int16_t y, uint16_t color)
{
	startWrite();
	writePixel(x, y, color);
	endWrite();
}