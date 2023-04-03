#include <sys/cpu/interrupts/test_interrupt/test_interrupt.h>

#include <lib/stdio.h>


__attribute__((interrupt)) VOID test_int(interrupt_frame_t* interrupt_frame) {
    __asm__("movq    $1,%rax"); // TODO: interrupt doesn't fire. (rax is not 1)
    __asm__("cli");
    __asm__("hlt");
    
meow:
    goto meow;
}
