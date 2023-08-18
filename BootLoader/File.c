#include "main.h"

EFI_STATUS
EFIAPI
OpenFile(IN EFI_HANDLE ImageHandle, IN CHAR16 *path, OUT EFI_PHYSICAL_ADDRESS *address)
{
    EFI_STATUS status = 0;

    EFI_HANDLE *FileSystemHandle = NULL;
    UINTN NoHandle = 0;
    status = LocateHandle(&FileSystemHandle, &NoHandle, &gEfiSimpleFileSystemProtocolGuid, L"EfiSimpleFileSystemProtocol");
    if (EFI_ERROR(status))
    {
        return status;
    }

    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FileSystem;
    status = OpenProtocolByHandle(ImageHandle, FileSystemHandle[0], &gEfiSimpleFileSystemProtocolGuid, (void **) &FileSystem, L"EfiSimpleFileSystemProtocol");
    if (EFI_ERROR(status))
    {
        return status;
    }

    EFI_FILE_PROTOCOL *volume;
    status = FileSystem->OpenVolume(FileSystem, &volume);
    if (EFI_ERROR(status))
    {
        Print(L"Failed to open volume\n");
        return status;
    }

    EFI_FILE_PROTOCOL *file;
    status = volume->Open(volume, &file, path, EFI_FILE_MODE_READ, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (EFI_ERROR(status))
    {
        Print(L"Failed open file");
        return status;
    }

    EFI_FILE_INFO *FileInfo;
    UINTN InfoSize = sizeof(EFI_FILE_INFO) + 128;

    status = gBS->AllocatePool(EfiLoaderData, InfoSize, (void **) &FileInfo);
    if (EFI_ERROR(status))
    {
        Print(L"Failed to allocate pool to save file info\n");
        return status;
    }

    status = file->GetInfo(file, &gEfiFileInfoGuid, &InfoSize, FileInfo);
    if (EFI_ERROR(status))
    {
        Print(L"Failed to get file info\n");
        return status;
    }

    UINTN NoPage = FileInfo->FileSize / 4096 + 1;
    status = gBS->AllocatePages(AllocateAnyPages, EfiLoaderData, NoPage, address);
    if (EFI_ERROR(status))
    {
        Print(L"Failed to allocate pages to save file data\n");
        return status;
    }

    UINTN ReadSize = FileInfo->FileSize;
    status = file->Read(file, &ReadSize, (void *) *address);
	if (EFI_ERROR(status))
	{
		Print(L"Failed to read file\n");
		return status;
	}

    gBS->FreePool(FileSystemHandle);
    gBS->FreePool(FileInfo);

    return status;
}