#include "pch/so2pch.h"

#include "AppRunningState.h"

AppRunningState::AppRunningState(App* app, AppContext* context) : AppStateAdapter(app, context) {}

AppState AppRunningState::getState() {
	return AppState::RUNNING;
}

bool AppRunningState::pause(int n) {
	if (data->pause(n)) {
		context->changeState(AppState::PAUSED);
		return true;
	}
	return false;
}