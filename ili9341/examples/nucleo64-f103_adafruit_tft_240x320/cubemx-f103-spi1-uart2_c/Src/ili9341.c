#include "ili9341.h"
#include "ili9341_ll.h"


#define MADCTL_MY  0x80     ///< Bottom to top
#define MADCTL_MX  0x40     ///< Right to left
#define MADCTL_MV  0x20     ///< Reverse Mode
#define MADCTL_ML  0x10     ///< LCD refresh Bottom to top
#define MADCTL_RGB 0x00     ///< Red-Green-Blue pixel order
#define MADCTL_BGR 0x08     ///< Blue-Green-Red pixel order
#define MADCTL_MH  0x04     ///< LCD refresh right to left

uint16_t ili9341_width  = 0x0000;
uint16_t ili9341_height = 0x0000;

void ili9341_startWrite(void)
{
	//SPI_BEGIN_TRANSACTION();

	//SPI_CS_LOW();
	ili9341_ll_spi_select();
}

void ili9341_endWrite(void)
{
	//SPI_BEGIN_TRANSACTION();

	//SPI_CS_LOW();
	ili9341_ll_spi_deselect();
}

void ili9341_writeCommand(uint8_t cmd){
	// SPI_DC_LOW();
	ili9341_ll_set_command_mode();

	// spiWrite(cmd);
	ili9341_ll_spiWrite(cmd);

	// SPI_DC_HIGH();
	ili9341_ll_set_data_mode();
}


void ili9341_begin()
{
	// Control Pins
    //digitalWrite(_dc, LOW);
	ili9341_ll_set_command_mode();
    //digitalWrite(_cs, HIGH);
    ili9341_ll_spi_deselect();

    //startWrite();
    ili9341_startWrite();

	ili9341_writeCommand(0xEF);
	ili9341_ll_spiWrite(0x03);
	ili9341_ll_spiWrite(0x80);
	ili9341_ll_spiWrite(0x02);

	ili9341_writeCommand(0xCF);
	ili9341_ll_spiWrite(0x00);
	ili9341_ll_spiWrite(0XC1);
	ili9341_ll_spiWrite(0X30);

	ili9341_writeCommand(0xED);
	ili9341_ll_spiWrite(0x64);
	ili9341_ll_spiWrite(0x03);
	ili9341_ll_spiWrite(0X12);
	ili9341_ll_spiWrite(0X81);

	ili9341_writeCommand(0xE8);
	ili9341_ll_spiWrite(0x85);
	ili9341_ll_spiWrite(0x00);
	ili9341_ll_spiWrite(0x78);

	ili9341_writeCommand(0xCB);
	ili9341_ll_spiWrite(0x39);
	ili9341_ll_spiWrite(0x2C);
	ili9341_ll_spiWrite(0x00);
	ili9341_ll_spiWrite(0x34);
	ili9341_ll_spiWrite(0x02);

	ili9341_writeCommand(0xF7);
	ili9341_ll_spiWrite(0x20);

	ili9341_writeCommand(0xEA);
	ili9341_ll_spiWrite(0x00);
	ili9341_ll_spiWrite(0x00);

	ili9341_writeCommand(ILI9341_PWCTR1);    //Power control
	ili9341_ll_spiWrite(0x23);   //VRH[5:0]

	ili9341_writeCommand(ILI9341_PWCTR2);    //Power control
	ili9341_ll_spiWrite(0x10);   //SAP[2:0];BT[3:0]

	ili9341_writeCommand(ILI9341_VMCTR1);    //VCM control
	ili9341_ll_spiWrite(0x3e);
	ili9341_ll_spiWrite(0x28);

	ili9341_writeCommand(ILI9341_VMCTR2);    //VCM control2
	ili9341_ll_spiWrite(0x86);  //--

	ili9341_writeCommand(ILI9341_MADCTL);    // Memory Access Control
	ili9341_ll_spiWrite(0x48);

	ili9341_writeCommand(ILI9341_VSCRSADD); // Vertical scroll
	ili9341_ll_spiWrite16(0);                 // Zero

	ili9341_writeCommand(ILI9341_PIXFMT);
	ili9341_ll_spiWrite(0x55);

	ili9341_writeCommand(ILI9341_FRMCTR1);
	ili9341_ll_spiWrite(0x00);
	ili9341_ll_spiWrite(0x18);

	ili9341_writeCommand(ILI9341_DFUNCTR);    // Display Function Control
	ili9341_ll_spiWrite(0x08);
	ili9341_ll_spiWrite(0x82);
	ili9341_ll_spiWrite(0x27);

	ili9341_writeCommand(0xF2);    // 3Gamma Function Disable
	ili9341_ll_spiWrite(0x00);

	ili9341_writeCommand(ILI9341_GAMMASET);    //Gamma curve selected
	ili9341_ll_spiWrite(0x01);

	ili9341_writeCommand(ILI9341_GMCTRP1);    //Set Gamma
	ili9341_ll_spiWrite(0x0F);
	ili9341_ll_spiWrite(0x31);
	ili9341_ll_spiWrite(0x2B);
	ili9341_ll_spiWrite(0x0C);
	ili9341_ll_spiWrite(0x0E);
	ili9341_ll_spiWrite(0x08);
	ili9341_ll_spiWrite(0x4E);
	ili9341_ll_spiWrite(0xF1);
	ili9341_ll_spiWrite(0x37);
	ili9341_ll_spiWrite(0x07);
	ili9341_ll_spiWrite(0x10);
	ili9341_ll_spiWrite(0x03);
	ili9341_ll_spiWrite(0x0E);
	ili9341_ll_spiWrite(0x09);
	ili9341_ll_spiWrite(0x00);

	ili9341_writeCommand(ILI9341_GMCTRN1);    //Set Gamma
	ili9341_ll_spiWrite(0x00);
	ili9341_ll_spiWrite(0x0E);
	ili9341_ll_spiWrite(0x14);
	ili9341_ll_spiWrite(0x03);
	ili9341_ll_spiWrite(0x11);
	ili9341_ll_spiWrite(0x07);
	ili9341_ll_spiWrite(0x31);
	ili9341_ll_spiWrite(0xC1);
	ili9341_ll_spiWrite(0x48);
	ili9341_ll_spiWrite(0x08);
	ili9341_ll_spiWrite(0x0F);
	ili9341_ll_spiWrite(0x0C);
	ili9341_ll_spiWrite(0x31);
	ili9341_ll_spiWrite(0x36);
	ili9341_ll_spiWrite(0x0F);

	ili9341_writeCommand(ILI9341_SLPOUT);    //Exit Sleep
	HAL_Delay(120);
	ili9341_writeCommand(ILI9341_DISPON);    //Display on
	HAL_Delay(120);
	ili9341_endWrite();

	ili9341_width  = ILI9341_TFTWIDTH;
	ili9341_height = ILI9341_TFTHEIGHT;
}


void ili9341_setRotation(uint8_t m)
{
	uint8_t rotation = m % 4; // can't be higher than 3
	switch (rotation) {
	case 0:
		m = (MADCTL_MX | MADCTL_BGR);
		ili9341_width  = ILI9341_TFTWIDTH;
		ili9341_height = ILI9341_TFTHEIGHT;
		break;
	case 1:
		m = (MADCTL_MV | MADCTL_BGR);
		ili9341_width  = ILI9341_TFTHEIGHT;
		ili9341_height = ILI9341_TFTWIDTH;
		break;
	case 2:
		m = (MADCTL_MY | MADCTL_BGR);
		ili9341_width  = ILI9341_TFTWIDTH;
		ili9341_height = ILI9341_TFTHEIGHT;
		break;
	case 3:
		m = (MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
		ili9341_width  = ILI9341_TFTHEIGHT;
		ili9341_height = ILI9341_TFTWIDTH;
		break;
    }

    ili9341_startWrite();
    ili9341_writeCommand(ILI9341_MADCTL);
    ili9341_ll_spiWrite(m);
    ili9341_endWrite();
}


/**************************************************************************
 *
 *  Set the "address window" - the rectangle we will write to RAM with the next chunk of SPI data writes. The ILI9341 will automatically wrap the data as each row is filled
 *  param   x  TFT memory 'x' origin
 *  param   y  TFT memory 'y' origin
 *  param   w  Width of rectangle
 *  param   h  Height of rectangle
 *
 **************************************************************************/
void ili9341_setAddrWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	uint32_t xa = ((uint32_t)x << 16) | (x+w-1);
	uint32_t ya = ((uint32_t)y << 16) | (y+h-1);
	ili9341_writeCommand(ILI9341_CASET); // Column addr set
	ili9341_ll_spiWrite32(xa);
	ili9341_writeCommand(ILI9341_PASET); // Row addr set
	ili9341_ll_spiWrite32(ya);
	ili9341_writeCommand(ILI9341_RAMWR); // write to RAM
}


/**************************************************************************
 *
 *  send 1 pixel of color
 *  param   color 16-bits of 5-6-5 color data
 *
 **************************************************************************/
void ili9341_writePixel(uint16_t color)
{
    ili9341_ll_spiWrite16(color);
}


/**************************************************************************
 *
 *  send 'len' pixels of a single color without setting up SPI transaction
 *  param   color 16-bits of 5-6-5 color data
 *  param   len Number of 16-bit pixels you want to write out with same color
 *
 **************************************************************************/
void ili9341_writeColor(uint16_t color, uint32_t len)
{
	uint8_t hi = color >> 8, lo = color;
	for (uint32_t t=len; t; t--){
		ili9341_ll_spiWrite(hi);
		ili9341_ll_spiWrite(lo);
	}
}


/**************************************************************************
 *
 *  Fill a rectangle, DOES NOT set up SPI transaction
 *  param    x  TFT X location begin
 *  param    y  TFT Y location begin
 *  param    w  Width of rectangle
 *  param    h  Height of rectangle
 *  param    color 16-bit 5-6-5 Color to fill with
 *
 **************************************************************************/
void ili9341_writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
	if((x >= ili9341_width) || (y >= ili9341_height)) return;
	int16_t x2 = x + w - 1, y2 = y + h - 1;
	if((x2 < 0) || (y2 < 0)) return;

	// Clip left/top
	if(x < 0) {
	x = 0;
	w = x2 + 1;
	}
	if(y < 0) {
		y = 0;
		h = y2 + 1;
	}

	// Clip right/bottom
	if(x2 >= ili9341_width)  w = ili9341_width  - x;
	if(y2 >= ili9341_height) h = ili9341_height - y;

	int32_t len = (int32_t)w * h;
	ili9341_setAddrWindow(x, y, w, h);
	ili9341_writeColor(color, len);
}


/**************************************************************************
 *
 *  Fill a rectangle
 *  param    x  TFT X location begin
 *  param    y  TFT Y location begin
 *  param    w  Width of rectangle
 *  param    h  Height of rectangle
 *  param    color 16-bit 5-6-5 Color to fill with
 *
 ***************************************************************************/
void ili9341_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
	ili9341_startWrite();
	ili9341_writeFillRect(x,y,w,h,color);
	ili9341_endWrite();
}


