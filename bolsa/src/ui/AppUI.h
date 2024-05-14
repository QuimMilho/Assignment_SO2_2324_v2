#pragma once

#include "pch/so2pch.h"
#include "ServerData/ServerData.h"

struct AppUI {
	AppUI(AppContext& app);

	void start();

private:
	AppContext& app;

	[[nodiscard]] int loadingUI();
	[[nodiscard]] int commandUI();
	void printError(const int err);
};