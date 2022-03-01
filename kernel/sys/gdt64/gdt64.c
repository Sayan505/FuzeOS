#include <sys/gdt64/gdt64.h>


void init_gdt() {
    // populate GDT    (TODO: TSS)
    gdt_t gdt = {
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    // struct gdt_entry null;

        {0x00, 0x00, 0x00, 0x9A, 0x20, 0x00},    // struct gdt_entry kernel_cs;
        {0x00, 0x00, 0x00, 0x92, 0x00, 0x00},    // struct gdt_entry kernel_ds;
    };

    
    // init gdt
    gdt_desc_t gdt_desc;

    gdt_desc.limit = (UINT16)(sizeof(gdt_t) - 1);    // set size
    gdt_desc.base  = (UINT64)(&gdt);                 // pass populated gdt


    LOAD_GDT64(&gdt_desc);    // lgdt
}




/*
// supply memcpy to make LD stop complaining
__attribute__((unused))
VOID* memcpy(VOID* dest, const VOID* src, UINT64 n_bytes) {
    char *pszDest = (char *)dest;
    const char *pszSource = (const char *)src;
    
    if((pszDest !=  NULL) && (pszSource != NULL)) {
        while(n_bytes) {
            *(pszDest++) = *(pszSource++);

            --n_bytes;
        }
    }
    return dest;
}
*/
