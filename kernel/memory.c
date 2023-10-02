#include "common.h"

struct
{
	OsMemoryDescript *map;
	unsigned long long DescriptCount;
	unsigned long long MapSize;
	unsigned long long TotalMemory;
	unsigned long long TotalFreeMemory;
	void *next_write;
} OsMemoryMap;

#define findDescriptAndChangeIt(p, size, dtype)                            \
	OsMemoryDescript *now = OsMemoryMap.map;                               \
	while (now)                                                            \
	{                                                                      \
		if (now->PhysicalStart == p && now->NumberOfPages > size)          \
		{                                                                  \
			OsMemoryDescript *next = now->next;                            \
			now->next = OsMemoryMap.next_write;                            \
			now->next->type = now->type;                                   \
			now->type = dtype;                                             \
			now->next->NumberOfPages = now->NumberOfPages - size;          \
			now->NumberOfPages = size;                                     \
			now->next->PhysicalStart = now->PhysicalStart + 4096 * size;   \
			now->next->next = next;                                        \
			OsMemoryMap.next_write += sizeof(OsMemoryDescript);            \
			OsMemoryMap.DescriptCount += 1;                                \
			break;                                                         \
		}                                                                  \
		else if (now->PhysicalStart == pml4 && now->NumberOfPages == size) \
		{                                                                  \
			now->type = OsData;                                            \
			break;                                                         \
		}                                                                  \
		now = now->next;                                                   \
	}

void *find_free_virtual_address();

PTE *find_PTE_from_address(void *address)
{
	PML4 *pml4 = (void *)(get_cr3() & 0xfffffffffffff000);
	unsigned long long offset = (unsigned long long)address >> 39;
	PDPT *pdpt = (void *)((unsigned long long)pml4->pdpt[offset] & 0xfffffffffffff000);
	offset = ((unsigned long long)address >> 30) & 0b111111111;
	PD *pd = (void *)((unsigned long long)pdpt->pd[offset] & 0xfffffffffffff000);
	offset = ((unsigned long long)address >> 21) & 0b111111111;
	PT *pt = (void *)((unsigned long long)pd->pt[offset] & 0xfffffffffffff000);
	offset = ((unsigned long long)address >> 12) & 0b111111111;
	return &pt->pte[offset];
}

void installPage(void *targe, void *paddress, char type)
{
	PTE *pte = find_PTE_from_address(targe);
	pte->page = paddress;
	pte->data += type;
}

void uninstallPage(void *address)
{
	PTE *pte = find_PTE_from_address(address);
	pte->data &= 0xfffffffffffffffe;
}

OsMemoryDescript *get_last_descript()
{
	OsMemoryDescript *now = OsMemoryMap.map;
	while (now)
	{
		now = now->next;
	}
	return now;
}

void *use_a_free_page_address(void *vaddress, OS_MEMORY_TYPE OMT)
{
	void *paddress;
	OsMemoryDescript *now = OsMemoryMap.map;
	while (now)
	{
		if (now->type = FreeMemory)
		{
			paddress = now->PhysicalStart;
			OsMemoryDescript *last = OsMemoryMap.next_write;
			int addSize = (OsMemoryMap.DescriptCount + 1) * sizeof(OsMemoryDescript) <= OsMemoryMap.MapSize && (OsMemoryMap.DescriptCount + 2) * sizeof(OsMemoryDescript) >= OsMemoryMap.MapSize;
			if (addSize)
			{
				void *address_for_next = find_free_virtual_address();
				installPage(address_for_next, paddress, OsData);
				now->VirtualStart = address_for_next;
				OsMemoryMap.MapSize += 4096;
				last = address_for_next;
			}
			OsMemoryDescript *next = now->next;
			now->next = last + sizeof(OsMemoryDescript);
			last = now->next;
			last->next = next;
			last->PhysicalStart = paddress + 4096;
			last->NumberOfPages = now->NumberOfPages - 1;
			OsMemoryMap.next_write = last + sizeof(OsMemoryDescript);
			if (!addSize)
				now->type = OMT;
			now->VirtualStart = vaddress;
			break;
		}
		now = now->next;
	}
	return paddress;
}

void free_a_page_from_address(void *address)
{
	OsMemoryDescript *now = OsMemoryMap.map;
	while (now)
	{
		if (now->VirtualStart == address)
		{
			now->type = FreeMemory;
			now->VirtualStart = 0;
		}
		now = now->next;
	}
}

void uninstall_page_at(void *address)
{
	free_a_page_from_address(address);
	uninstallPage(address);
}

void install_page_at(void *address, char type, OS_MEMORY_TYPE OMT)
{
	void *paddress = use_a_free_page_address(address, OMT);
	installPage(address, paddress, type);
}

void CheckVirtualMemory()
{
	PML4 *pml4 = (void *)(get_cr3() & 0xfffffffffffff000);
	findDescriptAndChangeIt(pml4, 1, OsData);
	for (unsigned long long i = 0; i < 4096 / sizeof(PDPT *); ++i)
	{
		PDPT *pdpt = (void *)((unsigned long long)pml4->pdpt[i] & 0xfffffffffffff000);
		if (!(unsigned long long)pml4->pdpt[i] & 1)
		{
			continue;
		}
		findDescriptAndChangeIt(pdpt, 1, OsData);
		for (unsigned long long j = 0; j < 4096 / sizeof(PD *); ++j)
		{
			PD *pd = (void *)((unsigned long long)pdpt->pd[i] & 0xfffffffffffff000);
			if ((unsigned long long)pdpt->pd[i] & 1)
			{
				continue;
			}
			findDescriptAndChangeIt(pd, 1, OsData);
			for (unsigned long long l = 0; l < 4096 / sizeof(PT *); ++i)
			{
				PT *pt = (void *)((unsigned long long)pd->pt[i] & 0xfffffffffffff000);
				if ((unsigned long long)pdpt->pd[i] & 1)
				{
					continue;
				}
				findDescriptAndChangeIt(pt, 1, OsData);
			}
		}
	}
}

int InitMemory(MemoryMap *map)
{
	OsMemoryMap.map = 0;
	OsMemoryMap.MapSize = map->MapSize + 4096 * 5;

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
		OsMemoryMap.map[OsMemoryAt].next = 0;
		if (i > 0 && OsMemoryMap.map[OsMemoryAt].type == OsMemoryMap.map[OsMemoryAt - 1].type)
			if (OsMemoryMap.map[OsMemoryAt].PhysicalStart == OsMemoryMap.map[OsMemoryAt - 1].PhysicalStart + (OsMemoryMap.map[OsMemoryAt - 1].NumberOfPages << 12))
			{
				OsMemoryMap.map[OsMemoryAt - 1].NumberOfPages += OsMemoryMap.map[OsMemoryAt].NumberOfPages;
				continue;
			}
		if (i > 0)
		{
			OsMemoryMap.map[OsMemoryAt - 1].next = &OsMemoryMap.map[OsMemoryAt];
		}
		++OsMemoryAt;
	}
	OsMemoryMap.DescriptCount = OsMemoryAt + 1;
	OsMemoryMap.TotalMemory = 0;
	OsMemoryMap.TotalFreeMemory = 0;
	OsMemoryMap.next_write = &OsMemoryMap.map[OsMemoryAt + 1];
	OsMemoryDescript *now = OsMemoryMap.map;
	while (now)
	{
		if (now->type != MMIO && now->type != Reserved)
		{
			OsMemoryMap.TotalMemory += now->NumberOfPages << 12;
			OsMemoryMap.TotalFreeMemory += now->type == FreeMemory ? now->NumberOfPages << 12 : 0;
		}
		now = now->next;
	}
	CheckVirtualMemory();
}

unsigned long long GetTotalMemory()
{
	return OsMemoryMap.TotalMemory;
}

unsigned long long GetTotalFreeMemory()
{
	return OsMemoryMap.TotalFreeMemory;
}

void *find_free_virtual_address_from_PT(PT *pt)
{
	for (unsigned long long i = 0; i < 4096 / sizeof(union page *); ++i)
	{
		if (!(pt->pte[i].data & 1))
		{
			return (void *)(i << 12);
		}
	}
	return (void *)-1;
}

void *find_free_virtual_address_from_PD(PD *pd)
{
	for (unsigned long long i = 0; i < 4096 / sizeof(PT *); ++i)
	{
		void *address = find_free_virtual_address_from_PT((void *)((unsigned long long)pd->pt[i] & 0xfffffffffffff000));
		if (address != (void *)-1)
		{
			return (void *)((i << 21) + address);
		}
	}
	return (void *)-1;
}

void *find_free_virtual_address_from_PDPT(PDPT *pdpt)
{
	for (unsigned long long i = 0; i < 4096 / sizeof(PD *); ++i)
	{
		void *address = find_free_virtual_address_from_PD((void *)((unsigned long long)pdpt->pd[i] & 0xfffffffffffff000));
		print("%p\n", address);
		if (address != (void *)-1)
		{
			return (void *)((i << 30) + address);
		}
	}
	return (void *)-1;
}

void *find_free_virtual_address_from_PML4(PML4 *pml4)
{
	for (unsigned long long i = 0; i < 4096 / sizeof(PDPT *); ++i)
	{
		void *address = find_free_virtual_address_from_PDPT((void *)((unsigned long long)pml4->pdpt[i] & 0xfffffffffffff000));
		if (address != (void *)-1)
		{
			return (void *)((i << 39) + address);
		}
	}
	return (void *)-1;
}

void *find_free_virtual_address()
{
	PML4 *pml4 = (void *)(get_cr3() & 0xfffffffffffff000);
	return find_free_virtual_address_from_PML4(pml4);
}

void *alloc_page(char type, OS_MEMORY_TYPE OMT)
{
	void *address = find_free_virtual_address();
	install_page_at(address, type, OMT);
	return address;
}

void free_page(void *address)
{
	uninstall_page_at(address);
}
