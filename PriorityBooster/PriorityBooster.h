#pragma once
#include <ntddk.h>
#include "Definitions.h"

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