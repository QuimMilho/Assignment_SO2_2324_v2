#include "pch/so2pch.h"

#include "WindowsHandle.h"

WindowsHandle::WindowsHandle(HANDLE handle) : handle(handle) {}

WindowsHandle::~WindowsHandle() {
	CloseHandle(handle);
}

HANDLE WindowsHandle::getHandle() const {
	return handle;
}