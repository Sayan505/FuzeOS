#pragma once


#include <lib/stdtypes.h>


#pragma pack(1)


typedef struct tag_gdt_desc {
    UINT16 limit;
    UINT64 base;
} gdt_desc_t;


typedef struct tag_gdt_entry {
    UINT16 limit15_0;
    UINT16 base15_0;

    UINT8 base23_16;
    UINT8 access_byte;
    UINT8 limit19_16_and_flags;

    UINT8 base31_24;
} gdt_entry_t;


__attribute__((aligned(0x1000)))
typedef struct tag_gdt {
    gdt_entry_t null;

    gdt_entry_t kernel_cs;
    gdt_entry_t kernel_ds;

    gdt_entry_t user_null;
    gdt_entry_t user_cs;
    gdt_entry_t user_ds;

    gdt_entry_t fw_cs;
    gdt_entry_t fw_ds;

    gdt_entry_t tss_low;
    gdt_entry_t tss_high;
} gdt_t;


#pragma pack()


extern void LOAD_GDT64(gdt_desc_t* gdt_desc);   // kernel/sys/gdt64/lgdt64.asm

void init_gdt();
