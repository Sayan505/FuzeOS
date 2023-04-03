#include <sys/cpu/interrupts/idt.h>

#include <sys/cpu/interrupts/test_interrupt/test_interrupt.h>


idtr_t idtr;
idt_desc_entry_t idt_desc_entry[256];

VOID init_interrupts(void) {
    idtr.limit = 256 * sizeof(idt_desc_entry_t) - 1;
    idtr.base = (UINT64)&idt_desc_entry;

    
    rig_idt_gate(0x00, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT, (UINT64)test_int);


    // load idt reg
    __asm__("lidt %0" : : "m" (idtr));

    __asm__ volatile("sti");
}
