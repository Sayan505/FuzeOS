#include <sys/gdt64/gdt64.h>
#include <sys/gdt64/tss64.h>


__attribute__((unused))
static VOID* zero_memory(VOID *dest, UINT64 n_bytes) {
	BYTE *p = (BYTE *)dest;

	while (n_bytes--)
        *(p++) = NULL;

	return dest;
}


void init_gdt() {
    // populate GDT
    gdt_t gdt = {
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // struct gdt_entry null;

        {0x00, 0x00, 0x00, 0x9A, 0xA0, 0x00}, // struct gdt_entry kernel_cs;
        {0x00, 0x00, 0x00, 0x92, 0xA0, 0x00}, // struct gdt_entry kernel_ds;

        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // struct gdt_entry user_null;
        {0x00, 0x00, 0x00, 0x9A, 0xA0, 0x00}, // struct gdt_entry user_cs;
        {0x00, 0x00, 0x00, 0x92, 0xA0, 0x00}, // struct gdt_entry user_ds;
        
        {0x00, 0x00, 0x00, 0x9A, 0xA0, 0x00}, // struct gdt_entry fw_cs;
        {0x00, 0x00, 0x00, 0x92, 0xA0, 0x00}, // struct gdt_entry fw_ds;
        
        {0x00, 0x00, 0x00, 0x89, 0xA0, 0x00}, // struct gdt_entry tss_low;
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}  // struct gdt_entry tss_high;
    };


    // prep Task State Segment
    tss_t tss;
    zero_memory((void *)&tss, sizeof(tss_t));

    UINT64 tss_base = (UINT64)&tss;    // fetch TSS base addr

    gdt.tss_low.base15_0  =  tss_base & 0xFFFF;
    gdt.tss_low.base23_16 = (tss_base >> 16) & 0xFF;
    gdt.tss_low.base31_24 = (tss_base >> 24) & 0xFF;
    gdt.tss_low.limit15_0 = sizeof(tss_t);

    gdt.tss_high.limit15_0 = (tss_base >> 32) & 0xFFFF;
    gdt.tss_high.base15_0  = (tss_base >> 48) & 0xFFFF;
    
    // init gdt
    gdt_desc_t gdt_desc;

    gdt_desc.limit = sizeof(gdt_t) - 1;    // set size
    gdt_desc.base  = (UINT64)&gdt;         // pass populated gdt

    LOAD_GDT64(&gdt_desc);    // upload gdt to cpu
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
