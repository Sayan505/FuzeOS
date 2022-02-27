#include <sys/gdt64/gdt64.h>


void set_segments(UINT16 cs, UINT16 ds) {
    __asm__ volatile(
        "push %0\n\t"
        "push $1f\n\t"
        "lretq\n\t"
        "1:\n\t"
        "mov %1, %%ds\n\t"
        "mov %1, %%es\n\t"
        "mov %1, %%fs\n\t"
        "mov %1, %%gs\n\t"
        "cli\n\t"               // disable interrupts
        "mov %1, %%ss\n\t"
        "sti\n\t"               // enable interrupts
        :: "rmi"((uint64_t)cs), "rm"((uint64_t)ds)
        : "memory"
    );
}

void init_gdt() {
    // populate GDT
    gdt_t gdt = {
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // struct gdt_entry null;

        {0x00, 0x00, 0x00, 0x9A, 0x20, 0x00}, // struct gdt_entry kernel_cs;
        {0x00, 0x00, 0x00, 0x92, 0x00, 0x00}, // struct gdt_entry kernel_ds;
    };

    
    // init gdt
    gdt_desc_t gdt_desc;

    gdt_desc.limit = (UINT16)(sizeof(gdt_t) - 1);    // set size
    gdt_desc.base  = (UINT64)(&gdt);                 // pass populated gdt


    __asm__ volatile("lgdt %0" :: "m"(gdt_desc) : "memory"); // upload gdt to cpu
    set_segments(0x08, 0x10);
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
