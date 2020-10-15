#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include "Booster.h"
#include "..\PriorityBooster\Definitions.h"


int main(int argc, const char* argv[])
{
	if (argc < 3)
	{
		printf("Usage: %s <threadId> <priority>", argv[0]);
		return 0;
	}

	auto symlink = L"\\\\.\\PriorityBooster"; // symlink string to driver device
	HANDLE device = CreateFile(symlink, GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, NULL, nullptr); // try to open handle to the device
	if (!device) return Error("Could not open handle to the PriorityBooster device..."); // cry if it fails...

	ThreadData data;
	data.ThreadId = atoi(argv[1]); // target thread ID 
	data.Priority = atoi(argv[2]); // target priority for the thread

	DWORD returnedData;
	BOOL success = DeviceIoControl(
		device, // device
		IOCTL_PRIORITY_BOOSTER_SET_PRIORITY, // IO control code
		&data, // input buffer
		sizeof(data), // input buffer size
		nullptr, // output buffer
		NULL, // output buffer size
		&returnedData, // amount of bytes written
		nullptr
	);
	
	CloseHandle(device);

	if (!success) return Error("Priority change failed...");
	else std::cout << "Priority change succeded!" << std::endl;

	return 0;
}