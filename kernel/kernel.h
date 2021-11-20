#pragma once


// GDT
extern void LOAD_GDT64();   // kernel/sys/gdt/gdt64.asm

// data types
#include <lib/stdtypes.h>


// boot protocol
#include <sys/bootprotocol/stiletto.h>


// serial port
#include <lib/serial.h>


// video
#include <sys/video/init.h>     // internal init code
#include <lib/video.h>


// stdout
#include <lib/stdout.h>


// memory
#include <sys/mem/mem.h>

// CPU
#include <lib/cpuid.h>


// welcome screen
void welcome_screen();
