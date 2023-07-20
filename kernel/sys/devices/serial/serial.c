#include <sys/devices/serial/serial_internal.h>
#include <sys/devices/serial/serial.h>


VOID set_baud(UINT16 port, BYTE baud_rate) {
    outb(port + 0, baud_rate);
    outb(port + 1, 0x00);
}


VOID init_serial(UINT16 port) {
    outb(port + 1, 0x00);
    outb(port + 3, 0x80);

    set_baud(port, BAUD_115200);    // set baud rate to 115200

    outb(port + 3, 0x03);
    outb(port + 2, 0xC7);
    outb(port + 4, 0x0B);
}

__attribute__((no_caller_saved_registers)) UINT32 is_serial_bus_clear(UINT16 port) {
    return inb(port + 5) & 0x20;
}

__attribute__((no_caller_saved_registers)) VOID serial_char_out(UINT16 port, char datb) {
    while (is_serial_bus_clear(port) == 0);

    outb(port, datb);
}

UINT32 is_serial_recv(UINT16 port) {
    return inb(port + 5) & 1;
}

BYTE serial_char_in(UINT16 port) {
    while(is_serial_recv(port) == 0);

    return inb(port);
}


__attribute__((no_caller_saved_registers)) VOID serial_str_out(UINT16 port, const char* strb) {
    int i = 0;

    while(*(strb + i)) {
        serial_char_out(port, *(strb + i));
        ++i;
    }
}


/*    external    */


VOID init_com1(VOID) {
    init_serial(COM1);
}

__attribute__((no_caller_saved_registers)) VOID com1_outb(char __datb__) {
    serial_char_out(COM1, __datb__);
}

__attribute__((no_caller_saved_registers)) VOID com1_outs(const char* __strb__) {
    serial_str_out(COM1, __strb__);
}

BYTE com1_inb(VOID) {
    return serial_char_in(COM1);
}


/*    debugging    */
__attribute__((no_caller_saved_registers)) VOID com1_addr_of_func(UINT64 func) {
     while(func) {
        int d = func % 10;
        func /= 10;
        serial_char_out(COM1, d + 48);
     }
}
