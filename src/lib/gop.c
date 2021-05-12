#include "gop.h"
#include "err.h"
#include <Library/UefiLib.h>
#include <Library/CpuLib.h>

EFI_GRAPHICS_OUTPUT_PROTOCOL* init_gop(EFI_BOOT_SERVICES* bs)
{
    EFI_GUID gopuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    EFI_GRAPHICS_OUTPUT_PROTOCOL* gop = NULL;
    EFI_ASSERT(bs->LocateProtocol(&gopuid, NULL, (void**)&gop),error);

    return gop;
    error: 
    Print(L"Gop failed to initialize.\n");
    return NULL;
}

EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* get_gop_mode(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop)
{
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *info;
    UINTN infoSize = sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION);
    UINT32 gop_mode_num = gop->Mode==NULL ? 0 : gop->Mode->Mode;
    EFI_STATUS status = gop->QueryMode(gop,gop_mode_num,&infoSize, &info); 
    if (status == EFI_NOT_STARTED)
        status = gop->SetMode(gop, 0);
    if(EFI_ERROR(status))
    {
        Print(L"Error occured while getting GOP mode, code:[%d]",status);
        return NULL;
    }


    return info;
}

void gop_query_modes(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop)
{
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *info;
    UINTN infoSize = sizeof(*info);
    for (UINT32 i = 0; i < gop->Mode->MaxMode; ++i)
    {
        EFI_ASSERT(gop->QueryMode(gop,i,&infoSize,&info ),drop);
        Print(L"mode %03d width %d height %d format %x%s\n", i,
              info->HorizontalResolution, info->VerticalResolution,
              info->PixelFormat, i == gop->Mode->Mode ? "(current)" : "");
    }



    drop:
        return; //Drop out
}

void print_framebuffer(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop)
{
    Print(L"Framebuffer address: %x\nSize: %d\nWidth: %d\nHeight: %d\nPixels Per Scan Line: %d\n",
        gop->Mode->FrameBufferBase, gop->Mode->FrameBufferSize,
        gop->Mode->Info->HorizontalResolution,
        gop->Mode->Info->VerticalResolution,
        gop->Mode->Info->PixelsPerScanLine);
    
}

EFI_STATUS set_gop_mode(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop,UINTN mode)
{
    EFI_STATUS status = gop->SetMode(gop,mode);
    if (EFI_ERROR(status)) return status;
    else print_framebuffer(gop);
    return status;

}
