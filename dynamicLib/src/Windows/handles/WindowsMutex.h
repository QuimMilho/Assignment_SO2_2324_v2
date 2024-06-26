#pragma once

#include "Windows/WindowsHandle.h"

struct SO2_API WindowsMutex : public WindowsHandle {
	WindowsMutex(const _TSTRING& name);
	virtual ~WindowsMutex();

	[[nodiscard]] int wait(long ms = 100);
	void release();
	[[nodiscard]] int getLastError() const;

private:
	_TSTRING name;
};