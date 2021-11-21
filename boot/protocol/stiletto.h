#pragma once


#include "stiletto_video.h"
#include "stiletto_acpi.h"
#include "stiletto_memory.h"
#include "stiletto_smbios.h"


typedef struct {
    stiletto_video_t  stiletto_video;
    stiletto_memory_t stiletto_memory;
    stiletto_acpi_t   stiletto_acpi;
    stiletto_smbios_t stiletto_smbios;
} stiletto_t;
