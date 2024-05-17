#pragma once

#include "pch/so2pch.h"
#include "macros.h"

struct SO2_API WindowsHandle {
	WindowsHandle(HANDLE handle);
	virtual ~WindowsHandle();

	HANDLE getHandle() const;
	int GetLastError() const;

protected:
	HANDLE handle;
	int error;
};