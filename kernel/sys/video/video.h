#pragma once

#include <lib/stdtypes.h>


VOID putpixel_routine(UI32 x, UI32 y, UI32 color);

VOID clr_scr();

VOID fill_scr(UI32 hex_rgb_color);


#define putpixel(__x__, __y__, __color__)   putpixel_routine(__x__, __y__, __color__)
