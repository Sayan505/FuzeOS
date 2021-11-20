#include <sys/mem/efi_memory.h>

#include <lib/serial.h>



char uintTo_StringOutput[128];
const char* to_string(uint64_t value){
    uint8_t size = 0;
    uint64_t sizeTest = value;
    while (sizeTest / 10 > 0){
        sizeTest /= 10;
        size++;
    }

    uint8_t index = 0;
    while(value / 10 > 0){
        uint8_t remainder = value % 10;
        value /= 10;
        uintTo_StringOutput[size - index] = remainder + '0';
        index++;
    }
    uint8_t remainder = value % 10;
    uintTo_StringOutput[size - index] = remainder + '0';
    uintTo_StringOutput[size + 1] = 0; 
    return uintTo_StringOutput;
}


UINT64 get_phys_memory_size(stiletto_memory_t stiletto_memory) {
    UINT64 num_entries;
    
    static UINT64 phys_memory_size = 0;
    if(phys_memory_size > 0) return phys_memory_size;

    num_entries = stiletto_memory.map_sz / stiletto_memory.desc_sz;

    for(UINT32 i = 0; i < num_entries; ++i) {
        EFI_MEMORY_DESCRIPTOR *efi_memory_descriptor = (EFI_MEMORY_DESCRIPTOR *)((UINT64)stiletto_memory.pMem_map + (i * stiletto_memory.desc_sz));
        phys_memory_size += efi_memory_descriptor->NumberOfPages * 4096;
    }

    //

    // BUG:
    // MEMORY SHOWING UP MORE THAN WHAT WAS ALLOCATED.
    com1_outs("Total Physical Memory: ");
    com1_outs(to_string(phys_memory_size));
    com1_outs(" Bytes\n");

    //

    return phys_memory_size;
}
