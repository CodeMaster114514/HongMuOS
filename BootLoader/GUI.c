#include "main.h"

EFI_STATUS
EFIAPI
creat_gop(IN EFI_HANDLE ImageHandle, OUT EFI_GRAPHICS_OUTPUT_PROTOCOL ***gop, UINTN *NoHandle)
{
	return CreatProtocols(ImageHandle, &gEfiGraphicsOutputProtocolGuid, NoHandle, (void ***)gop, L"EfiGraphicsOutputProtocol");
}

EFI_STATUS
EFIAPI
set_resolution(IN EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, IN UINTN hight, IN UINTN wight)
{
	EFI_STATUS status = EFI_SUCCESS;
	UINTN SizeOfInfo = 0;
	EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *info;
	for (UINTN i = 0; i < gop->Mode->MaxMode; ++i)
	{
		status = gop->QueryMode(
			gop,
			i,
			&SizeOfInfo,
			&info);
		if (EFI_ERROR(status))
		{
			Print(L"Faild to query mode\n");
			return status;
		}

		if (info->HorizontalResolution == hight && info->VerticalResolution == wight)
		{
			gop->SetMode(gop, i);
			break;
		}
		// Print(L"Mode %d; H %d;W: %d\n", i, info->HorizontalResolution, info->VerticalResolution);
	}
	return status;
}