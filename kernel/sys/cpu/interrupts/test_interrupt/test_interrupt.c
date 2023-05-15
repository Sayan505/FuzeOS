#include <sys/cpu/interrupts/test_interrupt/test_interrupt.h>

#include <lib/stdio.h>


__attribute__((interrupt)) VOID test_int(interrupt_frame_t* interrupt_frame) {
    __asm__("movq    $0xB16B00B5,%rax");
}
