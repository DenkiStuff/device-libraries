#include "gfx.hpp"

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

