#include <sys/mem/paging/paging.h>


__attribute__((aligned(0x1000)))
mapping_table pml4;


VOID* allocate_page(UINT64* alloc_start) {
    VOID* page = (VOID*)*alloc_start;

    (*alloc_start) += PAGE_SIZE;    // calc next page alloc start

    return page;
}

VOID identity_map(UINT64 logical, UINT64 next_alloc_start) {
    INT32 flags = PAGE_BIT_P_PRESENT | PAGE_BIT_RW_WRITABLE | PAGE_BIT_US_USER;

    INT32 pml4_idx = (logical >> 39) & 0x1ff;
    INT32 pdp_idx  = (logical >> 30) & 0x1ff;
    INT32 pd_idx   = (logical >> 21) & 0x1ff;
    INT32 pt_idx   = (logical >> 12) & 0x1ff;
    INT32 p_idx    = (logical      ) & 0x7ff;


    if(!(pml4.entries[pml4_idx] & PAGE_BIT_P_PRESENT)) {
        UINT64 pdpt_alloc = (UINT64)allocate_page(&next_alloc_start);

        zero_memory((VOID*)pdpt_alloc, PAGE_SIZE);

        pml4.entries[pml4_idx] = (pdpt_alloc & PAGE_ADDR_MASK) | flags;

        identity_map(pdpt_alloc, next_alloc_start);
    }


    mapping_table* pdpt = (mapping_table*)(pml4.entries[pml4_idx] & PAGE_ADDR_MASK);

    if(!(pdpt->entries[pdp_idx] & PAGE_BIT_P_PRESENT)) {
        UINT64 pdt_alloc = (UINT64)allocate_page(&next_alloc_start);

        zero_memory((VOID*)pdt_alloc, PAGE_SIZE);

        pdpt->entries[pdp_idx] = (pdt_alloc & PAGE_ADDR_MASK) | flags;

        identity_map(pdt_alloc, next_alloc_start);
    }


    mapping_table* pdt = (mapping_table*)(pdpt->entries[pdp_idx] & PAGE_ADDR_MASK);

    if(!(pdt->entries[pd_idx] & PAGE_BIT_P_PRESENT)) {
        UINT64 pt_alloc = (UINT64)allocate_page(&next_alloc_start);

        zero_memory((VOID*)pt_alloc, PAGE_SIZE);

        pdt->entries[pd_idx] = (pt_alloc & PAGE_ADDR_MASK) | flags;

        identity_map(pt_alloc, next_alloc_start);
    }


    mapping_table* pt = (mapping_table*)(pdt->entries[pd_idx] & PAGE_ADDR_MASK);

    if(!(pt->entries[pt_idx] & PAGE_BIT_P_PRESENT)) {
        pt->entries[pt_idx] = (logical & PAGE_ADDR_MASK) | flags;
    }
}


VOID init_paging(mem_info_t mem_info) {
    zero_memory((VOID*)&pml4, mem_info.page_size_kb);

    // allocate all pages
    for(UINT64 i = 0; i < mem_info.total_memory_nbytes; i += PAGE_SIZE) {
        identity_map(i, mem_info.best_alloc_start);
    }

    load_pml4(&pml4);
}
