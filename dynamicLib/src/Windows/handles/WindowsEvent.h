#pragma once

#include "Windows/WindowsHandle.h"

struct SO2_API WindowsEvent : public WindowsHandle {
	WindowsEvent(const _TSTRING& name, const bool manualReset = false);
	virtual ~WindowsEvent();

	[[nodiscard]] bool create();
	[[nodiscard]] bool open();

	[[nodiscard]] bool set();
	[[nodiscard]] bool reset();

	[[nodiscard]] int wait(const int ms = 100);

	[[nodiscard]] bool triggered() const;

private:
	_TSTRING name;
	int manualReset;
	bool trigger;
};