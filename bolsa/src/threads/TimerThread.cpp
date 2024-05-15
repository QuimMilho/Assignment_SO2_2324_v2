#include "pch/so2pch.h"

#include "TimerThread.h"

DWORD WINAPI threadFunction(LPVOID lpParam) {
	LOG_DEBUG("TimerThread criada!");
	TimerThread& data = *(TimerThread*)lpParam;
	AppContext& context = *(AppContext*) data.getData();

	WindowsMutex mutex(APP_MUTEX);

	while (data.running()) {

	}

	return 0;
}

TimerThread * TimerThread::createThread(AppContext& app) {
	return new TimerThread(app);
}

TimerThread::TimerThread(AppContext& app) : WindowsThread(&app, threadFunction) {}

TimerThread::~TimerThread() {}