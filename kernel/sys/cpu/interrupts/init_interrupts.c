#include <sys/cpu/interrupts/idt.h>

#include <sys/cpu/interrupts/test_interrupt/test_interrupt.h>

#include <lib/serial.h>


idtr_t idtr;
idt_desc_entry_t idt_desc_entry[256];

VOID init_interrupts(VOID) {
    idtr.limit = 256 * sizeof(idt_desc_entry_t) - 1;
    idtr.base = (UINT64)&idt_desc_entry;


    rig_idt_gate(0,  KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(2,  KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(1,  KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(3,  KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(4,  KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(5,  KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(6,  KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(7,  KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(8,  KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(9,  KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(10, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(11, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(12, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(13, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(14, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(15, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(16, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(17, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(18, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(19, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(20, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(21, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(22, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(23, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(24, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(25, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(26, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(27, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(28, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(29, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(30, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);
    rig_idt_gate(31, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)test_int);

    rig_idt_gate(32, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT, (UINT64)test_int);
    rig_idt_gate(33, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT, (UINT64)test_int);
    rig_idt_gate(34, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT, (UINT64)test_int);
    rig_idt_gate(35, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT, (UINT64)test_int);
    rig_idt_gate(36, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT, (UINT64)test_int);
    rig_idt_gate(37, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT, (UINT64)test_int);
    rig_idt_gate(38, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT, (UINT64)test_int);
    rig_idt_gate(39, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT, (UINT64)test_int);
    rig_idt_gate(40, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT, (UINT64)test_int);
    rig_idt_gate(41, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT, (UINT64)test_int);
    rig_idt_gate(42, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT, (UINT64)test_int);
    rig_idt_gate(43, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT, (UINT64)test_int);
    rig_idt_gate(44, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT, (UINT64)test_int);
    rig_idt_gate(45, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT, (UINT64)test_int);
    rig_idt_gate(46, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT, (UINT64)test_int);
    rig_idt_gate(47, KERNEL_CS, IDT_GATE_TYPE_INTERRUPT, (UINT64)test_int);



    // load idt reg
    __asm__("lidt %0" : : "m" (idtr));

    __asm__ volatile("sti");
}
