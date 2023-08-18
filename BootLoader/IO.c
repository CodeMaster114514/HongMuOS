#include "main.h"

EFI_STATUS
EFIAPI
creat_di2(IN EFI_HANDLE ImageHandle, OUT EFI_DISK_IO2_PROTOCOL ***di2, OUT UINTN *NoHandle)
{
    return CreatProtocols(ImageHandle, &gEfiDiskIo2ProtocolGuid, NoHandle, (void ***)di2, L"EfiDiskIo2Protocol");
}

EFI_STATUS
EFIAPI
creat_bi2(IN EFI_HANDLE ImageHandle, OUT EFI_BLOCK_IO2_PROTOCOL ***bi2, OUT UINTN *NoHandle)
{
    return CreatProtocols(ImageHandle, &gEfiBlockIo2ProtocolGuid, NoHandle, (void ***)bi2, L"EfiBlockIo2Protocol");
}

EFI_STATUS
EFIAPI
creat_wmc2(IN EFI_HANDLE ImageHandle, OUT EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL ***wmc2, OUT UINTN *NoHandle)
{
    return CreatProtocols(ImageHandle, &gEfiWiFi2ProtocolGuid, NoHandle, (void ***)wmc2, L"EfiWiFi2ProtocolGuid");
}