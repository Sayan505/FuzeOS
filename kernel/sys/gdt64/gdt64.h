#pragma once


#include <lib/stdtypes.h>


#pragma pack(1)


typedef struct tag_gdt_desc {
    UINT16 limit;
    UINT64 base;
} gdt_desc_t;


typedef struct tag_gdt_entry {
    UINT16 limit_low_15_0;
    UINT16 base_low_15_0;

    UINT8 base_mid_23_16;
    UINT8 access_byte;
    UINT8 granularity;

    UINT8 base_high_31_24;
} gdt_entry_t;


typedef struct tag_gdt {
    gdt_entry_t null;

    gdt_entry_t kernel_cs;
    gdt_entry_t kernel_ds;
} gdt_t;


#pragma pack()


void set_segments(UINT16 cs, UINT16 ds);

void init_gdt();
