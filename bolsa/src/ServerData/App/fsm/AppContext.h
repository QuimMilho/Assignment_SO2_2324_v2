#pragma once

#include "pch/so2pch.h"

#include "ServerData/App/App.h"
#include "ServerData/App/fsm/AppState.h"
#include "ServerData/App/fsm/states/IAppState.h"

struct AppContext {
	AppContext();
	void changeState(AppState newState);

	void addUsers(const _TSTRING& fileName);

	[[nodiscard]] AppState getState() const;

	[[nodiscard]] bool pause(int n);
	[[nodiscard]] bool resume();

private:
	std::unique_ptr<IAppState> atual;
	std::unique_ptr<App> app;

	IAppState* getInstance(AppState newState);
};