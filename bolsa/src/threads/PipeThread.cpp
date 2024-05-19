#include "pch/so2pch.h"

#include "PipeThread.h"
#include "SinglePipeThread.h"

DWORD WINAPI PipeThread::function(LPVOID lpParam) {
	LOG_DEBUG("PipeThread criada!");
	PipeThread& data = *(PipeThread*) lpParam;
	App& context = *(App*)data.getData();

	while (data.running()) {

	}

	return 0;
}

PipeThread* PipeThread::createThread(App& app) {
	return new PipeThread(app);
}

PipeThread::PipeThread(App& app) : WindowsThread(&app) {}

PipeThread::~PipeThread() {}
