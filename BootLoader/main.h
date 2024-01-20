#ifndef MAIN_H
#define MAIN_H
#define Loader

#include <efi/efi.h>
#include <efi/efilib.h>
#include "../inc/common.h"

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
GetAllInfomation(IN OUT Table *table, IN EFI_HANDLE ImageHandle);

EFI_STATUS
EFIAPI
enter_kernel(IN EFI_HANDLE ImageHandle, OUT Table *table);

EFI_STATUS
EFIAPI
OpenFile(IN EFI_HANDLE ImageHandle, IN CHAR16 *PATH, OUT EFI_PHYSICAL_ADDRESS *address);

#endif