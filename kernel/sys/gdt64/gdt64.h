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

    gdt_entry_t kernel_cs;  // 0x08 (kernel base selector)
    gdt_entry_t kernel_ds;  // 0x10

    gdt_entry_t user_null;  // user base selector

    gdt_entry_t user_cs;    // 0x20
    gdt_entry_t user_ds;    // 0x28

    gdt_entry_t ovmf_ds;    // 0x30
    gdt_entry_t ovmf_cs;    // 0x38

    gdt_entry_t tss_low;    // 0x40
    gdt_entry_t tss_high;   // 0x48
} gdt_t;


#pragma pack()

extern gdt_t gdt;

extern void LOAD_GDT64(gdt_desc_t* gdt_desc);

void init_gdt();

// ref: https://wiki.osdev.org/Global_Descriptor_Table
