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

bool AppStateAdapter::update() {
	return false;
}

bool AppStateAdapter::updateBoard() {
	return false;
}

bool AppStateAdapter::buy(const _TSTRING& username, const _TSTRING& companyName, const int nShares,
		const double sharePrice) {
	return false;
}

bool AppStateAdapter::sell(const _TSTRING& username, const _TSTRING& companyName, const int nShares,
		const double sharePrice) {
	return false;
}