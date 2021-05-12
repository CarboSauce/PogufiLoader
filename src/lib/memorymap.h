#pragma once

#include <Uefi.h>

typedef struct
{
    UINTN mapKey;
    EFI_MEMORY_DESCRIPTOR* memDescriptor;
} efiMemMap_t;

efiMemMap_t initialize_memory_map();