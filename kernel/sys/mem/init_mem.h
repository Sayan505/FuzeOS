#pragma once


#include <lib/stdtypes.h>

#include <boot/protocol/stiletto_memory.h>

#include <sys/mem/info.h>
#include <sys/mem/efi/efi_memory_descriptor.h>

#include <sys/mem/paging/paging.h>


mem_info_t init_mem(stiletto_memory_t stiletto_memory);
