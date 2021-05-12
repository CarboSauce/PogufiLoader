#pragma once
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/SimpleFileSystem.h>
EFI_FILE* load_file(CHAR16*);
