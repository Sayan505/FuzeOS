#include <sys/cpu/interrupts/idt.h>


VOID rig_idt_gate(BYTE number, BYTE seg_sel, BYTE type_attrib, UINT64 handler_offset) {
    idt_desc_entry[number].isr_low = (UINT16)(handler_offset & 0x000000000000ffff);
    idt_desc_entry[number].seg_sel = seg_sel;
    idt_desc_entry[number].ist = 0;
    idt_desc_entry[number].type_attrib = type_attrib;
    idt_desc_entry[number].isr_mid = (UINT16)((handler_offset & 0x00000000ffff0000) >> 16);
    idt_desc_entry[number].isr_high = (UINT32)((handler_offset & 0xffffffff00000000) >> 32);
    idt_desc_entry[number].reserved = 0;
}

// test_int = 0x000000000063347D
