#ifndef __gfx_hpp__
#define __gfx_hpp__

#include <cstdint>

class gfx {
	//private:

	public:
		gfx(int16_t w, int16_t h); // Constructor

		// This MUST be defined by the derivitive class:
		virtual void drawPixel(int16_t x, int16_t y, uint16_t color) = 0;
		// tsest virtual void startWrite(void) = 0;
		// virtual void endWrite(void) = 0;
		virtual void startWrite(void);
		virtual void endWrite(void);

		// 
		void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
		void writePixel(int16_t x, int16_t y, uint16_t color);
		void writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

	protected:
		const int16_t WIDTH, HEIGHT;  // This is the 'raw' display w/h - never changes
		int16_t _width, _height; // Display w/h as modified by current rotation
		int16_t cursor_x, cursor_y;
		uint8_t textsize, rotation;
		uint16_t textcolor, textbgcolor;
		bool wrap; // If set, 'wrap' text at right edge of display
		bool _cp437; // If set, use correct CP437 charset (default is off)
		//GFXfont *gfxFont;
};


#endif //__gfx_hpp__