#include "pch/so2pch.h"

#include "WindowsHandle.h"

WindowsHandle::WindowsHandle(HANDLE handle) : handle(handle), error(0) {}

WindowsHandle::~WindowsHandle() {
	CloseHandle(handle);
}

HANDLE WindowsHandle::getHandle() const {
	return handle;
}

int WindowsHandle::GetLastError() const {
	return error;
}