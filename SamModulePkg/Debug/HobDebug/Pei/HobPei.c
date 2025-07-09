//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------
#include "HobPei.h"
#include <PiPei.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/PeiServicesLib.h>

//----------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
EFI_GUID gHobDebugGuid = HOB_DEBUG_GUID;

//----------------------------------------------------------------------------
// Function Definition
//----------------------------------------------------------------------------

//==================================================
// Hob Pei Entry
//==================================================
EFI_STATUS
HobPeiEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
    EFI_STATUS    Status = EFI_SUCCESS;

    HOB_DEBUG_GROUP *HobDebugGroup;
    HobDebugGroup = BuildGuidHob (
      &gHobDebugGuid,
      sizeof(HOB_DEBUG_GROUP)
    );
    if (HobDebugGroup == NULL) {
        DEBUG((DEBUG_ERROR, "[HobPeiEntry]: Failed to create HobDebugGroup\n"));
        Status = EFI_OUT_OF_RESOURCES;
        return Status;
    }
    HobDebugGroup->HobDebugValue = 0x66;
    DEBUG((DEBUG_INFO, "[HobPeiEntry]: Created HobDebugGroup, HobDebugGroup->HobDebugValue = 0x%02x\n", HobDebugGroup->HobDebugValue));

    EFI_PHYSICAL_ADDRESS PageBuffer;
    UINTN PageSize = 0x1000;

    Status = PeiServicesAllocatePages (
      EfiBootServicesCode,
      EFI_SIZE_TO_PAGES(PageSize),
      &PageBuffer
    );
    if (EFI_ERROR(Status)) {
        DEBUG((DEBUG_ERROR, "[HobPeiEntry]: Failed to allocate pages, 0x%d(%r)\n", Status, Status));
        return Status;
    }

    UINT8 *PagePtr = (UINT8*)(UINTN)PageBuffer;
    for (UINTN i = 0; i < PageSize; i++) {
      PagePtr[i] = (UINT8)i;
    }

    BuildMemoryAllocationHob(PageBuffer, PageSize, EfiBootServicesCode);

    DEBUG((DEBUG_INFO, "[HobPeiEntry]: Allocated page memory(Boot Service) at 0x%lx(size=0x%lx), and built MemoryAllocationHob\n", PageBuffer, PageSize));

    return Status;
}
