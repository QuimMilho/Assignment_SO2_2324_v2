#pragma once

#include "Windows/WindowsHandle.h"

struct SO2_API WindowsThread : public WindowsHandle {
	virtual ~WindowsThread();

	[[nodiscard]] bool running() const;
	[[nodiscard]] bool paused() const;

	[[nodiscard]] int pause();
	[[nodiscard]] int resume();

	[[nodiscard]] void* getData();

	void stop();

protected:
	WindowsThread(void * threadData, LPTHREAD_START_ROUTINE function);

private:
	DWORD threadId;
	bool isPaused;
	bool isRunning;
	void * data;
};