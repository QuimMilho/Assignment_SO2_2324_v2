#include "pch/so2pch.h"

#include "WindowsThread.h"

DWORD WINAPI threadFunction(LPVOID lpParam) {
	LOG_INFO(_T("Thread iniciada!"));
	WindowsThread* t = (WindowsThread *) lpParam;
	int r = t->function(lpParam);
	LOG_INFO(_T("Thread terminada! Saída: %d"), r);
	return r;
}

WindowsThread::WindowsThread(void* threadData) : WindowsHandle(
		CreateThread(NULL, 0, threadFunction, this, 0, &threadId)), isPaused(false), isRunning(true),
		data(threadData) {}

WindowsThread::~WindowsThread() {}

bool WindowsThread::running() const {
	return isRunning;
}

bool WindowsThread::paused() const {
	return isPaused;
}

void WindowsThread::stop() {
	isRunning = false;
}

int WindowsThread::pause() {
	if (isPaused)
		return -1;
	isPaused = true;
	return SuspendThread(handle);
}

int WindowsThread::resume() {
	if (!isPaused)
		return -1;
	isPaused = false;
	return ResumeThread(handle);
}

void* WindowsThread::getData() {
	return data;
}