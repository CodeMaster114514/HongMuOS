#ifndef COMMON_H
#define COMMON_H

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Uefi/UefiBaseType.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/DiskIo2.h>
#include <Protocol/BlockIo2.h>

typedef struct
{
    UINTN MapSize;
    EFI_MEMORY_DESCRIPTOR *Map;
    UINTN MapKey;
    UINTN DescriptorSize;
    UINT32 DescriptorVersion;
} Memory;

typedef struct
{
    UINTN GOP_count;
    EFI_GRAPHICS_OUTPUT_PROTOCOL **GOP;

    UINTN DI2_count;
    EFI_DISK_IO2_PROTOCOL **DI2;

    UINTN BI2_count;
    EFI_BLOCK_IO2_PROTOCOL **BI2;

    Memory *mem;

} Table;

#endif