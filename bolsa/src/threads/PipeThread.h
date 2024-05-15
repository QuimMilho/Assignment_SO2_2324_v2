#pragma once

#include "dynamicLib.h"
#include "ServerData/ServerData.h"

struct PipeThread : public WindowsThread {
	static PipeThread* createThread(App& app);
	virtual ~PipeThread();

private:
	PipeThread(App& app);

};