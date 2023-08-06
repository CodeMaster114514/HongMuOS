#include "main.h"

EFI_STATUS
EFIAPI
GetAllInfomation(IN OUT Table *table, IN EFI_HANDLE ImageHandle)
{
    EFI_STATUS status = EFI_SUCCESS;

    EFI_GRAPHICS_OUTPUT_PROTOCOL **gop;
    UINTN NoHandle = 0;
    status = creat_gop(ImageHandle, &gop, &NoHandle);
    if (EFI_ERROR(status))
    {
        return status;
    }

    table->GOP = gop;
    table->GOP_count = NoHandle;

    EFI_DISK_IO2_PROTOCOL **di2;
    status = creat_di2(ImageHandle, &di2, &NoHandle);
    if (EFI_ERROR(status))
    {
        return status;
    }

    table->DI2 = di2;
    table->DI2_count = NoHandle;

    EFI_BLOCK_IO2_PROTOCOL **bi2;
    status = creat_bi2(ImageHandle, &bi2, &NoHandle);
    if (EFI_ERROR(status))
    {
        return status;
    }

    table->BI2 = bi2;
    table->BI2_count = NoHandle;

    status = GetMemoryInfomation(&table->mem);
    if(EFI_ERROR(status))
    {
        return status;
    }

    return EFI_SUCCESS;
}