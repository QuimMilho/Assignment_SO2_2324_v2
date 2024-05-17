#pragma once

#include "ServerData/App/fsm/AppStateAdapter.h"

struct AppPausedState : public AppStateAdapter {
	AppState getState() override;

	AppPausedState(App* app, AppContext* context);

	[[nodiscard]] int addCompany(const _TSTRING& fileName) override;
	[[nodiscard]] int addCompany(const _TSTRING& companyName, const int total_shares, const double share_price) override;

	[[nodiscard]] bool resume() override;
	[[nodiscard]] bool close() override;

private:

};