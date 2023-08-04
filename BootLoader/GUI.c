#include "main.h"

EFI_STATUS
EFIAPI
creat_gop(IN EFI_HANDLE ImageHandle, OUT EFI_GRAPHICS_OUTPUT_PROTOCOL **gop)
{
    EFI_STATUS status = EFI_SUCCESS;

    EFI_HANDLE *handle = NULL;
    UINTN NoHandle = 0;
    status = gBS->LocateHandleBuffer(
        ByProtocol,
        &gEfiGraphicsOutputProtocolGuid,
        NULL,
        &NoHandle,
        &handle);

    if (EFI_ERROR(status))
    {
        Print(L"Failed to locate handle\n");
    }

    /*gBS->AllocatePool(
        EfiRuntimeServicesData,
        sizeof(EFI_GRAPHICS_OUTPUT_PROTOCOL *) * (*count),
        (void **)*gop);

    if (EFI_ERROR(status))
    {
        Print(L"Failed to alloc pool to save protocol\n");
        return status;
    }

    for (UINTN i = 0; i < *count; ++i)
    {
        status = gBS->InstallProtocolInterface(
            handle[i],
            &gEfiGraphicsOutputProtocolGuid,
            EFI_NATIVE_INTERFACE,
            NULL);
        if (EFI_ERROR(status))
        {
            Print(L"Failed install interface in %dth. %p\n", i,handle[0]);
            return status;
        }

        status = gBS->OpenProtocol(
            handle[i],
            &gEfiGraphicsOutputProtocolGuid,
            (void **)&(*gop)[i],
            ImageHandle,
            NULL,
            EFI_OPEN_PROTOCOL_GET_PROTOCOL);
        if (EFI_ERROR(status))
        {
            Print(L"Failed to open protocol in %dth\n", i);
            return status;
        }
    }*/

    //status = gBS->InstallProtocolInterface(&handle[0],&gEfiGraphicsOutputProtocolGuid,EFI_NATIVE_INTERFACE,NULL);
    //if(EFI_ERROR(status))
    //{
        //Print(L"Failed to install interface\n");
        //return status;
    //}

    status = gBS->OpenProtocol(handle[0],&gEfiGraphicsOutputProtocolGuid,(void **)gop,ImageHandle,NULL,EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if(EFI_ERROR(status))
    {
        Print(L"Failed to open protocol\n");
        return status;
    }

    return status;
}

EFI_STATUS
EFIAPI
set_resolution(IN EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, IN UINTN hight, IN UINTN wight)
{
    EFI_STATUS status = EFI_SUCCESS;
    UINTN SizeOfInfo = 0;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *info;
    for (UINTN i = 0; i < gop->Mode->MaxMode; ++i)
    {
        status = gop->QueryMode(
            gop,
            i,
            &SizeOfInfo,
            &info);
        if(EFI_ERROR(status))
        {
            Print(L"Faild to query mode\n");
            return status;
        }

        if(info->HorizontalResolution == hight && info->VerticalResolution == wight)
        {
            gop->SetMode(gop,
                i);
                break;
        }
        Print(L"Mode %d; H %d;W: %d\n", i, info->HorizontalResolution, info->VerticalResolution);
    }
    return status;
}