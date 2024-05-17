#include "pch/so2pch.h"

#include "AppPausedState.h"

AppPausedState::AppPausedState(App* app, AppContext* context) : AppStateAdapter(app, context) {}

AppState AppPausedState::getState() {
	return AppState::PAUSED;
}

bool AppPausedState::resume() {
	if (data->resume()) {
		int n = data->checkStock();
		LOG_DEBUG("App will resume. There were made %d sales!", n);
		context->changeState(AppState::RUNNING);
		return true;
	}
	return false;
}

bool AppPausedState::close() {
	data->stopThreads();
	return true;
}

int AppPausedState::addCompany(const _TSTRING& fileName) {
	return -1;
}

int AppPausedState::addCompany(const _TSTRING& companyName, const int total_shares, const double share_price) {
	return -1;
}