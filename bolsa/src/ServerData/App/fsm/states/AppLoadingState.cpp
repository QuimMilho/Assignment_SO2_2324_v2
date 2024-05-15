#include "pch/so2pch.h"

#include "AppLoadingState.h"

AppLoadingState::AppLoadingState(App* data, AppContext* context) : AppStateAdapter(data, context) {}

AppState AppLoadingState::getState() {
	return AppState::LOADING;
}

int AppLoadingState::addUsers(const _TSTRING& fileName) {
	_TIFSTREAM file(fileName);
	int n;

	if (!file.is_open()) {
		LOG_ERRO("O ficheiro \"%s\" não existe!", fileName.c_str());
		return 0;
	}

	LOG_INFO("Ficheiro aberto!");

	SET_FILE_UTF8(file);

	data->readUsers(file);
	n = data->nUsers();

	LOG_DEBUG("Foram lidos %d utilizadores!", n)

	data->startThreads();

	if (n)
		context->changeState(AppState::RUNNING);

	return n;
}