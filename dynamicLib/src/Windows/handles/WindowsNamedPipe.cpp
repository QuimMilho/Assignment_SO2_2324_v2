#include "pch/so2pch.h"

#include "WindowsNamedPipe.h"

WindowsNamedPipe::WindowsNamedPipe(const _TSTRING& name, const int bufferSize, const int defaultTimeout) : 
		WindowsHandle(NULL), size(bufferSize), defaultTimeout(defaultTimeout) {}

WindowsNamedPipe::~WindowsNamedPipe() {}

bool WindowsNamedPipe::create() {
	handle = CreateNamedPipe(name.c_str(), PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE,
			PIPE_UNLIMITED_INSTANCES, size, size, defaultTimeout, NULL);
	if (handle == NULL) 
		return false;
	return true;
}

bool WindowsNamedPipe::open() {
	handle = CreateFile(name.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (handle == NULL)
		return false;
	return true;
}

void WindowsNamedPipe::terminate() {
	FlushFileBuffers(handle);
	DisconnectNamedPipe(handle);
}

int WindowsNamedPipe::write(void * e, const int size) {
	DWORD bytesWriten = 0;
	if (WriteFile(handle, e, size, &bytesWriten, NULL)) {
		error = GetLastError();
		LOG_ERRO(_T("Erro ao escrever no Named Pipe!"));
		return 0;
	}
	LOG_INFO(_T("Foram escritos %d bytes!"), bytesWriten);
	return bytesWriten;
}

int WindowsNamedPipe::read(void * e, const int size) {
	DWORD bytesRead = 0;
	if (ReadFile(handle, e, size, &bytesRead, NULL)) {
		error = GetLastError();
		LOG_ERRO(_T("Erro ao ler do Named Pipe!"));
		return 0;
	}
	LOG_INFO(_T("Foram lidos %d bytes!"), bytesRead);
	return bytesRead;
}

int WindowsNamedPipe::write(HANDLE h, void* e, const int size) {
	DWORD bytesWriten = 0;
	if (WriteFile(h, e, size, &bytesWriten, NULL)) {
		LOG_ERRO(_T("Erro ao escrever no Named Pipe!"));
		return 0;
	}
	LOG_INFO(_T("Foram escritos %d bytes!"), bytesWriten);
	return bytesWriten;
}

int WindowsNamedPipe::read(HANDLE h, void* e, const int size) {
	DWORD bytesRead = 0;
	if (ReadFile(h, e, size, &bytesRead, NULL)) {
		LOG_ERRO(_T("Erro ao ler do Named Pipe!"));
		return 0;
	}
	LOG_INFO(_T("Foram lidos %d bytes!"), bytesRead);
	return bytesRead;
}