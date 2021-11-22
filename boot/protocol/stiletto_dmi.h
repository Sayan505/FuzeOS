#pragma once


#include "../types.h"


typedef struct {
    stiletto_dmi_type2_baseboard_t baseboard;
    stiletto_dmi_type4_processor_t processor;
    stiletto_dmi_type17_memory_a_t memory_a;
    stiletto_dmi_type20_memory_b_t memory_b;
} stiletto_dmi_t;


typedef struct {
    char Manufacturer[64];
    char ProductName[64];
} stiletto_dmi_type2_baseboard_t;

typedef struct {
    char           ProcessorVersion[64];
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
