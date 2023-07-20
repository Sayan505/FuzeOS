#pragma once

#include <lib/stdtypes.h>


__attribute__((no_caller_saved_registers)) VOID putpixel_routine(UINT32 x, UINT32 y, UINT32 color);

__attribute__((no_caller_saved_registers)) VOID clr_scr(VOID);

__attribute__((no_caller_saved_registers)) VOID fill_scr(UINT32 hex_rgb_color);


#define putpixel(__x__, __y__, __color__)   putpixel_routine(__x__, __y__, __color__)
