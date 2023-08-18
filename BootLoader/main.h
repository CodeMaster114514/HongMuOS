#ifndef MAIN_H
#define MAIN_H

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Uefi/UefiBaseType.h>
#include <Guid/FileInfo.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/DiskIo2.h>
#include <Protocol/BlockIo2.h>
#include <Protocol/WiFi2.h>
#include "../common.h"

EFI_STATUS
EFIAPI
UefiMain(IN EFI_HANDLE ImageHand, IN EFI_SYSTEM_TABLE *SystemTable);

EFI_STATUS
EFIAPI
creat_gop(IN EFI_HANDLE ImageHand, OUT EFI_GRAPHICS_OUTPUT_PROTOCOL ***gop, UINTN *NoHandle);
EFI_STATUS
EFIAPI
set_resolution(IN EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, IN UINTN hight, IN UINTN wight);

EFI_STATUS
EFIAPI
LocateHandle(OUT EFI_HANDLE **handle, OUT UINTN *NoHandle, IN EFI_GUID *guid, IN const CHAR16 *HandleType);
EFI_STATUS
EFIAPI
OpenProtocolByHandle(IN EFI_HANDLE ImageHandle, IN EFI_HANDLE handle, IN EFI_GUID *guid, void **protocol, IN const CHAR16 *ProtocolType);
EFI_STATUS
EFIAPI
CreatProtocols(IN EFI_HANDLE ImageHandle, IN EFI_GUID *guid ,OUT UINTN *NoHandle, OUT void ***protocol, IN CHAR16 *ProtocolType);

EFI_STATUS
EFIAPI
creat_di2(IN EFI_HANDLE ImageHandle, OUT EFI_DISK_IO2_PROTOCOL ***di2, UINTN *NoHandle);
EFI_STATUS
EFIAPI
creat_bi2(IN EFI_HANDLE ImageHandle, OUT EFI_BLOCK_IO2_PROTOCOL ***bi2, UINTN *NoHAndle);
EFI_STATUS
EFIAPI
creat_wmc2(IN EFI_HANDLE ImageHandle, OUT EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL ***wmc2, OUT UINTN *NoHandle);

EFI_STATUS
EFIAPI
GetAllInfomation(IN OUT Table *table, IN EFI_HANDLE ImageHandle);

EFI_STATUS
EFIAPI
enter_kernel(IN EFI_HANDLE ImageHandle, OUT Table *table);

EFI_STATUS
EFIAPI
OpenFile(IN EFI_HANDLE ImageHandle, IN CHAR16 *PATH, OUT EFI_PHYSICAL_ADDRESS *address);

#endif