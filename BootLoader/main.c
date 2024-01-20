#include "main.h"
#include <stdbool.h>

EFIAPI
EFI_STATUS
efi_main(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
	EFI_STATUS status = EFI_SUCCESS;

	Table *table = NULL;

	InitializeLib(ImageHandle, SystemTable);

	Print(L"Hello World\n");

	status = gBS->AllocatePool(EfiLoaderData, sizeof(Table), (void **)&table);
	if (EFI_ERROR(status))
	{
		Print(L"Failed to allocate pool to save table, error code %d; %d; %d\n", status, EFI_OUT_OF_RESOURCES, table);
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
