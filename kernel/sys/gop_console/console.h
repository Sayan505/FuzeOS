// font rendering routines

#pragma once


#include <lib/stdtypes.h>


VOID k_putchr(const CHAR  _char);
VOID k_putstr(const CHAR* _str);

VOID k_putchr_rgb(const CHAR  _char, UINT32 _color);
VOID k_putstr_rgb(const CHAR* _str,  UINT32 _color);
