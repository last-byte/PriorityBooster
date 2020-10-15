#include <ntddk.h>
#include "PriorityBooster.h"

extern "C" 
NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
	DriverObject->DriverUnload = PriorityBoosterUnload; // function responsible for driver unloading
	DriverObject->MajorFunction[IRP_MJ_CREATE] = PriorityBoosterCreateClose; // function responsible for Create* calls
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = PriorityBoosterCreateClose;  // function responsible for Close* calls
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = PriorityBoosterDeviceControl; // function responsible for handling calls to DeviceIoControl

	UNICODE_STRING deviceName = RTL_CONSTANT_STRING(L"\\Device\\PriorityBooster"); // initialize unicode string with device name \Device\PriorityBooster
	PDEVICE_OBJECT DeviceObject;
	NTSTATUS status;
	status = IoCreateDevice
	(
		DriverObject, // the driver object of DriverEntry
		0, // no need to allocate extra bytes for this one
		&deviceName, // the address of the unicode string containing the device name
		FILE_DEVICE_UNKNOWN, // value used for most software drivers
		0, // set to zero for software drivers
		FALSE, // exclusive access, set to false to allow more clients per device
		&DeviceObject // the pointer to pointer to which to write the return value
	);

	if (!NT_SUCCESS(status))
	{
		KdPrint(("Failed to create device. Error: 0x%08X\n", status));
		return status;
	}

	UNICODE_STRING symlink = RTL_CONSTANT_STRING(L"\\??\\PriorityBooster"); // symbolic link named PriorityBooster under GLOBAL??
	status = IoCreateSymbolicLink(&symlink, &deviceName); // try to create symbolink link

	if (!NT_SUCCESS(status))
	{
		KdPrint(("Failed to create symlink. Error: 0x%08X\n", status));
		IoDeleteDevice(DeviceObject);
		return status;
	}

	UNREFERENCED_PARAMETER(RegistryPath);
	
	return STATUS_SUCCESS;
}