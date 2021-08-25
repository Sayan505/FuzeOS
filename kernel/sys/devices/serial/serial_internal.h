#pragma once


#include <lib/stdtypes.h>

#include <sys/devices/io_ports.h>


// init serial
VOID init_serial(UI16 port);

// set baud rate
VOID set_baud(UI16 port, BYTE baud_rate);

// serial in
UI32 is_serial_bus_clear(UI16 port);
VOID serial_char_out(UI16 port, char  datb);
VOID serial_str_out(UI16 port,  char* strb);

// serial out
UI32 is_serial_recv(UI16 port);
BYTE serial_char_in(UI16 port);
