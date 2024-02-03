#pragma once


// data types
#include <lib/stdtypes.h>

// stdlib
#include <lib/stdlib.h>


// boot protocol
#include <boot/protocol/stiletto.h>

static stiletto_t kernel_stiletto;    // kernel's fork of the boot protocol


// GDT
#include <sys/gdt64/gdt64.h>


// serial port
#include <lib/serial.h>


// video
#include <sys/video/init.h>     // internal init code
#include <lib/video.h>


// console/stdio
#include <lib/stdio.h>


// memory
#include <sys/mem/init_mem.h>


// interrupts
#include <sys/cpu/interrupts/init_interrupts.h>

// CPU
#include <lib/cpuid.h>
