#include <sys/cpu/interrupts/idt.h>

#include <sys/cpu/interrupts/exceptions/exceptions.h>

#include <lib/serial.h>


idtr_t idtr;
idt_desc_entry_t idt_desc_entry[256];

extern VOID enable_sce(VOID);   // enable sys call ext


VOID init_interrupts(VOID) {
    idtr.limit = 256 * sizeof(idt_desc_entry_t) - 1;
    idtr.base = (UINT64)&idt_desc_entry;


    rig_idt_gate(0,  KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)division_error);
    rig_idt_gate(1,  KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)debug);
    rig_idt_gate(2,  KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)nmi);
    rig_idt_gate(3,  KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)breakpoint);
    rig_idt_gate(4,  KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)overflow);
    rig_idt_gate(5,  KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)bound_range_exceeded);
    rig_idt_gate(6,  KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)invalid_opcode);
    rig_idt_gate(7,  KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)device_not_available);
    rig_idt_gate(8,  KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)double_fault);
    rig_idt_gate(9,  KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)coproc_seg_overrun);
    rig_idt_gate(10, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)invalid_tss);
    rig_idt_gate(11, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)seg_not_present);
    rig_idt_gate(12, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)stack_seg_fault);
    rig_idt_gate(13, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)gen_prot_fault);
    rig_idt_gate(14, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)page_fault);
    rig_idt_gate(15, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)reserved_gate1);
    rig_idt_gate(16, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)x87_floating_point_exception);
    rig_idt_gate(17, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)alignment_check);
    rig_idt_gate(18, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)machine_check);
    rig_idt_gate(19, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)simd_floating_point_exception);
    rig_idt_gate(20, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)virt_exception);
    rig_idt_gate(21, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)control_protection_exception);
    rig_idt_gate(22, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)reserved_gate2_1);
    rig_idt_gate(23, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)reserved_gate2_2);
    rig_idt_gate(24, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)reserved_gate2_3);
    rig_idt_gate(25, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)reserved_gate2_4);
    rig_idt_gate(26, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)reserved_gate2_5);
    rig_idt_gate(27, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)reserved_gate2_6);
    rig_idt_gate(28, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)hypervisor_injection_exception);
    rig_idt_gate(29, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)vmm_communication_exception);
    rig_idt_gate(30, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)security_exception);
    rig_idt_gate(31, KERNEL_CS, IDT_GATE_TYPE_TRAP, (UINT64)reserved_gate3);



    // load idt reg
    __asm__("lidt %0" : : "m" (idtr));

    __asm__ volatile("sti");

    // enable System Call Extensions
    enable_sce();
}
