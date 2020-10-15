#include <ntifs.h> // needed for PsLookupThreadByThreadId
#include <ntddk.h>
#include "PriorityBooster.h"

NTSTATUS PriorityBoosterDeviceControl(_In_ PDEVICE_OBJECT DeviceObject, _In_ PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	auto stack = IoGetCurrentIrpStackLocation(Irp); // get IO_STACK_LOCATION structure from IRP
	auto status = STATUS_SUCCESS;

	auto controlCode = stack->Parameters.DeviceIoControl.IoControlCode; // get IRP's control code
	if (controlCode != IOCTL_PRIORITY_BOOSTER_SET_PRIORITY)
	{
		status = STATUS_INVALID_DEVICE_REQUEST; // set error if IOCTL is wrong
		KdPrint(("Wrong IOCTL code!\n"));
	}
	else
	{
		if (stack->Parameters.DeviceIoControl.InputBufferLength < sizeof(ThreadData))
		{
			status = STATUS_BUFFER_TOO_SMALL; // set error if buffer length is wrong
			KdPrint(("Wrong buffer length!\n"));
		}
		else
		{
			auto data = (ThreadData*)stack->Parameters.DeviceIoControl.Type3InputBuffer;
			if (data == nullptr)
			{
				status = STATUS_INVALID_PARAMETER; // set error if the pointer is NULL
				KdPrint(("Pointer in PriorityBoosterDeviceControl function is null!\n"));
			}
			else
			{
				if (data->Priority < 1 || data->Priority > 31)
				{
					status = STATUS_INVALID_PARAMETER; // set error if input priority is out of range
					KdPrint(("Priority for the thread is out of range!\n"));
				}
				else
				{
					PETHREAD thread;
					auto threadId = ULongToHandle(data->ThreadId); // macro used to cast the thread's ID to the type needed by PsLookupThreadByThreadId
					status = PsLookupThreadByThreadId(threadId, &thread);

					if (NT_SUCCESS(status)) // continue if PsLookupThreadByThreadId has succeeded
					{
						KeSetPriorityThread((PKTHREAD)thread, data->Priority); // set thread priority to input priority
						ObDereferenceObject(thread);
						KdPrint(("Thread priority changed for thread ID %d to value %d\n", data->ThreadId, data->Priority));
					}
					else KdPrint(("Could not change priority (PSLookupThreadByThreadId failed)\n"));
				}
			}
		}
	}

	Irp->IoStatus.Status = status; // set IRP status
	Irp->IoStatus.Information = NULL; // set IRP information to 0
	IoCompleteRequest(Irp, IO_NO_INCREMENT); // complete IRP with no client priority boost
	return status;
}