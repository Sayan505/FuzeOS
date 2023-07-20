#pragma once


#include <lib/stdtypes.h>


#pragma pack(1)


typedef struct tag_gdt_desc {
    UINT16 limit;
    UINT64 base;
} gdt_desc_t;


typedef struct tag_gdt_entry {
    UINT16 limit_0_15;
    UINT16 base_low_16_31;

    UINT8 base_mid_32_39;
    UINT8 access_byte_40_47;
    UINT8 granularity____limit_48_51__flags_52_55;

    UINT8 base_high_56_63;
} gdt_entry_t;


typedef struct tag_gdt {
    gdt_entry_t null;

    gdt_entry_t kernel_cs;  // 0x08 (kernel base selector)
    gdt_entry_t kernel_ds;  // 0x10

    gdt_entry_t user_null;  // 0x18 (user base selector)
    gdt_entry_t user_ds;    // 0x20
    gdt_entry_t user_cs;    // 0x28

    gdt_entry_t tss_low;    // 0x30
    gdt_entry_t tss_high;   // 0x38
} gdt_t;


#pragma pack()

extern gdt_t gdt;

extern VOID LOAD_GDT64(gdt_desc_t* gdt_desc);

VOID init_gdt(VOID);

// ref: https://wiki.osdev.org/Global_Descriptor_Table
