#pragma once


// data types
#include <lib/stdtypes.h>

// stdlib
#include <lib/stdlib.h>


// GDT
#include <sys/gdt64/gdt64.h>


// boot protocol
#include <sys/bootprotocol/stiletto.h>


// serial port
#include <lib/serial.h>


// video
#include <sys/video/init.h>     // internal init code
#include <lib/video.h>

static stiletto_t kernel_stiletto = { 0 };


// stdio
#include <lib/stdio.h>


// memory
//#include <sys/mem/mem.h>

// CPU
#include <lib/cpuid.h>


// welcome screen
void welcome_screen();
