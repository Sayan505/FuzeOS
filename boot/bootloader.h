#pragma once


#include <elf.h>


#include <Uefi.h>

#include <Guid/Acpi.h>
#include <Guid/SmBios.h>
#include <Guid/FileInfo.h>

#include <Protocol/GraphicsOutput.h>
#include <Protocol/Smbios.h>
#include <Protocol/SimpleFileSystem.h>

#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>


#include "types.h"
#include "protocol/stiletto.h"

#define KERNEL_ABS_PATH    L"\\sys\\kernel"
#define IMAGE_LOAD_ADDR    (0x0000000002000000)


EFI_STATUS get_dmi_str_from_index(IN CHAR8 *base_ptr,IN UINT8 strtable_offset, OUT CHAR8 *str_buffer);  // fetches strings from SMBIOS string tables

uint64_t load_image(void *pImage);  // ELF64 exec image parser
