#include <ntddk.h>
#include "PriorityBooster.h"

void PriorityBoosterUnload(_In_ PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING symlink = RTL_CONSTANT_STRING(L"\\??\\PriorityBooster");
	IoDeleteSymbolicLink(&symlink); // delete the symlink created by DriverEntry
	IoDeleteDevice(DriverObject->DeviceObject); // delete the device object created by DriverEntry
}