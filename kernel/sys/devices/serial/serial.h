#pragma once


#include <lib/stdtypes.h>


// abstractions for COM1

VOID init_com1();               // init serial with COM1 port

VOID com1_outb(char __datb__);  // emit bytes through COM1
VOID com1_outs(char* __strb__); // emit string through COM1

BYTE com1_inb();                // listen for bytes through COM1


#define reset_com1() init_com1()
