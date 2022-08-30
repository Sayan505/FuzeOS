#pragma once


#include <lib/stdtypes.h>


#pragma pack(1)


// ref: Figure 7-11. 64-Bit TSS Format
typedef struct tag_tss {
    UINT32 reserved0;

    UINT32 rsp0_low;
    UINT32 rsp0_high;

    UINT32 rsp1_low;
    UINT32 rsp1_high;

    UINT32 rsp2_low;
    UINT32 rsp2_high;

    UINT32 reserved1_low;
    UINT32 reserved1_high;

    UINT32 ist1_low;
    UINT32 ist1_high;

    UINT32 ist2_low;
    UINT32 ist2_high;

    UINT32 ist3_low;
    UINT32 ist3_high;

    UINT32 ist4_low;
    UINT32 ist4_high;

    UINT32 ist5_low;
    UINT32 ist5_high;

    UINT32 ist6_low;
    UINT32 ist6_high;

    UINT32 ist7_low;
    UINT32 ist7_high;

    UINT32 reserved2;

    UINT32 reserved3;

    UINT16 reserved4;
    UINT16 iopb_offset;
} tss_t;


#pragma pack()
