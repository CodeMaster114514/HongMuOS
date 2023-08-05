#include "main.h"

EFI_STATUS
EFIAPI
UefiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS status;

    Table *table;

    status = gBS->AllocatePool(EfiRuntimeServicesData, sizeof(Table), (void **)&table);
    if(EFI_ERROR(status))
    {
        Print(L"Failed to allocate pool to save table");
        return status;
    }

    EFI_GRAPHICS_OUTPUT_PROTOCOL **gop;
    UINTN gop_count = 0;
    status = creat_gop(ImageHandle, &gop, &gop_count);
    if (EFI_ERROR(status))
    {
        return status;
    }

    table->GOP = gop;
    table->GOP_count = gop_count;

    status = set_resolution(gop[0], 1920, 1080);
    if (EFI_ERROR(status))
    {
        return status;
    }
    return EFI_SUCCESS;
}