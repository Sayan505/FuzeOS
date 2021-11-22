#pragma once


#include "../types.h"


typedef struct {
    char           ProcessorVersion[64];
    char           ProcessorManufacturer[64];
    unsigned short CurrentSpeed;
    unsigned char  CoreCount;
    unsigned char  ThreadCount;
} stiletto_dmi_type4_processor_t;

typedef struct {
    unsigned short ConfiguredMemoryClockSpeed;
} stiletto_dmi_type17_memory_a_t;

typedef struct {
    unsigned long long Size;    // ExtendedEndingAddress - ExtendedStartingAddress + 1 (Bytes)
} stiletto_dmi_type20_memory_b_t;


typedef struct {
    stiletto_dmi_type4_processor_t processor;
    stiletto_dmi_type17_memory_a_t memory_a;
    stiletto_dmi_type20_memory_b_t memory_b;
} stiletto_dmi_t;
