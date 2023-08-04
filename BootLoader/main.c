#include "main.h"

EFI_STATUS
EFIAPI
UefiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS status;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;
    status = creat_gop(ImageHandle, &gop);
    if(EFI_ERROR(status))
    {
        return status;
    }

    status = set_resolution(gop, 1920,1080);
    if(EFI_ERROR(status))
    {
        return status;
    }
    return EFI_SUCCESS;
}