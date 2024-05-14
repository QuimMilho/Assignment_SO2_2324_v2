#include "pch/so2pch.h"

#include "dynamicLib.h"
#include "ServerData/ServerData.h"
#include "ui/AppUI.h"

int _tmain(int argc, TCHAR** argv) {
	DEFINE_UNICODE;

	AppContext app;
	AppUI appUI(app);
	appUI.start();

	return 0;
}