#pragma once

#include "ServerData/App/fsm/AppStateAdapter.h"

struct AppLoadingState : public AppStateAdapter {
	AppState getState() override;
	
	AppLoadingState(App* app, AppContext* context);

	[[nodiscard]] int addUsers(const _TSTRING& fileName) override;

private:

};