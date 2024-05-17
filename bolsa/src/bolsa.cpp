#include "pch/so2pch.h"

#include "dynamicLib.h"
#include "ServerData/ServerData.h"
#include "ui/AppUI.h"

#define APP_RUNNING_MUTEX _T("AppRunningMutex")

int _tmain(int argc, TCHAR** argv) {
	DEFINE_UNICODE;

	WindowsMutex mutex(APP_RUNNING_MUTEX);
	if (mutex.wait(0) != WAIT_OBJECT_0) {
		_TCOUT << _T("Já existe um programa bolsa em execução!") << _TENDL;
		return -1;
	}

	AppContext app;
	AppUI appUI(app);
	appUI.start();

	mutex.release();

	return 0;
}