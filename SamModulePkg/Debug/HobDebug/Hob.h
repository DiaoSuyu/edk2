#ifndef __HOB_H__
#define __HOB_H__

#include <Uefi.h>

// 3F2504E0-4F89-11D3-9A0C-0305E82C3301
#define HOB_DEBUG_GUID {0x3f2504e0, 0x4f89, 0x11d3, { 0x9a, 0x0c, 0x03, 0x05, 0xe8, 0x2c, 0x33, 0x01}}

#pragma pack(1)
typedef struct {
    UINT8 HobDebugValue;
} HOB_DEBUG_GROUP;
#pragma pack()

extern EFI_GUID gHobDebugGuid;

#endif // __HOB_H__
