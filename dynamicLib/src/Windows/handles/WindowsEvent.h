#pragma once

#include "Windows/WindowsHandle.h"

struct SO2_API WindowsEvent : public WindowsHandle {
	WindowsEvent(const _TSTRING& name, const bool manualReset = false);
	virtual ~WindowsEvent();

	bool create();
	bool open();

	bool set();
	bool reset();

	int wait(const int ms = 100);

	bool triggered() const;

private:
	_TSTRING name;
	int manualReset;
	bool trigger;
};