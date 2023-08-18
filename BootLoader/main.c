#include "main.h"
#include <stdbool.h>

EFI_STATUS
EFIAPI
UefiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
	EFI_STATUS status;

	Table *table;

	status = gBS->AllocatePool(EfiRuntimeServicesData, sizeof(Table), (void **)&table);
	if (EFI_ERROR(status))
	{
		Print(L"Failed to allocate pool to save table\n");
		return status;
	}

	status = GetAllInfomation(table, ImageHandle);
	if (EFI_ERROR(status))
	{
		return status;
	}

	Print(L"%d\n", table->vdieo.FrameBufferSize);
	
	status = enter_kernel(ImageHandle, table);

	return status;
}
