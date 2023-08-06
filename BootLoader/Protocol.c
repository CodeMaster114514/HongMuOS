#include "main.h"

EFI_STATUS
EFIAPI
LocateHandle(OUT EFI_HANDLE **handle, OUT UINTN *NoHandle, IN EFI_GUID *guid, IN const CHAR16 *HandleType)
{
    EFI_STATUS status = EFI_SUCCESS;

    status = gBS->LocateHandleBuffer(ByProtocol, guid, NULL, NoHandle, handle);

    if (EFI_ERROR(status))
    {
        Print(L"Failed to locate %s handle\n", HandleType);
        return status;
    }

    return status;
}

EFI_STATUS
EFIAPI
OpenProtocolByHandle(IN EFI_HANDLE ImageHandle, IN EFI_HANDLE handle, IN EFI_GUID *guid, void **protocol, IN const CHAR16 *ProtocolType)
{
    EFI_STATUS status = EFI_SUCCESS;

    status = gBS->OpenProtocol(handle, guid, protocol, ImageHandle, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);

    if (EFI_ERROR(status))
    {
        Print(L"Failed to open %s protocol\n");
        return status;
    }

    return status;
}

EFI_STATUS
EFIAPI
CreatProtocols(IN EFI_HANDLE ImageHandle, IN EFI_GUID *guid ,OUT UINTN *NoHandle, OUT void ***protocol, IN CHAR16 *ProtocolType)
{
    EFI_STATUS status = EFI_SUCCESS;

    EFI_HANDLE *handle = NULL;

    status = LocateHandle(&handle, NoHandle, guid, ProtocolType);
    if (EFI_ERROR(status))
    {
        return status;
    }

    status = gBS->AllocatePool(EfiRuntimeServicesData, sizeof(void *) * *NoHandle, (void **)protocol);
    if (EFI_ERROR(status))
    {
        Print(L"Failed to alloc pool\n");
        return status;
    }

    void **Protocol = *protocol;

    for (UINTN i = 0; i < *NoHandle; ++i)
    {
        status = OpenProtocolByHandle(ImageHandle, handle[i], guid, (void **)&Protocol[i], ProtocolType);
        if (EFI_ERROR(status))
        {
            return status;
        }
    }

    gBS->FreePool((void *)handle);

    return status;
}
