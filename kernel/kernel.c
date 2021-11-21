/*
    The Fuze Kernel
*/


#include <kernel.h>

#include <lib/nolibc.h>


__attribute__ ((sysv_abi))
void start_kernel(stiletto_t *stiletto) {
    // back it up
    memcpy(&kernel_stiletto, stiletto, sizeof(stiletto_t));

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
    //init_memory(kernel_stiletto.stiletto_memory);


    // init video
    init_video(kernel_stiletto.stiletto_video);

    clr_scr();  // draw bg


    // READY!
    k_putstr_rgb(
        " ______   _    _   ______  ______  ""  ""  ____    _____ ""\r\n"
        "|  ____| | |  | | |___  / |  ____| ""  "" / __ \\  / ____|""\r\n"
        "| |__    | |  | |    / /  | |__    ""  ""| |  | | | (___  ""\r\n"
        "|  __|   | |  | |   / /   |  __|   ""  ""| |  | |  \\___ \\ ""\r\n"
        "| |      | |__| |  / /__  | |____  ""  ""| |__| |  ____) |""\r\n"
        "|_|       \\____/  /_____| |______|""  ""  \\____/  |_____/ ""\r\n""\r\n",
        0xEE9B00);

    k_putstr_rgb("\r\nFuzeOS ", 0xEE9B00);
    k_putstr_rgb("V0.01-100", 0x0A9396);
    k_putstr_rgb(" (ALPHA)\r\n\r\n", 0x005F73);

    k_putstr_rgb("CPU: ", 0x00B4D8);
    k_putstr_rgb(get_cpu_vendor_string(), 0xE9D8A6);
    k_putstr("\r\n");

    k_putstr_rgb("Memory: ", 0x00B4D8);
    k_putstr_rgb(uint_to_str(kernel_stiletto.stiletto_memory.total_mem_bytes), 0xE9D8A6);
    k_putstr_rgb(" Bytes\r\n", 0xE9D8A6);

    k_putstr_rgb("Terminal: ", 0x00B4D8);
    k_putstr_rgb(uint_to_str(kernel_stiletto.stiletto_video.horiz), 0xE9D8A6);
    k_putstr_rgb(" x ", 0xE9D8A6);
    k_putstr_rgb(uint_to_str(kernel_stiletto.stiletto_video.vert), 0xE9D8A6);
    k_putstr("\r\n");




    __asm__ volatile("cli");
    __asm__ volatile("hlt");   // halt cpu
}


//sudo dd if=OS.img of=/dev/sdc bs=1M count=64 oflag=sync
