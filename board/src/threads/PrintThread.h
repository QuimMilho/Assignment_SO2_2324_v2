#pragma once

#include "dynamicLib.h"

struct PrintThread : public WindowsThread {
	[[nodiscard]] static PrintThread* createThread();
	virtual ~PrintThread();

	DWORD WINAPI function(LPVOID lpParam) override;
private:
	PrintThread();
};