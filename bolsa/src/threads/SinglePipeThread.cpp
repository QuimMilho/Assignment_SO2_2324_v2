#include "pch/so2pch.h"

#include "SinglePipeThread.h"



SinglePipeThread::SinglePipeThread(SinglePipeThreadData& data) : WindowsThread(&data) {}

SinglePipeThread::~SinglePipeThread() {}

DWORD WINAPI SinglePipeThread::function(LPVOID lpParam) {
	User* u;
	SinglePipeThreadData& data = *(SinglePipeThreadData*)lpParam;
	WindowsMutex mutex(APP_ACCESS_MUTEX);
	
	while (1) {

	}
}

SinglePipeThread* SinglePipeThread::createThread(SinglePipeThreadData& data) {
	return new SinglePipeThread(data);
}