#include <Uefi.h>
#include <Library/CpuLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include "gop.h"
#include "disk.h"
#include <Library/UefiLib.h>
#include <Protocol/SimpleFileSystem.h>
#include <Guid/FileInfo.h>
#include <Library/FileHandleLib.h>
#include "eggload.h"

extern EFI_STATUS EFIAPI UefiBootServicesTableLibConstructor(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE* SystemTable);
extern EFI_STATUS EFIAPI DxeDebugLibConstructor(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE* SystemTable);
extern EFI_STATUS EFIAPI UefiRuntimeServicesTableLibConstructor (IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE* SystemTable);

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    UefiBootServicesTableLibConstructor(ImageHandle,SystemTable);
    DxeDebugLibConstructor(ImageHandle,SystemTable);
    UefiRuntimeServicesTableLibConstructor(ImageHandle,SystemTable);

    gST->ConOut->ClearScreen(gST->ConOut);


    load_egg_kernel();

    return RETURN_SUCCESS;
}
