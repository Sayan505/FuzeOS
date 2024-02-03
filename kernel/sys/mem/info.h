#pragma once


#include <lib/stdtypes.h>


#define PAGE_SIZE (4096)


typedef struct {
    UINTN best_alloc_start;
    UINTN max_num_pages;
    UINT64 total_memory_nbytes;
    UINT32 page_size_kb;
} mem_info_t;
