# pragma once


#include <lib/stdtypes.h>

typedef struct tag_idt_desc_entry {
    UINT16 isr_low;     // lower 16 bits of the ISR's addr

    UINT16 seg_sel;     // cs selector
    UINT8 ist;          // interrupt stack table
    UINT8 type;         // gate type attrib.: Interrupt, Trap, Task
    
    UINT16 isr_mid;     // higher 16 bits of the lower 32 bits of the ISR's addr

    UINT32 isr_high;    // higher 32 bits of the ISR's addr

    UINT32 reserved;
} __attribute__((packed)) idt_desc_entry;

typedef struct tag_idtr {
    UINT16 limit;
    UINT64 offset; // base
} __attribute__((packed)) idtr;


// ref: https://wiki.osdev.org/IDT
// ref: https://wiki.osdev.org/Interrupt_Descriptor_Table
