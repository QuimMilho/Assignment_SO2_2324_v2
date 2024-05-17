#pragma once

#include "pch/so2pch.h"

#include "ServerData/App/App.h"
#include "ServerData/App/fsm/AppState.h"
#include "ServerData/App/fsm/states/IAppState.h"

struct AppContext {
	AppContext();
	void changeState(AppState newState);

	void addUsers(const _TSTRING& fileName);
	int addCompanies(const _TSTRING& fileName);
	int addCompanies(const _TSTRING& companyName, const int total_shares, const double share_price);

	[[nodiscard]] AppState getState() const;

	[[nodiscard]] bool pause(int n);
	[[nodiscard]] bool resume();

	bool update();
	bool updateBoard(WindowsSharedMemory& memory);

	static AppContext* getInstance();
	bool close();

	App& getApp();
	bool isRunning() const;

private:
	static AppContext* instance;

	std::unique_ptr<IAppState> atual;
	App app;

	bool running;

	IAppState* getInstance(AppState newState);
};