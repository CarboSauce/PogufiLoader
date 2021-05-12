#pragma once

#include <Uefi.h>
#include <Protocol/GraphicsOutput.h>

EFI_GRAPHICS_OUTPUT_PROTOCOL* init_gop(EFI_BOOT_SERVICES*);

EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* get_gop_mode(EFI_GRAPHICS_OUTPUT_PROTOCOL*);

void gop_query_modes(EFI_GRAPHICS_OUTPUT_PROTOCOL *);

EFI_STATUS set_gop_mode(EFI_GRAPHICS_OUTPUT_PROTOCOL*,UINTN);

void print_framebuffer(EFI_GRAPHICS_OUTPUT_PROTOCOL*);