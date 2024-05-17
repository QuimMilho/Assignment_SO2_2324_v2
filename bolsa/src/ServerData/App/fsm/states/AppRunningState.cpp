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

int AppRunningState::addCompany(const _TSTRING& fileName) {
	_TIFSTREAM file(fileName);
	_TSTRING str, companyName;
	int line = 0, total = 0, totalShares;
	double share_price;

	if (!file.is_open()) {
		return -2;
	}

	SET_FILE_UTF8(file);

	while (std::getline(file, str)) {
		line++;
		_TSTRINGSTREAM ss(str);

		if (ss >> companyName >> totalShares >> share_price) {
			if (data->addCompany(companyName, totalShares, share_price))
				total++;
			else
				LOG_ERRO(_T("Ocorreu um erro ao ler a empresa na linha %d!"), line);
		} else {
			LOG_ERRO(_T("Algum dos valores da empresa na linha %d não é válido!"), line);
		}
	}

	return total;
}

int AppRunningState::addCompany(const _TSTRING& companyName, const int total_shares, const double share_price) {
	if (data->addCompany(companyName, total_shares, share_price))
		return 1;
	return 0;
}

bool AppRunningState::close() {
	data->stopThreads();
	return true;
}

bool AppRunningState::update() {
	return false;
}

bool AppRunningState::updateBoard(WindowsSharedMemory& memory) {
	if (data->updateBoard(memory))
		return true;
	return false;
}