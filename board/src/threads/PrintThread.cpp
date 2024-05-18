#include "pch/so2pch.h"

#include "PrintThread.h"

PrintThread::PrintThread() : WindowsThread(NULL) {}

PrintThread::~PrintThread() {}

DWORD WINAPI PrintThread::function(LPVOID lpParam) {
	TCHAR c = _TGETCHAR();
	return (int) c;
}

PrintThread* PrintThread::createThread() {
	return new PrintThread();
}