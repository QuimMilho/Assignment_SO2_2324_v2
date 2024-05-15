#include "pch/so2pch.h"

#include "WindowsMutex.h"

WindowsMutex::WindowsMutex(const _TSTRING& name) : 
		WindowsHandle(CreateMutex(NULL, FALSE, name.c_str())), name(name) {
	error = getLastError();
}

WindowsMutex::~WindowsMutex() {
	ReleaseMutex(handle);
}

void WindowsMutex::release() {
	ReleaseMutex(handle);
}

int WindowsMutex::wait(long ms) {
	int n = WaitForSingleObject(handle, ms);
	error = getLastError();
	return n;
}

int WindowsMutex::getLastError() const {
	return error;
}