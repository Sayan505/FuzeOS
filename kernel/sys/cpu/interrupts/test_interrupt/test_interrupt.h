# pragma once


#include <lib/stdtypes.h>

#include <sys/cpu/interrupts/interrupt_frame.h>


__attribute__((interrupt)) VOID test_int(interrupt_frame_t* interrupt_frame);
