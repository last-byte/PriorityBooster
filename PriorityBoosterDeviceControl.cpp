#include <ntddk.h>
#include "PriorityBooster.h"

NTSTATUS PriorityBoosterDeviceControl(_In_ PDEVICE_OBJECT DeviceObject, _In_ PIRP Irp)
{
	return STATUS_SUCCESS;
}