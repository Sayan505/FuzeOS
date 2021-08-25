// font rendering routines

#pragma once


#include <lib/stdtypes.h>


void k_putchr(const CHAR  _char);
void k_putstr(const CHAR* _str);

void k_putchr_rgb(const CHAR  _char, UI32 _color);
void k_putstr_rgb(const CHAR* _str,  UI32 _color);
