#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Uefi/UefiBaseType.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/DiskIo2.h>

EFI_STATUS
EFIAPI
UefiMain(IN EFI_HANDLE ImageHand,IN EFI_SYSTEM_TABLE* SystemTable);

EFI_STATUS
EFIAPI
creat_gop(IN EFI_HANDLE ImageHand, OUT EFI_GRAPHICS_OUTPUT_PROTOCOL **gop);

EFI_STATUS
EFIAPI
set_resolution(IN EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, IN UINTN hight, IN UINTN wight);