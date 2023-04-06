#pragma once


#include <lib/stdtypes.h>


// abstractions for COM1

VOID init_com1(VOID);               // init serial with COM1 port

VOID com1_outb(char __datb__);  // emit bytes through COM1
VOID com1_outs(const char* __strb__); // emit string through COM1

BYTE com1_inb(VOID);                // listen for bytes through COM1


// DEBUGGING THRU COM1
VOID com1_addr_of_func(UINT64 func);


#define reset_com1() init_com1()
