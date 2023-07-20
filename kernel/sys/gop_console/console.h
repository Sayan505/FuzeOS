// font rendering routines

#pragma once


#include <lib/stdtypes.h>


__attribute__((no_caller_saved_registers)) VOID k_putchr(const CHAR  _char);
__attribute__((no_caller_saved_registers)) VOID k_putstr(const CHAR* _str);

__attribute__((no_caller_saved_registers)) VOID k_putchr_rgb(const CHAR  _char, UINT32 _color);
__attribute__((no_caller_saved_registers)) VOID k_putstr_rgb(const CHAR* _str,  UINT32 _color);
