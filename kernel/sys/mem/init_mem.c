#include <sys/mem/init_mem.h>


mem_info_t init_mem(stiletto_memory_t stiletto_memory) {
    mem_info_t res;

    UINTN best_alloc_start = 0;
    UINTN max_num_pages = 0;
    UINT64 total_memory_nbytes = 0;


    for(UINT32 i = 0; i < stiletto_memory.map_sz; i += stiletto_memory.desc_sz) {
        EFI_MEMORY_DESCRIPTOR* curr_desc = (EFI_MEMORY_DESCRIPTOR*)&stiletto_memory.pMem_map[i];    // go thru all the desc

        total_memory_nbytes += (PAGE_SIZE * curr_desc->NumberOfPages);

        if(curr_desc->Type == EFI_CONVENTIONAL_MEMORY) {    // only account for "EfiConventionalMemory" type of descriptors
            if(curr_desc->NumberOfPages > max_num_pages) {  // record the desc with the most num of pages
                max_num_pages = curr_desc->NumberOfPages;
                best_alloc_start = curr_desc->PhysicalStart;
            }
        }
    }

    res.best_alloc_start = best_alloc_start;
    res.max_num_pages = max_num_pages;
    res.total_memory_nbytes = total_memory_nbytes;
    res.page_size_kb = PAGE_SIZE;

    init_paging(res);

    return res;
}
