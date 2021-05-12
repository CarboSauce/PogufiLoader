#pragma once

#ifndef EFI_ASSERT
    #define EFI_ASSERT(check, execute) do \
        { if (EFI_ERROR(check)) goto execute; } \
        while(0)
#endif