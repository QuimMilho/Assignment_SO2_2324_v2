#pragma once

#include "ServerData/App/App.h"
#include "ServerData/App/fsm/AppContext.h"
#include "ServerData/App/fsm/states/IAppState.h"

struct AppStateAdapter : public IAppState {
	[[nodiscard]] int addUsers(const _TSTRING& fileName) override;
	[[nodiscard]] int addCompany() override;

	[[nodiscard]] bool resume() override;
	[[nodiscard]] bool pause(int n) override;

protected:
	AppStateAdapter(App* data, AppContext* context);

	AppContext* context;
	App* data;
};