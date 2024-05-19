#pragma once

#include "dynamicLib.h"

#include "ServerData/ServerData.h"

struct SinglePipeThreadData {
	App& app;
	HANDLE namedPipe;
};

struct SinglePipeThread : public WindowsThread {
	[[nodiscard]] static SinglePipeThread* createThread(SinglePipeThreadData& data);
	virtual ~SinglePipeThread();

	DWORD WINAPI function(LPVOID lpParam) override;

private:
	SinglePipeThread(SinglePipeThreadData& data);
};