#include <cstdlib>
#include "gfx.hpp"


#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif


gfx::gfx(int16_t w, int16_t h) : WIDTH(w), HEIGHT(h)
{
	_width    = WIDTH;
	_height   = HEIGHT;
	rotation  = 0;
	cursor_y  = cursor_x    = 0;
	textsize  = 1;
	textcolor = textbgcolor = 0xFFFF;
	wrap      = true;
	_cp437    = false;
	//gfxFont   = NULL;
}


void gfx::startWrite(void)
{

}

void gfx::endWrite(void)
{
	
}

void gfx::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
{
    // Update in subclasses if desired!
    // if(x0 == x1){
    //     if(y0 > y1) _swap_int16_t(y0, y1);
    //     drawFastVLine(x0, y0, y1 - y0 + 1, color);
    // } else if(y0 == y1){
    //     if(x0 > x1) _swap_int16_t(x0, x1);
    //     drawFastHLine(x0, y0, x1 - x0 + 1, color);
    // } else {
		startWrite();
		writeLine(x0, y0, x1, y1, color);
		endWrite();
    // }
}



void gfx::writePixel(int16_t x, int16_t y, uint16_t color)
{
	// Overwrite in subclasses if startWrite is defined!
	drawPixel(x, y, color);
}

// Bresenham's algorithm - thx wikpedia
void gfx::writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
{
	int16_t steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		_swap_int16_t(x0, y0);
		_swap_int16_t(x1, y1);
	}

	if (x0 > x1) {
		_swap_int16_t(x0, x1);
		_swap_int16_t(y0, y1);
	}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1) {
		ystep = 1;
	} else {
		ystep = -1;
	}

	for (; x0<=x1; x0++) {
		if (steep) {
			writePixel(y0, x0, color);
	    } else {
			writePixel(x0, y0, color);
	    }
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
}