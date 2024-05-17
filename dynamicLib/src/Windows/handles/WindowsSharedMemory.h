#pragma once

#include "Windows/WindowsHandle.h"

struct SO2_API WindowsSharedMemory : public WindowsHandle {
	WindowsSharedMemory(const _TSTRING& name, const int size = 1024);
	virtual ~WindowsSharedMemory();

	[[nodiscard]] int createFile(const int access);
	[[nodiscard]] int openFile(const int access);
	[[nodiscard]] int map();
	void unmap();

	[[nodiscard]] bool create(const int access);
	[[nodiscard]] bool open(const int access);

	void write(void* e, const int size = 0);
	[[nodiscard]] int read(void* e, const int size = 0);

private:
	void* data;
	_TSTRING name;
	int size, access;
	bool created;
};
