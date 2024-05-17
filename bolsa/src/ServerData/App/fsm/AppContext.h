#pragma once

#include "pch/so2pch.h"

#include "ServerData/App/App.h"
#include "ServerData/App/fsm/AppState.h"
#include "ServerData/App/fsm/states/IAppState.h"

struct AppContext {
	AppContext();
	void changeState(AppState newState);

	void addUsers(const _TSTRING& fileName);
	[[nodiscard]] int addCompanies(const _TSTRING& fileName);
	[[nodiscard]] int addCompanies(const _TSTRING& companyName, const int total_shares, const double share_price);

	[[nodiscard]] AppState getState() const;

	[[nodiscard]] bool pause(int n);
	[[nodiscard]] bool resume();

	[[nodiscard]] bool update();
	[[nodiscard]] bool updateBoard(WindowsSharedMemory& memory);

	[[nodiscard]] static AppContext* getInstance();
	[[nodiscard]] bool close();

	[[nodiscard]] App& getApp();
	[[nodiscard]] bool isRunning() const;

private:
	static AppContext* instance;

	std::unique_ptr<IAppState> atual;
	App app;

	bool running;

	[[nodiscard]] IAppState* getInstance(AppState newState);
};