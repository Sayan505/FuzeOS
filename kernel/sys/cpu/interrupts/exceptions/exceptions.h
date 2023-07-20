# pragma once


#include <lib/stdtypes.h>

#include <sys/cpu/interrupts/interrupt_frame.h>


__attribute__((interrupt)) VOID division_error(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID debug(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID nmi(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID breakpoint(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID overflow(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID bound_range_exceeded(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID invalid_opcode(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID device_not_available(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID double_fault(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID coproc_seg_overrun(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID invalid_tss(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID seg_not_present(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID stack_seg_fault(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID gen_prot_fault(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID page_fault(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID reserved_gate1(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID x87_floating_point_exception(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID alignment_check(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID machine_check(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID simd_floating_point_exception(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID virt_exception(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID control_protection_exception(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID reserved_gate2_1(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID reserved_gate2_2(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID reserved_gate2_3(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID reserved_gate2_4(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID reserved_gate2_5(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID reserved_gate2_6(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID hypervisor_injection_exception(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID vmm_communication_exception(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID security_exception(interrupt_frame_t* interrupt_frame);
__attribute__((interrupt)) VOID reserved_gate3(interrupt_frame_t* interrupt_frame);
