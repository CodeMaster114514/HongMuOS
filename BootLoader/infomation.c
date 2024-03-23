#include "main.h"
#include <Guid/Acpi.h>

EFI_STATUS
EFIAPI
GetMemoryMap(UINTN *size, EFI_MEMORY_DESCRIPTOR **buffer, UINTN *MapKey, UINTN *DescriptSize, UINT32 *DescriptVersion)
{
	EFI_STATUS status = EFI_SUCCESS;
	gBS->GetMemoryMap(size, *buffer, MapKey, DescriptSize, DescriptVersion);
	*size += 512;

	gBS->AllocatePool(EfiLoaderData, *size, (void **) buffer);
	if (EFI_ERROR(status))
	{
		Print(L"Failed to allocate pool to save memory descriptor\n");
		return status;
	}

	status = gBS->GetMemoryMap(size, *buffer, MapKey, DescriptSize, DescriptVersion);
	if (EFI_ERROR(status))
	{
		Print(L"Failed to get memory map %d\n", status);
		return status;
	}

	return status;
}

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

	UINTN MapSize = 0;
	EFI_MEMORY_DESCRIPTOR *map = NULL;
	UINTN MapKey = 0;
	UINTN DescriptSize = 0;
	UINT32 DescriptVersion = 0;
	status = GetMemoryMap(&MapSize, &map, &MapKey, &DescriptSize, &DescriptVersion);
	if (EFI_ERROR(status))
	{
		return status;
	}

	status = EfiGetSystemConfigurationTable(&gEfiAcpiTableGuid, (void **) &table->rsdt);
	if (EFI_ERROR(status))
	{
		Print(L"Failed to get RSDT address");
		return status;
	}

	table->map.DescriptSize = DescriptSize;
	table->map.DescriptVersion = DescriptVersion;
	table->map.MapKey = MapKey;
	table->map.MapSize = MapSize;
	table->map.MemoryMap = (MemoryDescript *)map;

	Print(L"%d\n%d\n", sizeof(MemoryDescript), sizeof(EFI_MEMORY_DESCRIPTOR));
	Print(L"%d\n", map[0].Type);

	return EFI_SUCCESS;
}
