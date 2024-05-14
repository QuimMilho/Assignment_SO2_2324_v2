#include "pch/so2pch.h"

#include "AppStateAdapter.h"

AppStateAdapter::AppStateAdapter(App* data, AppContext* context) : data(data), context(context) {}

int AppStateAdapter::addUsers(const _TSTRING& fileName) {
	return 0;
}

int AppStateAdapter::addCompany() {
	return 0;
}

bool AppStateAdapter::resume() {
	return false;
}

bool AppStateAdapter::pause(int n) {
	return false;
}