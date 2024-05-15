#include "pch/so2pch.h"

#include "PipeThread.h"

DWORD WINAPI threadFunction(LPVOID lpParam) {
	LOG_DEBUG("PipeThread criada!");
	PipeThread& data = *(PipeThread*) lpParam;
	App& context = *(App*)data.getData();

	WindowsMutex mutex(APP_MUTEX);

	while (data.running()) {
	}

	return 0;
}

PipeThread* PipeThread::createThread(App& app) {
	return new PipeThread(app);
}

PipeThread::PipeThread(App& app) : WindowsThread(&app, threadFunction) {}

PipeThread::~PipeThread() {}