#pragma once

#include "ServerData/App/App.h"
#include "ServerData/App/fsm/AppContext.h"
#include "ServerData/App/fsm/states/IAppState.h"

struct AppStateAdapter : public IAppState {
	[[nodiscard]] int addUsers(const _TSTRING& fileName) override;
	[[nodiscard]] int addCompany() override;

	[[nodiscard]] bool resume() override;
	[[nodiscard]] bool pause(int n) override;

	[[nodiscard]] bool update() override;
	[[nodiscard]] bool updateBoard() override;

	[[nodiscard]] bool buy(const _TSTRING& username, const _TSTRING& companyName, const int nShares,
			const double sharePrice) override;

	[[nodiscard]] bool sell(const _TSTRING& username, const _TSTRING& companyName, const int nShares,
			const double sharePrice) override;

protected:
	AppStateAdapter(App* data, AppContext* context);

	AppContext* context;
	App* data;
};