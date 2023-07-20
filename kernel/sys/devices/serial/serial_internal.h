#pragma once


#include <lib/stdtypes.h>

#include <sys/devices/io_ports.h>


// init serial
VOID init_serial(UINT16 port);

// set baud rate
VOID set_baud(UINT16 port, BYTE baud_rate);

// serial in
__attribute__((no_caller_saved_registers)) UINT32 is_serial_bus_clear(UINT16 port);
__attribute__((no_caller_saved_registers)) VOID serial_char_out(UINT16 port, char  datb);
__attribute__((no_caller_saved_registers)) VOID serial_str_out(UINT16 port,  const char* strb);

// serial out
UINT32 is_serial_recv(UINT16 port);
BYTE serial_char_in(UINT16 port);
