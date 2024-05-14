#pragma once

#include "ServerData/App/fsm/AppStateAdapter.h"

struct AppPausedState : public AppStateAdapter {
	AppState getState() override;

	AppPausedState(App* app, AppContext* context);

	bool resume() override;

private:

};