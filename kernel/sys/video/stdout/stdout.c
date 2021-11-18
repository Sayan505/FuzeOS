#include <sys/video/stdout/internal.h>
#include <sys/video/stdout/stdout.h>


VOID k_putchr(const CHAR _char) {
    static INT32 posi_x = char_width;
    static INT32 posi_y = char_height;

    // CR
    if (_char == '\r') {
        posi_x = 8;

        return;
    }
    // LF
    if (_char == '\n') {
        posi_y += 12;

        return;
    }

    INT32 cx, cy;
    INT32 mask[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
    BYTE* glyph = FONT + _char * 16ULL;

    for (cy = 0; cy < 16; ++cy) {
        for (cx = 0; cx < 8; ++cx) {
            if (glyph[cy] & mask[cx]) putpixel_routine(posi_x - cx, posi_y + cy - 12, 0xFFFFFFFF);
        }
    }

    // next posi
    posi_x += 8;
}

VOID k_putstr(const CHAR* _str) {
    while (*_str != '\0') {
        k_putchr(*_str);

        ++_str;
    }
}


// overloads
void k_putchr_rgb(const CHAR _char, UINT32 _color) {
    static INT32 posi_x = char_width;
    static INT32 posi_y = char_height;

    // CR
    if (_char == '\r') {
        posi_x = 8;

        return;
    }
    // LF
    if (_char == '\n') {
        posi_y += 12;

        return;
    }

    INT32 cx, cy;
    INT32 mask[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
    BYTE* glyph = FONT + _char * 16ULL;

    for (cy = 0; cy < 16; ++cy) {
        for (cx = 0; cx < 8; ++cx) {
            if (glyph[cy] & mask[cx]) putpixel_routine(posi_x - cx, posi_y + cy - 12, _color);
        }
    }

    // next posi
    posi_x += 8;
}

void k_putstr_rgb(const CHAR* _str, UINT32 _color) {
    while (*_str != '\0') {
        k_putchr_rgb(*_str, _color);

        ++_str;
    }
}
