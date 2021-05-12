#include "disk.h"
#include <Protocol/LoadedImage.h>

EFI_FILE* load_file(CHAR16* path)
{
    EFI_FILE* loaded_file;
    EFI_LOADED_IMAGE_PROTOCOL* loaded_image;
    gBS->HandleProtocol(gImageHandle,&gEfiLoadedImageProtocolGuid,(void**)&loaded_image);
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fs;
    gBS->HandleProtocol(loaded_image->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, (void**)&fs);
    EFI_FILE* dir; 
    fs->OpenVolume(fs,&dir);
    if (EFI_ERROR(dir->Open(dir, &loaded_file, path, EFI_FILE_MODE_READ,
                            EFI_FILE_READ_ONLY)))
        return NULL;
    return loaded_file;
} 