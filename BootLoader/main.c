#include "main.h"
#include <stdbool.h>

EFI_STATUS
EFIAPI
UefiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS status;

    Table *table;

    status = gBS->AllocatePool(EfiRuntimeServicesData, sizeof(Table), (void **)&table);
    if(EFI_ERROR(status))
    {
        Print(L"Failed to allocate pool to save table\n");
        return status;
    }

    //status = GetAllInfomation(table, ImageHandle);

    status = set_resolution(table->GOP[0], 1920, 1080);
    if (EFI_ERROR(status))
    {
        return status;
    }

    return status;
}
