#include "common.h"

struct
{
	OsMemoryDescript *map;
	unsigned long long DescriptCount;
	unsigned long long MapSize;
	unsigned long long TotalMemory;
} OsMemoryMap;

int InitMemory(MemoryMap *map)
{
	OsMemoryMap.map = 0;
	OsMemoryMap.MapSize = map->MapSize + 4096;

	unsigned long long NumberOfMemoryMapPages = (OsMemoryMap.MapSize >> 12) + 1;
	unsigned long long EfiDescriptCount = map->MapSize / map->DescriptSize;
	for (unsigned long long i = 0; i < EfiDescriptCount; ++i)
	{
		if (map->MemoryMap[i].NumberOfPages >= NumberOfMemoryMapPages && map->MemoryMap[i].type == EfiConventionalMemory)
		{
			OsMemoryMap.map = (void *)map->MemoryMap[i].PhysicalStart;
			OsMemoryMap.MapSize = map->MemoryMap[i].NumberOfPages << 12;
			break;
		}
	}
	unsigned long long OsMemoryAt = 0;
	for (unsigned long long i = 0; i < EfiDescriptCount; ++i)
	{
		if (map->MemoryMap[i].type == EfiBootServicesCode || map->MemoryMap[i].type == EfiBootServicesData || map->MemoryMap[i].type == EfiConventionalMemory)
		{
			OsMemoryMap.map[OsMemoryAt].type = FreeMemory;
		}
		else if (map->MemoryMap[i].type == EfiMemoryMappedIO || map->MemoryMap[i].type == EfiMemoryMappedIOPortSpace)
		{
			OsMemoryMap.map[OsMemoryAt].type = MMIO;
		}
		else if (map->MemoryMap[i].type == EfiLoaderCode)
		{
			OsMemoryMap.map[OsMemoryAt].type = OsCode;
		}
		else if (map->MemoryMap[i].type == EfiLoaderData)
		{
			OsMemoryMap.map[OsMemoryAt].type = OsData;
		}
		else if (map->MemoryMap[i].type == EfiACPIMemoryNVS || map->MemoryMap[i].type == EfiACPIReclaimMemory)
		{
			OsMemoryMap.map[OsMemoryAt].type = ACPI;
		}
		else if (map->MemoryMap[i].type == EfiReservedMemoryType)
		{
			OsMemoryMap.map[OsMemoryAt].type = Reserved;
		}
		else
		{
			OsMemoryMap.map[OsMemoryAt].type = UEFI;
		}
		OsMemoryMap.map[OsMemoryAt].PhysicalStart = map->MemoryMap[i].PhysicalStart;
		OsMemoryMap.map[OsMemoryAt].VirtualStart = map->MemoryMap[i].VirtualStart;
		OsMemoryMap.map[OsMemoryAt].NumberOfPages = map->MemoryMap[i].NumberOfPages;
		if (i > 0 && OsMemoryMap.map[OsMemoryAt].type == OsMemoryMap.map[OsMemoryAt - 1].type)
			if (OsMemoryMap.map[OsMemoryAt].PhysicalStart == OsMemoryMap.map[OsMemoryAt - 1].PhysicalStart + (OsMemoryMap.map[OsMemoryAt - 1].NumberOfPages << 12))
			{
				OsMemoryMap.map[OsMemoryAt - 1].NumberOfPages += OsMemoryMap.map[OsMemoryAt].NumberOfPages;
				continue;
			}
		++OsMemoryAt;
	}
	OsMemoryMap.DescriptCount = OsMemoryAt + 1;
	OsMemoryMap.TotalMemory = 0;
	for (unsigned long long i = 0; i < OsMemoryMap.DescriptCount; ++i)
	{
		if (OsMemoryMap.map[i].type != MMIO && OsMemoryMap.map[i].type != Reserved)
		{
			OsMemoryMap.TotalMemory += OsMemoryMap.map[i].NumberOfPages << 12;
		}
	}
}

unsigned long long GetTotalMemory()
{
	return OsMemoryMap.TotalMemory;
}