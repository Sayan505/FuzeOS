#include <sys/gdt64/gdt64.h>
#include <sys/gdt64/tss.h>


VOID init_gdt(VOID) {
    // populate GDT
    __attribute__((aligned(0x1000)))
    gdt_t gdt = {
        {0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00},    // struct gdt_entry null;

        {0x0000, 0x0000, 0x00, 0x9A, 0xA0, 0x00},    // struct gdt_entry kernel_cs;
        {0x0000, 0x0000, 0x00, 0x92, 0xA0, 0x00},    // struct gdt_entry kernel_ds;

        {0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00},    // struct gdt_entry user_null;
        {0x0000, 0x0000, 0x00, 0xF2, 0xA0, 0x00},    // struct gdt_entry user_ds;
        {0x0000, 0x0000, 0x00, 0xFA, 0xA0, 0x00},    // struct gdt_entry user_cs;

        {0x0000, 0x0000, 0x00, 0x89, 0xA0, 0x00},    // struct gdt_entry tss_low;
        {0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00},    // struct gdt_entry tss_high;
    };


    tss_t tss = { 0, 0, 0, 0, 0, 0 ,0 , 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 };
    UINT64 tss_base = (UINT64) &tss;

    gdt.tss_low.base_low_16_31 = tss_base & 0xffff;
    gdt.tss_low.base_mid_32_39 = (tss_base >> 16) & 0xff;
    gdt.tss_low.base_high_56_63 = (tss_base >> 24) & 0xff;
    gdt.tss_low.limit_0_15 = sizeof(tss);
    gdt.tss_high.limit_0_15 = (tss_base >> 32) & 0xffff;
    gdt.tss_high.base_low_16_31 = (tss_base >> 48) & 0xffff;


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
