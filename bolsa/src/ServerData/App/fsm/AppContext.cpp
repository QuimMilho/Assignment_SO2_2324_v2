#include "pch/so2pch.h"

#include "AppContext.h"
#include "ServerData/App/fsm/states/AppLoadingState.h"
#include "ServerData/App/fsm/states/AppRunningState.h"
#include "ServerData/App/fsm/states/AppPausedState.h"

AppContext::AppContext() {
	this->app = std::unique_ptr<App>(new App());
	changeState(AppState::LOADING);
}

void AppContext::changeState(AppState newState) {
	IAppState * state = getInstance(newState);
	if (!state) {
		LOG_ERRO("Ocorreu um erro ao mudar de estado! Novo estado: %d.", newState);
		return;
	}
	this->atual = std::unique_ptr<IAppState>(state);
	LOG_INFO("Estado mudado para %d.", newState);
}

IAppState* AppContext::getInstance(AppState newState) {
	switch (newState) {
	case AppState::LOADING:
		return new AppLoadingState(app.get(), this);
	case AppState::PAUSED:
		return new AppRunningState(app.get(), this);
	case AppState::RUNNING:
		return new AppPausedState(app.get(), this);
	default:
		return nullptr;
	}
}

void AppContext::addUsers(const _TSTRING& fileName) {
	atual->addUsers(fileName);
}

AppState AppContext::getState() const {
	return atual->getState();
}

bool AppContext::pause(int n) {
	return atual->pause(n);
}

bool AppContext::resume() {
	return atual->resume();
}