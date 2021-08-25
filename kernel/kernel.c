/*
    The Fuze Kernel
*/


#include <kernel.h>


__attribute__ ((noreturn))
void start_kernel(stiletto_t *stiletto) {
    LOAD_GDT64(&&start);    // supply return address in rdi (https://gcc.gnu.org/onlinedocs/gcc/Labels-as-Values.html)
start:
    // get the segments right
    __asm__ volatile("mov $0x10, %ax");
    
    __asm__ volatile("mov %ax, %ss");
    __asm__ volatile("mov %ax, %ds");
    __asm__ volatile("mov %ax, %es");
    __asm__ volatile("mov %ax, %gs");
    __asm__ volatile("mov %ax, %fs");


    // init serial
    init_com1();

    com1_outs("OK");


    // init video
    init_video(stiletto->stiletto_video);

    clr_scr();

    k_putstr("MEOWWWWM!\n\r");

    __asm__ volatile("cli");
    for(;;) { __asm__ volatile("hlt"); }    // end of kernel
}

//sudo dd if=OS.img of=/dev/sdc bs=1M count=64 oflag=sync
