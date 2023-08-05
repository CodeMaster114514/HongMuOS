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