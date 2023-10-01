#include "common.h"

struct
{
	OsMemoryDescript *map;
	unsigned long long DescriptCount;
	unsigned long long MapSize;
	unsigned long long TotalMemory;
	unsigned long long TotalFreeMemory;
} OsMemoryMap;

void uninstallPage(void *address)
{
	PML4 *pml4 = (void *)(get_cr3() & 0xfffffffffffff000);
	unsigned long long offset = (unsigned long long)address >> 39;
	PDPT *pdpt = (void *)((unsigned long long)pml4->pdpt[offset] & 0xfffffffffffff000);
	offset = ((unsigned long long)address >> 30) & 0b111111111;
	PD *pd = (void *)((unsigned long long)pdpt->pd[offset] & 0xfffffffffffff000);
	offset = ((unsigned long long)address >> 21) & 0b111111111;
	PT *pt = (void *)((unsigned long long)pd->pt[offset] & 0xfffffffffffff000);
	offset = ((unsigned long long)address >> 12) & 0b111111111;
	pt->pages[offset]->data &= 0xfffffffffffffffe;
}

void UninstallFreeMemory()
{
	for (unsigned long long i = 0; i < OsMemoryMap.DescriptCount; ++i)
	{
		if (OsMemoryMap.map[i].type == FreeMemory)
		{
			for (unsigned long long j = 0; j < OsMemoryMap.map[i].NumberOfPages; ++j)
			{
				void *Vadd = OsMemoryMap.map[i].VirtualStart;
				uninstallPage(Vadd);
				Vadd += 4096;
			}
			OsMemoryMap.map[i].VirtualStart = 0;
		}
	}
}

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
			map->MemoryMap[i].type = EfiLoaderData;
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
	OsMemoryMap.TotalFreeMemory = 0;
	for (unsigned long long i = 0; i < OsMemoryMap.DescriptCount; ++i)
	{
		if (OsMemoryMap.map[i].type != MMIO && OsMemoryMap.map[i].type != Reserved)
		{
			OsMemoryMap.TotalMemory += OsMemoryMap.map[i].NumberOfPages << 12;
			OsMemoryMap.TotalFreeMemory += OsMemoryMap.map[i].type == FreeMemory ? OsMemoryMap.map[i].NumberOfPages << 12 : 0;
		}
	}
	UninstallFreeMemory();
}

unsigned long long GetTotalMemory()
{
	return OsMemoryMap.TotalMemory;
}

unsigned long long GetTotalFreeMemory()
{
	return OsMemoryMap.TotalFreeMemory;
}