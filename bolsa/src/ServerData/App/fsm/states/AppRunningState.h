#pragma once

#include "ServerData/App/fsm/AppStateAdapter.h"

struct AppRunningState : public AppStateAdapter {
	AppState getState() override;

	AppRunningState(App* app, AppContext* context);

	bool pause(int n) override;

private:

};