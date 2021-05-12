#include "memorymap.h"
#include "err.h"
#include <Library/CpuLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

efiMemMap_t initialize_memory_map()
{
   EFI_MEMORY_DESCRIPTOR* EfiMemoryMap = {0};
   UINTN EfiMemoryMapSize = 0;
   UINTN EfiMapKey;
   UINTN EfiDescriptorSize;
   UINT32 EfiDescriptorVersion;
   EFI_MEMORY_DESCRIPTOR* EfiEntry;
   //
   // Get the EFI memory map.
   //

   EFI_ASSERT(gBS->GetMemoryMap(
                  &EfiMemoryMapSize,
                  EfiMemoryMap,
                  &EfiMapKey,
                  &EfiDescriptorSize,
                  &EfiDescriptorVersion),
              error);

   //
   // Use size returned for the AllocatePool.
   //

   EFI_ASSERT((EFI_MEMORY_DESCRIPTOR*)gBS->AllocatePool(EfiLoaderData,
                                                        EfiMemoryMapSize + 2 * EfiDescriptorSize,
                                                        (void**)&EfiMemoryMap),
              error);
   if (EFI_ERROR(gBS->GetMemoryMap(
           &EfiMemoryMapSize,
           EfiMemoryMap,
           &EfiMapKey,
           &EfiDescriptorSize,
           &EfiDescriptorVersion)))
   {
      gBS->FreePool(EfiMemoryMap);
   }

   //
   // Get descriptors
   //
   EfiEntry = EfiMemoryMap;
   /*    do
   {

      EfiEntry = NEXT_MEMORY_DESCRIPTOR(EfiEntry, EfiDescriptorSize);
   } while ((UINT8*)EfiEntry < (UINT8*)EfiMemoryMap + EfiMemoryMapSize);
 */
   return (efiMemMap_t){.mapKey = EfiMapKey, .memDescriptor = EfiMemoryMap};

error:
   Print(L"Error happened with Memory map!");
   return (efiMemMap_t){0,0};
}