/*
    The Fuze Kernel
*/


#include <kernel.h>


__attribute__ ((sysv_abi))
void start_kernel(stiletto_t *stiletto) {
    // init gdt
    LOAD_GDT64();

    // get the segments right
    __asm__ volatile("mov $0x10, %ax");
    
    __asm__ volatile("mov %ax, %ss");
    __asm__ volatile("mov %ax, %ds");
    __asm__ volatile("mov %ax, %es");
    __asm__ volatile("mov %ax, %gs");
    __asm__ volatile("mov %ax, %fs");


    // init serial
    init_com1();

    com1_outs("Initialized Serial (COM1)\n");


    // init video
    init_video(stiletto->stiletto_video);

    // init memory
    init_memory(stiletto->stiletto_memory);


    clr_scr();

    k_putstr("READY!\n\r");




    __asm__ volatile("cli");
    __asm__ volatile("hlt");   // halt cpu
}

//sudo dd if=OS.img of=/dev/sdc bs=1M count=64 oflag=sync
