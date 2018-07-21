#include "ili9341.hpp"
#include "ili9341_ll.hpp"


ili9341::ili9341() : gfx(ILI9341_WIDTH, ILI9341_HEIGHT) {;}



void ili9341::init()
{

	// Control Pins
	// pinMode(_dc, OUTPUT);
	// digitalWrite(_dc, LOW);
	setCommandMode();

	// pinMode(_cs, OUTPUT);
	// digitalWrite(_cs, HIGH);
	endWrite();

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
	// SPI_WRITE32(xa);
		// if(_sclk < 0){
		// 	{
		// 		(*(volatile uint8_t *)((0x2E) + 0x20)) = ((xa) >> 24);
		// 		while(!((*(volatile uint8_t *)((0x2D) + 0x20)) & (1 << (7))));
		// 	};
		// 	{
		// 		(*(volatile uint8_t *)((0x2E) + 0x20)) = ((xa) >> 16);
		// 		while(!((*(volatile uint8_t *)((0x2D) + 0x20)) & (1 << (7))));
		// 	};
		// 	{
		// 		(*(volatile uint8_t *)((0x2E) + 0x20)) = ((xa) >> 8);
		// 		while(!((*(volatile uint8_t *)((0x2D) + 0x20)) & (1 << (7))));
		// 	};
		// 	{
		// 		(*(volatile uint8_t *)((0x2E) + 0x20)) = (xa);
		// 		while(!((*(volatile uint8_t *)((0x2D) + 0x20)) & (1 << (7))));
		// 	};
		// } else {
		// 	spiWrite((xa) >> 24);
		// 	spiWrite((xa) >> 16);
		// 	spiWrite((xa) >> 8); 
		// 	spiWrite(xa);
		// };
	spiWrite32(xa);
	
	writeCommand(ILI9341_PASET); // Row addr set
	
	//SPI_WRITE32(ya);
	spiWrite32(ya);

	writeCommand(ILI9341_RAMWR); // write to RAM
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

/**************************************************************************/
/*!
   @brief  Draw a single pixel, DOES NOT set up SPI transaction
    @param    x  TFT X location
    @param    y  TFT Y location
    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void ili9341::writePixel(int16_t x, int16_t y, uint16_t color) {
    if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) return;
    setAddrWindow(x,y,1,1);
    writePixel(color);
}


/**************************************************************************/
/*!
    @brief   Blit 1 pixel of color without setting up SPI transaction
    @param   color 16-bits of 5-6-5 color data
*/
/**************************************************************************/
void ili9341::writePixel(uint16_t color)
{
	// SPI_WRITE16(color);
	// if(_sclk < 0){
	// 	{
	// 		(*(volatile uint8_t *)((0x2E) + 0x20)) = ((color) >> 8);
	// 		while(!((*(volatile uint8_t *)((0x2D) + 0x20)) & (1 << (7))));
	// 	}; 
	// 	{
	// 		(*(volatile uint8_t *)((0x2E) + 0x20)) = (color); 
	// 		while(!((*(volatile uint8_t *)((0x2D) + 0x20)) & (1 << (7))));
	// 	};
	// } else {
	// 	spiWrite((color) >> 8); 
	// 	spiWrite(color);
	// };
	spiWrite16(color); 
}


/**************************************************************************/
/*!
   @brief  Write 8-bit data to command/register (DataCommand line low).
   Does not set up SPI transaction.
   @param  cmd The command/register to transmit
*/
/**************************************************************************/
void ili9341::writeCommand(uint8_t cmd)
{
    // *dcport &= ~dcpinmask; // SPI_DC_LOW();
    setCommandMode();

    spiWrite(cmd);

    // *dcport |= dcpinmask; //SPI_DC_HIGH();
   setDataMode();
}





/**************************************************************************/
/*!
   @brief  Begin SPI transaction
*/
/**************************************************************************/
void ili9341::startWrite(void)
{
	//SPI_BEGIN_TRANSACTION(); //if(_sclk < 0){SPI.beginTransaction(SPISettings(_freq, 1, 0x00));};

	//SPI_CS_LOW(); //*csport &= ~cspinmask;
	ili9341_ll_spi_select();
}


/**************************************************************************/
/*!
   @brief  End SPI transaction
*/
/**************************************************************************/
void ili9341::endWrite(void)
{
	//SPI_CS_HIGH();  //*csport |= cspinmask;
	ili9341_ll_spi_deselect();

    //SPI_END_TRANSACTION();	//if(_sclk < 0){SPI.endTransaction();};
}





/**************************************************************************/
/*!
   @brief  Write 8-bit data via hardware. Does not set up SPI transaction.
   @param  b Byte of data to write over SPI
*/
/**************************************************************************/
void ili9341::spiWrite(uint8_t b)
{
    // if(_sclk < 0){
    //     HSPI_WRITE(b);
    //     return;
    // }
    // for(uint8_t bit = 0x80; bit; bit >>= 1){
    //     if((b) & bit){
    //         SSPI_MOSI_HIGH();
    //     } else {
    //         SSPI_MOSI_LOW();
    //     }
    //     SSPI_SCK_LOW();
    //     SSPI_SCK_HIGH();
    // }
    ili9341_ll_spiWrite(b);
}

/**************************************************************************/
/*!
   @brief  Write 16-bit data via hardware SPI. Does not set up SPI transaction.
   @param  b Byte of data to write over SPI
*/
/**************************************************************************/
void ili9341::spiWrite16(uint16_t b)
{
    ili9341_ll_spiWrite16(b);
}


/**************************************************************************/
/*!
   @brief  Write 16-bit data via hardware SPI. Does not set up SPI transaction.
   @param  b Byte of data to write over SPI
*/
/**************************************************************************/
void ili9341::spiWrite32(uint32_t b)
{
    ili9341_ll_spiWrite32(b);
}


/**************************************************************************/
/*!
   @brief  set ili9341 data mode
*/
/**************************************************************************/
void ili9341::setCommandMode(void)
{
	ili9341_ll_set_command_mode();
}


/**************************************************************************/
/*!
   @brief  set ili9341 data mode
*/
/**************************************************************************/
void ili9341::setDataMode(void)
{
	ili9341_ll_set_data_mode();
}