#include <ntddk.h>
#include "PriorityBooster.h"

NTSTATUS PriorityBoosterCreateClose(_In_ PDEVICE_OBJECT DeviceObject, _In_ PIRP Irp) // takes in a device object pointer and an I/O Request Packet pointer
{
	return STATUS_SUCCESS;
}