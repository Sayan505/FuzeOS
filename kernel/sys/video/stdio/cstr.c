#include <sys/video/stdio/cstr.h>


CHAR uint_to_str_buffer[128] = { 0 };

const CHAR* uint_to_str(UINT64 val) {
    UINT8 size = 0, index = 0;
    UINT64 size_test = val;

    while(size_test / 10 > 0) {
        size_test /= 10;

        ++size;
    }

    while(val / 10 > 0) {
        UINT8 r = val % 10;
        val /= 10;

        uint_to_str_buffer[size - index] = r + '0';

        ++index;
    }

    UINT8 r = val % 10;

    uint_to_str_buffer[size - index] = r + '0';
    uint_to_str_buffer[size + 1] = 0;
    
    return uint_to_str_buffer;
}


CHAR int_to_str_buffer[128] = { 0 };

const CHAR* int_to_str(INT64 val) {
    UINT8 size = 0, index = 0, is_negative = 0;
    if (val < 0) {
        is_negative = 1;
        val *= -1;

        int_to_str_buffer[0] = '-';
    }

    INT64 size_test = val;

    while(size_test / 10 > 0) {
        size_test /= 10;

        ++size;
    }

    while(val / 10 > 0) {
        INT8 r = val % 10;
        val /= 10;

        int_to_str_buffer[is_negative + size - index] = r + '0';

        ++index;
    }

    INT8 r = val % 10;

    int_to_str_buffer[is_negative + size - index] = r + '0';
    int_to_str_buffer[is_negative + size + 1] = 0;
    
    return int_to_str_buffer;
}
