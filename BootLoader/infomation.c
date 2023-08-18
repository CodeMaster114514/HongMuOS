#include "main.h"

EFI_STATUS
EFIAPI
GetAllInfomation(IN OUT Table *table, IN EFI_HANDLE ImageHandle)
{
	EFI_STATUS status = EFI_SUCCESS;

	EFI_GRAPHICS_OUTPUT_PROTOCOL **gop;
	UINTN NoHandle = 0;
	status = creat_gop(ImageHandle, &gop, &NoHandle);
	if (EFI_ERROR(status))
	{
		return status;
	}

	status = set_resolution(*gop, 1920, 1080);
	if (EFI_ERROR(status))
	{
		return status;
	}

	table->vdieo.Frame = (RGB *) gop[0]->Mode->FrameBufferBase;
	table->vdieo.FrameBufferSize = gop[0]->Mode->FrameBufferSize;
	table->vdieo.wight = gop[0]->Mode->Info->HorizontalResolution;
	table->vdieo.hight = gop[0]->Mode->Info->VerticalResolution;
	Print(L"h:%d\nw:%d\n", table->vdieo.hight, table->vdieo.wight);

	return EFI_SUCCESS;
}