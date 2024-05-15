#pragma once

#include "dynamicLib.h"
#include "ServerData/ServerData.h"

struct TimerThread : public WindowsThread {
	static TimerThread* createThread(AppContext& app);
	virtual ~TimerThread();

private:
	TimerThread(AppContext& app);

};