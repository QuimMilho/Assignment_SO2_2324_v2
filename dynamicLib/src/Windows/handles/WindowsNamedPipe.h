#pragma once

#include "macros.h"
#include "Windows/WindowsHandle.h"

#define DEFAULT_NAMED_PIPE_BUFFER 4096

struct SO2_API WindowsNamedPipe : public WindowsHandle {
	WindowsNamedPipe(const _TSTRING& name, const int bufferSize = DEFAULT_NAMED_PIPE_BUFFER, 
			const int defaultTimeout = 100);
	virtual ~WindowsNamedPipe();

	[[nodiscard]] bool create();
	[[nodiscard]] bool open();
	void terminate();

	[[nodiscard]] int write(void* e, const int size);
	[[nodiscard]] int read(void* e, const int size);

	[[nodiscard]] static int write(HANDLE h, void* e, const int size);
	[[nodiscard]] static int read(HANDLE h, void* e, const int size);

private:
	_TSTRING name;
	int size, defaultTimeout;
};
