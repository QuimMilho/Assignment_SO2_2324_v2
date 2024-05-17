#pragma once

#include "dynamicLib.h"
#include "ServerData/ServerData.h"

struct TimerThread : public WindowsThread {
	[[nodiscard]] static TimerThread* createThread(AppContext& app);
	virtual ~TimerThread();

	DWORD WINAPI function(LPVOID lpParam) override;

private:
	TimerThread(AppContext& app);

};