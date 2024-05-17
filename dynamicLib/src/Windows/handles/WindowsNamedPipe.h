#pragma once

#include "macros.h"
#include "Windows/WindowsHandle.h"

template<typename T>
struct Envelope {
	TCHAR toName[MAX_STRING], fromName[MAX_STRING];
	T data;
};

struct SO2_API WindowsNamedPipe : public WindowsHandle {
	WindowsNamedPipe(const _TSTRING& name);
	virtual ~WindowsNamedPipe();

	int createFile();
	int openFile();
	int unmap();

	template<typename T>
	int write(Envelope<T>* e);
	template<typename T>
	int read(Envelope<T>* e);

private:
	_TSTRING name;
	int size, access;
};
