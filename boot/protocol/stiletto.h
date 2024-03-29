#pragma once


#include "stiletto_video.h"
#include "stiletto_acpi.h"
#include "stiletto_memory.h"
#include "stiletto_dmi.h"


typedef struct {
    stiletto_video_t  stiletto_video;
    stiletto_memory_t stiletto_memory;
    stiletto_acpi_t   stiletto_acpi;
    stiletto_dmi_t    stiletto_dmi;
} stiletto_t;
