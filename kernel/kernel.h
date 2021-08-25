#pragma once


// GDT
extern void LOAD_GDT64();

// data types
#include <lib/stdtypes.h>


// boot protocol
#include <sys/bootprotocol/stiletto.h>


// serial port
#include <lib/serial.h>


// video
#include <sys/video/init.h>
#include <lib/video.h>


// stdout
#include <lib/stdout.h>