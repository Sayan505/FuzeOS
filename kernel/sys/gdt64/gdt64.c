#include <sys/gdt64/gdt64.h>


__attribute__((unused))
static VOID* zero_memory(VOID *dest, UINT64 n_bytes) {
	BYTE *p = (BYTE *)dest;

	while (n_bytes--)
        *(p++) = NULL;

	return dest;
}


VOID init_gdt(VOID) {
    // populate GDT
    gdt_t gdt = {
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    // struct gdt_entry null;

        {0x00, 0x00, 0x00, 0x9A, 0xA0, 0x00},    // struct gdt_entry kernel_cs;
        {0x00, 0x00, 0x00, 0x92, 0x00, 0x00},    // struct gdt_entry kernel_ds;

        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00},    // struct gdt_entry user_null;

        {0x00, 0x00, 0x00, 0xFA, 0xA0, 0x00},    // struct gdt_entry user_cs;
        {0x00, 0x00, 0x00, 0xF2, 0xA0, 0x00},    // struct gdt_entry user_ds;

        {0x00, 0x00, 0x00, 0x92, 0xA0, 0x00},    // struct gdt_entry ovmf_ds;
        {0x00, 0x00, 0x00, 0x9A, 0xA0, 0x00},    // struct gdt_entry ovmf_cs;
    };

    
    // init gdt
    gdt_desc_t gdt_desc;

    gdt_desc.limit = (UINT16)(sizeof(gdt_t) - 1);    // set size
    gdt_desc.base  = (UINT64)(&gdt);                 // pass populated gdt


    LOAD_GDT64(&gdt_desc);    // lgdt
}




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

// ref: https://wiki.osdev.org/Global_Descriptor_Table
