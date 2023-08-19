#include "main.h"
#include <elf.h>

#define True 1
#define False 0

typedef int Bool;
typedef int (*Kernel)(Table *table);

Bool CheckElf(void *file)
{
	Elf64_Ehdr *header = (Elf64_Ehdr *)file;
	Bool isElf = header->e_ident[EI_MAG0] == ELFMAG0 && header->e_ident[EI_MAG1] == ELFMAG1 && header->e_ident[EI_MAG2] == ELFMAG2 && header->e_ident[EI_MAG3] == ELFMAG3;
	Print(L"%d\n", isElf);
	isElf = isElf && header->e_type == ET_EXEC;
	Print(L"%d\n", isElf);
	isElf = isElf && header->e_machine == EM_X86_64;
	Print(L"%d\n", isElf);
	return isElf;
}

EFI_STATUS LoadSeg(void *kernel, Kernel *entry)
{
	EFI_STATUS status;
	Elf64_Ehdr *ElfHeader = (Elf64_Ehdr *)kernel;
	Elf64_Phdr *ProgramHeader = (Elf64_Phdr *)(kernel + ElfHeader->e_phoff);
	
	EFI_PHYSICAL_ADDRESS HighAddr = 0;
	EFI_PHYSICAL_ADDRESS LowAddr = 0xffffffffffffffff;

	for (int i = 0; i < ElfHeader->e_phnum; ++i)
	{
		if (ProgramHeader[i].p_type == PT_LOAD && ProgramHeader[i].p_paddr < LowAddr)
		{
			LowAddr = ProgramHeader[i].p_paddr;
		}
		if (ProgramHeader[i].p_type == PT_LOAD && ProgramHeader[i].p_paddr + ProgramHeader[i].p_memsz > HighAddr)
		{
			HighAddr = ProgramHeader[i].p_paddr + ProgramHeader[i].p_memsz;
		}
	}

	UINTN pages = (HighAddr - LowAddr) / 4096 + 1;

	EFI_PHYSICAL_ADDRESS NewKernelAddress;

	status = gBS->AllocatePages(AllocateAnyPages, EfiLoaderCode, pages, &NewKernelAddress);
	if (EFI_ERROR(status))
	{
		Print(L"Failed to allocate pages to save kernel code\n");
		return status;
	}

	UINT64 *Zero = (UINT64 *)NewKernelAddress;
	UINTN loop_time = pages << 9;
	for (UINTN i = 0;i < loop_time;++i)
	{
		Zero[i] = 0;
	}

	UINT64 offset = NewKernelAddress - LowAddr;
	for (UINTN i = 0;i < ElfHeader->e_phnum;++i)
	{
		if (ProgramHeader[i].p_type == PT_LOAD)
		{
			UINT8 *from = (UINT8 *)kernel + ProgramHeader[i].p_offset;
			UINT8 *to = (UINT8 *)ProgramHeader[i].p_vaddr + offset;

			for (UINTN j = 0;j < ProgramHeader[i].p_filesz;++j)
			{
				to[j] = from[j];
			}
		}
	}

	*entry = (Kernel) ElfHeader->e_entry + offset;

	return status;
}

EFI_STATUS
EFIAPI
enter_kernel(IN EFI_HANDLE ImageHandle, IN Table *table)
{
	EFI_STATUS status = EFI_SUCCESS;
	EFI_PHYSICAL_ADDRESS kernel;
	status = OpenFile(ImageHandle, L"\\kernel", &kernel);

	if (!CheckElf((void *)kernel))
	{
		Print(L"This isn't a elf file\n");
		return status;
	}

	Kernel kernel_entry;

	status = LoadSeg((void *)kernel, &kernel_entry);
	if (EFI_ERROR(status))
	{
		Print(L"Failed to load segements\n");
		return status;
	}

	gBS->ExitBootServices(ImageHandle, table->map.MapKey);
	if (EFI_ERROR(status))
	{
		Print(L"Failed to exit boot services\n");
		return status;
	}

	Print(L"%d\n",kernel_entry(table));
	return status;
}