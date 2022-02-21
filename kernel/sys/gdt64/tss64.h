#include <lib/stdtypes.h>


typedef struct tag_tss {
    UINT32 reserved0;
    UINT64 rsp0;
    UINT64 rsp1;
    UINT64 rsp2;
    UINT64 reseved1;
    UINT64 ist1;
    UINT64 ist2;
    UINT64 ist3;
    UINT64 ist4;
    UINT64 ist5;
    UINT64 ist6;
    UINT64 ist7;
    UINT64 reseved2;
    UINT16 reseved3;
    UINT16 iopb_offset;
} tss_t;
