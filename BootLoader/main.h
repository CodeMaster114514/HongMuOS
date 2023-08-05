#ifndef MAIN_H
#define MAIN_H

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Uefi/UefiBaseType.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/DiskIo2.h>
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

#endif