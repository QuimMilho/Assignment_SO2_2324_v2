#pragma once

#include "ServerData/App/fsm/AppStateAdapter.h"

struct AppRunningState : public AppStateAdapter {
	AppState getState() override;

	AppRunningState(App* app, AppContext* context);

	[[nodiscard]] bool pause(int n) override;
	[[nodiscard]] int addCompany(const _TSTRING& fileName) override;
	[[nodiscard]] int addCompany(const _TSTRING& companyName, const int total_shares, const double share_price) override;

	[[nodiscard]] bool update() override;
	[[nodiscard]] bool updateBoard(WindowsSharedMemory& memory) override;

	bool close() override;

private:

};