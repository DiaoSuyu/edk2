//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------
#include "HobDxe.h"
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Pi/PiHob.h>

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
// Hob Dxe Entry
//==================================================
EFI_STATUS HobDxeEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_STATUS    Status = EFI_SUCCESS;

    EFI_HOB_GUID_TYPE *GuidHob;
    HOB_DEBUG_GROUP *HobDebugGroup;

    GuidHob = GetFirstGuidHob(&gHobDebugGuid);
    if (GuidHob == NULL) {
        DEBUG((DEBUG_ERROR, "[HobDxeEntry]: Failed to get hob with gHobDebugGuid\n"));
        Status = EFI_OUT_OF_RESOURCES;
        return Status;
    }
    HobDebugGroup = (HOB_DEBUG_GROUP*)GET_GUID_HOB_DATA(GuidHob);
    DEBUG((DEBUG_INFO, "[HobDxeEntry]: HobDebugGroup->HobDebugValue = 0x%02x\n", HobDebugGroup->HobDebugValue));

    EFI_PEI_HOB_POINTERS Hob;
    for (Hob.Raw = GetHobList(); !END_OF_HOB_LIST(Hob); Hob.Raw = GET_NEXT_HOB(Hob)) {
      if (GET_HOB_TYPE(Hob) == EFI_HOB_TYPE_MEMORY_ALLOCATION) {
        EFI_HOB_MEMORY_ALLOCATION *MemAlloc = Hob.MemoryAllocation;
        if (MemAlloc->AllocDescriptor.MemoryLength == 0x1000 &&
            MemAlloc->AllocDescriptor.MemoryType == EfiBootServicesCode) {
          UINT8 *Ptr = (UINT8 *)(UINTN)MemAlloc->AllocDescriptor.MemoryBaseAddress;
          DEBUG((DEBUG_INFO, "[HobDxeEntry]: Found Page MemoryAllocationHob, Base=0x%lx, Length=0x%lx\n",  \
              MemAlloc->AllocDescriptor.MemoryBaseAddress, MemAlloc->AllocDescriptor.MemoryLength));
          for (UINTN i = 0; i < 0x1000; i++) {
            if ((i % 16) == 0) {
              DEBUG((DEBUG_INFO, "\n%04x: ", i));
            }
            DEBUG((DEBUG_INFO, "%02x ", Ptr[i]));
          }
          DEBUG((DEBUG_INFO, "\n"));
          break; 
        }
      }
    }

    return Status;
}
