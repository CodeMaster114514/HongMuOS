#include "main.h"

EFI_STATUS
EFIAPI
GetMemoryInfomation(OUT Memory **mem)
{
    UINTN status = EFI_SUCCESS;

    UINTN MapSize = 0;
    EFI_MEMORY_DESCRIPTOR *Map = NULL;
    UINTN MapKey = 0;
    UINTN DescriptorSize = 0;
    UINT32 DescriptorVersion = 0;

    status = gBS->GetMemoryMap(&MapSize, Map, &MapKey, &DescriptorSize, &DescriptorVersion);
    if (EFI_ERROR(status) && status != EFI_BUFFER_TOO_SMALL)
    {
        Print(L"Failed to get memory map size\n");
        return status;
    }

    status = gBS->AllocatePool(EfiRuntimeServicesData, MapSize, (void **)&Map);
    if (EFI_ERROR(status))
    {
        Print(L"Failed to locate pool to save map");
        return status;
    }

    status = gBS->GetMemoryMap(&MapSize, Map, &MapKey, &DescriptorSize, &DescriptorVersion);
    if (EFI_ERROR(status))
    {
        Print(L"Failed to get memory map\n");
        return status;
    }

    status = gBS->AllocatePool(EfiRuntimeServicesData, sizeof(Memory), (void **)mem);
    if(EFI_ERROR(status))
    {
        Print(L"Failed to locate pool to save Memory");
        return status;
    }

    Memory *memory = *mem;
    memory->Map = Map;
    memory->MapSize = MapSize;
    memory->MapKey = MapKey;
    memory->DescriptorSize = DescriptorSize;
    memory->DescriptorVersion = DescriptorVersion;

    return status;
}
