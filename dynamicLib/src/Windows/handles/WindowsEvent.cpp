#include "pch/so2pch.h"

#include "WindowsEvent.h"

WindowsEvent::WindowsEvent(const _TSTRING& name, const bool manualReset): WindowsHandle(NULL), name(name),
		manualReset(manualReset ? 1 : 0), trigger(false) {}

WindowsEvent::~WindowsEvent() {}

bool WindowsEvent::create() {
	handle = CreateEvent(NULL, manualReset, FALSE, name.c_str());
	error = GetLastError();
	if (handle)
		return true;
	return false;
}

bool WindowsEvent::open() {
	handle = OpenEvent(SYNCHRONIZE, FALSE, name.c_str());
	error = GetLastError();
	if (handle)
		return true;
	return false;
}

bool WindowsEvent::set() {
	BOOL set = SetEvent(handle);
	error = GetLastError();
	if (set)
		trigger = true;
	return set;
}

bool WindowsEvent::reset() {
	BOOL reset = ResetEvent(handle);
	error = GetLastError();
	if (reset)
		trigger = false;
	return reset;
}

int WindowsEvent::wait(const int ms) {
	return WaitForSingleObject(handle, ms);
}

bool WindowsEvent::triggered() const {
	return trigger;
}