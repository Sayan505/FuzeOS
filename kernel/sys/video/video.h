#pragma once

#include <lib/stdtypes.h>


VOID putpixel_routine(UINT32 x, UINT32 y, UINT32 color);

VOID clr_scr();

VOID fill_scr(UINT32 hex_rgb_color);


#define putpixel(__x__, __y__, __color__)   putpixel_routine(__x__, __y__, __color__)
