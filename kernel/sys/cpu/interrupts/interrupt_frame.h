#pragma once


#include <lib/stdtypes.h>


typedef struct tag_interrupt_frame {
    UINT64 rip;
    UINT64 cs;
    UINT64 rflags;
    UINT64 rsp;
    UINT64 ss;
} interrupt_frame_t;
