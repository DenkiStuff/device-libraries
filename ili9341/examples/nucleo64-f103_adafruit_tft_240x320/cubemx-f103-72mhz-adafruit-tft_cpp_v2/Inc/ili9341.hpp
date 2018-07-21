#ifndef __ili9341_h__
#define __ili9341_h__

#include "gfx.hpp"


#define ILI9341_WIDTH   240       ///< ILI9341 max TFT width
#define ILI9341_HEIGHT  320       ///< ILI9341 max TFT height


#define ILI9341_NOP        0x00      ///< No-op register
#define ILI9341_SWRESET    0x01      ///< Software reset register
#define ILI9341_RDDID      0x04      ///< Read display identification information
#define ILI9341_RDDST      0x09      ///< Read Display Status 

#define ILI9341_SLPIN      0x10      ///< Enter Sleep Mode
#define ILI9341_SLPOUT     0x11      ///< Sleep Out
#define ILI9341_PTLON      0x12      ///< Partial Mode ON
#define ILI9341_NORON      0x13      ///< Normal Display Mode ON

#define ILI9341_RDMODE     0x0A      ///< Read Display Power Mode 
#define ILI9341_RDMADCTL   0x0B      ///< Read Display MADCTL
#define ILI9341_RDPIXFMT   0x0C      ///< Read Display Pixel Format
#define ILI9341_RDIMGFMT   0x0D      ///< Read Display Image Format 
#define ILI9341_RDSELFDIAG 0x0F      ///< Read Display Self-Diagnostic Result

#define ILI9341_INVOFF     0x20      ///< Display Inversion OFF
#define ILI9341_INVON      0x21      ///< Display Inversion ON 
#define ILI9341_GAMMASET   0x26      ///< Gamma Set 
#define ILI9341_DISPOFF    0x28      ///< Display OFF 
#define ILI9341_DISPON     0x29      ///< Display ON

#define ILI9341_CASET      0x2A      ///< Column Address Set 
#define ILI9341_PASET      0x2B      ///< Page Address Set
#define ILI9341_RAMWR      0x2C      ///< Memory Write
#define ILI9341_RAMRD      0x2E      ///< Memory Read

#define ILI9341_PTLAR      0x30      ///< Partial Area
#define ILI9341_MADCTL     0x36      ///< Memory Access Control
#define ILI9341_VSCRSADD   0x37      ///< Vertical Scrolling Start Address
#define ILI9341_PIXFMT     0x3A      ///< COLMOD: Pixel Format Set

#define ILI9341_FRMCTR1    0xB1      ///< Frame Rate Control (In Normal Mode/Full Colors)
#define ILI9341_FRMCTR2    0xB2      ///< Frame Rate Control (In Idle Mode/8 colors)
#define ILI9341_FRMCTR3    0xB3      ///< Frame Rate control (In Partial Mode/Full Colors)
#define ILI9341_INVCTR     0xB4      ///< Display Inversion Control
#define ILI9341_DFUNCTR    0xB6      ///< Display Function Control

#define ILI9341_PWCTR1     0xC0      ///< Power Control 1
#define ILI9341_PWCTR2     0xC1      ///< Power Control 2
#define ILI9341_PWCTR3     0xC2      ///< Power Control 3
#define ILI9341_PWCTR4     0xC3      ///< Power Control 4
#define ILI9341_PWCTR5     0xC4      ///< Power Control 5
#define ILI9341_VMCTR1     0xC5      ///< VCOM Control 1
#define ILI9341_VMCTR2     0xC7      ///< VCOM Control 2

#define ILI9341_RDID1      0xDA      ///< Read ID 1
#define ILI9341_RDID2      0xDB      ///< Read ID 2
#define ILI9341_RDID3      0xDC      ///< Read ID 3
#define ILI9341_RDID4      0xDD      ///< Read ID 4

#define ILI9341_GMCTRP1    0xE0      ///< Positive Gamma Correction
#define ILI9341_GMCTRN1    0xE1      ///< Negative Gamma Correction
//#define ILI9341_PWCTR6     0xFC


// Color definitions
#define ILI9341_BLACK       0x0000      ///<   0,   0,   0
#define ILI9341_NAVY        0x000F      ///<   0,   0, 128
#define ILI9341_DARKGREEN   0x03E0      ///<   0, 128,   0
#define ILI9341_DARKCYAN    0x03EF      ///<   0, 128, 128
#define ILI9341_MAROON      0x7800      ///< 128,   0,   0
#define ILI9341_PURPLE      0x780F      ///< 128,   0, 128
#define ILI9341_OLIVE       0x7BE0      ///< 128, 128,   0
#define ILI9341_LIGHTGREY   0xC618      ///< 192, 192, 192
#define ILI9341_DARKGREY    0x7BEF      ///< 128, 128, 128
#define ILI9341_BLUE        0x001F      ///<   0,   0, 255
#define ILI9341_GREEN       0x07E0      ///<   0, 255,   0
#define ILI9341_CYAN        0x07FF      ///<   0, 255, 255
#define ILI9341_RED         0xF800      ///< 255,   0,   0
#define ILI9341_MAGENTA     0xF81F      ///< 255,   0, 255
#define ILI9341_YELLOW      0xFFE0      ///< 255, 255,   0
#define ILI9341_WHITE       0xFFFF      ///< 255, 255, 255
#define ILI9341_ORANGE      0xFD20      ///< 255, 165,   0
#define ILI9341_GREENYELLOW 0xAFE5      ///< 173, 255,  47
#define ILI9341_PINK        0xFC18      ///< 255, 128, 192


/// Class to manage hardware interface with ILI9341 chipset (also seems to work with ILI9340)
class ili9341 : public gfx {
	protected:

	public:
		ili9341();

		// Required Non-Transaction
		void drawPixel(int16_t x, int16_t y, uint16_t color);


		// Transaction API
		void startWrite(void);
		void endWrite(void);
		void writeCommand(uint8_t cmd);
		void spiWrite(uint8_t b);

		// Transaction API not used by GFX
		void writePixel(uint16_t color);
		void setAddrWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
};

#endif //__ili9341_h__
