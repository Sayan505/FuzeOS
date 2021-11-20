/*
    The Fuze Kernel
*/


#include <kernel.h>

#include <lib/nolibc.h>

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


    // init memory
    init_memory(stiletto->stiletto_memory);


    // init video
    init_video(stiletto->stiletto_video);

    clr_scr();  // draw bg


    // READY!
    {
        k_putstr_rgb(
            " ______   _    _   ______  ______  ""  ""  ____    _____ ""\r\n"
            "|  ____| | |  | | |___  / |  ____| ""  "" / __ \\  / ____|""\r\n"
            "| |__    | |  | |    / /  | |__    ""  ""| |  | | | (___  ""\r\n"
            "|  __|   | |  | |   / /   |  __|   ""  ""| |  | |  \\___ \\ ""\r\n"
            "| |      | |__| |  / /__  | |____  ""  ""| |__| |  ____) |""\r\n"
            "|_|       \\____/  /_____| |______|""  ""  \\____/  |_____/ ""\r\n""\r\n",
            0xEE9B00);

        k_putstr_rgb("FuzeOS ", 0xEE9B00);
        k_putstr_rgb("V0.01-100", 0x0A9396);
        k_putstr_rgb(" (ALPHA)\r\n", 0x005F73);

        k_putstr_rgb("CPU: ", 0x00B4D8);
        k_putstr_rgb(get_cpu_vendor_string(), 0xccff33);
    }



    __asm__ volatile("cli");
    __asm__ volatile("hlt");   // halt cpu
}


//sudo dd if=OS.img of=/dev/sdc bs=1M count=64 oflag=sync
