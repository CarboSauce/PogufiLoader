#include "eggload.h"
#include "disk.h"
#include "gop.h"
#include <Library/FileHandleLib.h>
#include <Library/UefiLib.h>
#include "memorymap.h"

void load_egg_kernel ()
{
   EFI_FILE* file = load_file (L"kernel.img");
   if (file == NULL)
   {
      Print (L"Kernel Couldnt be loaded.\n");
      return;
   }
   else
      Print (L"Kernel loaded sucesfully.");

   UINT64 file_size;

   // load kernel from file
   EFI_PHYSICAL_ADDRESS* load_address = (EFI_PHYSICAL_ADDRESS*)0x200000;
   gBS->AllocatePages (AllocateAddress, EfiLoaderData, 1, load_address);
   FileHandleSetPosition (file, 0);
   FileHandleGetSize (file, &file_size);
   FileHandleRead (file, &file_size, load_address);

   egg_kernel_entry kernel_entry = (egg_kernel_entry)load_address;

   egg_t* kernel_frame;

   gBS->AllocatePool (EfiLoaderData, sizeof (egg_t), (void**)&kernel_frame);

   // setup frame buffer for egg kernel
   EFI_GRAPHICS_OUTPUT_PROTOCOL* gop = init_gop (gBS);

   set_gop_mode (gop, gop->Mode->MaxMode - 1);
   kernel_frame->fb = (framebuffer_t){
      .fb_start = (void*)gop->Mode->FrameBufferBase,
      .fb_end = (void*)(gop->Mode->FrameBufferBase
                        + gop->Mode->FrameBufferSize),
      .pitch = gop->Mode->Info->PixelsPerScanLine,
      .height = gop->Mode->Info->VerticalResolution,
      .width = gop->Mode->Info->HorizontalResolution
   };


   efiMemMap_t memMap = initialize_memory_map();

   gBS->ExitBootServices(memMap.memDescriptor,memMap.mapKey);
   kernel_entry (kernel_frame);
}