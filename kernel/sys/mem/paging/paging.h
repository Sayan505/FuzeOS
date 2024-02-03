#pragma once


#include <lib/stdtypes.h>
#include <lib/stdlib.h>

#include <sys/mem/info.h>


#define PAGE_BIT_P_PRESENT (1 << 0)
#define PAGE_BIT_RW_WRITABLE (1 << 1)
#define PAGE_BIT_US_USER (1 << 2)
#define PAGE_XD_NX (1 << 63)

#define PAGE_ADDR_MASK (0x000ffffffffff000)

#define PAGE_BIT_A_ACCESSED (1 << 5)
#define PAGE_BIT_D_DIRTY (1 << 6)


#pragma pack(1)

typedef struct {
    UINT64 entries[512];
} mapping_table;

#pragma pack()


VOID init_paging(mem_info_t mem_info);
VOID* allocate_page(UINT64* alloc_start);
VOID identity_map(UINT64 logical, UINT64 next_alloc_start);
extern VOID load_pml4(mapping_table* pml4);
