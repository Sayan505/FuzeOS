# pragma once


#include <lib/stdtypes.h>


typedef struct tag_idt_desc_entry {
    UINT16 isr_low;     // lower 16 bits of the ISR's addr

    UINT16 seg_sel;     // cs selector
    UINT8 ist;          // interrupt stack table offset
    UINT8 type_attrib;  // gate type attrib.: Interrupt, Trap
    
    UINT16 isr_mid;     // higher 16 bits of the lower 32 bits of the ISR's addr

    UINT32 isr_high;    // higher 32 bits of the ISR's addr

    UINT32 reserved;
} __attribute__((packed)) idt_desc_entry_t;


typedef struct tag_idtr {
    UINT16 limit;   // size
    UINT64 base;    // address/offset
} __attribute__((packed)) idtr_t;

extern idtr_t idtr;
extern idt_desc_entry_t idt_desc_entry[256];


// Interrupt Gate: 0x8E (p=1, dpl=0b00, type=0b1110 => type_attributes=0b1000_1110=0x8E) (type_attrib)
#define IDT_GATE_TYPE_INTERRUPT (BYTE)0x8E

// Trap Gate: 0x8F (p=1, dpl=0b00, type=0b1111 => type_attributes=1000_1111b=0x8F) (type_attrib)
#define IDT_GATE_TYPE_TRAP      (BYTE)0x8F


// seg_sel:
#define KERNEL_CS (BYTE)0x08
#define USER_CS   (BYTE)0x20


VOID rig_idt_gate(BYTE number, BYTE seg_sel, BYTE type_attrib, UINT64 handler_offset);


// ref: https://wiki.osdev.org/IDT
