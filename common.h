#ifndef COMMON_H
#define COMMON_H

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Uefi/UefiBaseType.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/DiskIo2.h>

typedef struct
{
    UINTN GOP_count;
    EFI_GRAPHICS_OUTPUT_PROTOCOL **GOP;
} Table;

#endif