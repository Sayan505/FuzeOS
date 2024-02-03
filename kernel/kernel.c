/*
    The Fuze OS Kernel
*/


#include <kernel.h>


VOID start_kernel(stiletto_t *stiletto) {
    // fork it up
    zero_memory(&kernel_stiletto, sizeof(stiletto_t));
    memcpy(&kernel_stiletto, stiletto, sizeof(stiletto_t));

    // init mem
    //mem_info_t mem_info = init_mem(kernel_stiletto.stiletto_memory);


    // init gdt
    init_gdt();


    // init serial
    init_com1();
    com1_outs("Initialized Serial (COM1)\n");


    // init video
    init_video(kernel_stiletto.stiletto_video);

    // init interrupts
    init_interrupts();


    clr_scr();  // draw bg


    // READY!
    k_putstr_rgb(
        "  ______   _    _   ______  ______  ""  ""  ____    _____ ""\r\n"
        "|  ____| | |  | | |___  / |  ____| ""  "" / __ \\  / ____|""\r\n"
        "| |__    | |  | |    / /  | |__    ""  ""| |  | | | (___  ""\r\n"
        "|  __|   | |  | |   / /   |  __|   ""  ""| |  | |  \\___ \\ ""\r\n"
        "| |      | |__| |  / /__  | |____  ""  ""| |__| |  ____) |""\r\n"
        "|_|       \\____/  /_____| |______|""  ""  \\____/  |_____/ ""\r\n""\r\n",
        0xEE9B00);

    k_putstr_rgb("\r\nFuzeOS ", 0xEE9B00);
    k_putstr_rgb("V0.01-100", 0x0A9396);
    k_putstr_rgb(" (ALPHA)\r\n", 0x005F73);
    k_putstr_rgb(get_cpu_vendor_string(), 0xE9D8A6);  // CPUID


    //init_userspace((ADDR)usermode_subroutine, (ADDR)&usermode_stack[1023]);    // stack grows downwards in x86/64

    __asm__ volatile("cli");
    __asm__ volatile("hlt");
}


//sudo dd if=OS.img of=/dev/sdc bs=1M count=64 oflag=sync
