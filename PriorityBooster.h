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

void PriorityBoosterUnload
(
	_In_ PDRIVER_OBJECT DriverObject
);

NTSTATUS PriorityBoosterCreateClose
(
	_In_ PDEVICE_OBJECT DeviceObject, 
	_In_ PIRP Irp
);

NTSTATUS PriorityBoosterDeviceControl
(
	_In_ PDEVICE_OBJECT DeviceObject,
	_In_ PIRP Irp
);