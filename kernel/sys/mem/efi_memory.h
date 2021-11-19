#pragma once


#include <lib/stdtypes.h>

#include <sys/bootprotocol/stiletto_memory.h>


typedef struct {
    UINT32 Type;
    VOID*  PhysicalStart;
    VOID*  VirtualStart;
    UINT64 NumberOfPages;
    UINT64 Attribute;
} EFI_MEMORY_DESCRIPTOR;


UINT64 get_phys_memory_size(stiletto_memory_t stiletto_memory);
