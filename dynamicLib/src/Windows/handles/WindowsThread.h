#pragma once

#include "Windows/WindowsHandle.h"

struct SO2_API WindowsThread : public WindowsHandle {
	virtual ~WindowsThread();

	virtual DWORD WINAPI function(LPVOID data) = 0;

	[[nodiscard]] bool running() const;
	[[nodiscard]] bool paused() const;

	[[nodiscard]] int pause();
	[[nodiscard]] int resume();

	[[nodiscard]] void* getData();
	void terminate();

	void stop();

protected:
	WindowsThread(void * threadData);

private:
	DWORD threadId;
	bool isPaused;
	bool isRunning;
	void * data;
};