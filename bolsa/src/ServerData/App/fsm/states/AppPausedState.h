#pragma once

#include "ServerData/App/fsm/AppStateAdapter.h"

struct AppPausedState : public AppStateAdapter {
	AppState getState() override;

	AppPausedState(App* app, AppContext* context);

	int addCompany(const _TSTRING& fileName) override;
	int addCompany(const _TSTRING& companyName, const int total_shares, const double share_price) override;

	bool resume() override;
	bool close() override;

private:

};