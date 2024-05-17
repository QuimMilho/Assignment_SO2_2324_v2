#pragma once

#include "dynamicLib.h"
#include "ServerData/ServerData.h"

struct PipeThread : public WindowsThread {
	[[nodiscard]] static PipeThread* createThread(App& app);
	virtual ~PipeThread();

	DWORD WINAPI function(LPVOID lpParam) override;

private:
	PipeThread(App& app);

};