#pragma once

#define PRIORITY_BOOSTER_DEVICE 0x8000
#define FUNCTION_DEVICE_ONE 0x800
#define IOCTL_PRIORITY_BOOSTER_SET_PRIORITY CTL_CODE(PRIORITY_BOOSTER_DEVICE, FUNCTION_DEVICE_ONE, METHOD_NEITHER, FILE_ANY_ACCESS)

typedef ULONG DWORD;

typedef struct ThreadData
{
	DWORD ThreadId; // contains the ID of the thread
	int Priority; // the priority we want to set on the thread
} ThreadData;
