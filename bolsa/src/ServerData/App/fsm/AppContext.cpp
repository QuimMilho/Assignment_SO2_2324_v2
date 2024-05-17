#include "pch/so2pch.h"

#include "AppContext.h"
#include "ServerData/App/fsm/states/AppLoadingState.h"
#include "ServerData/App/fsm/states/AppRunningState.h"
#include "ServerData/App/fsm/states/AppPausedState.h"

AppContext * AppContext::instance = nullptr;

AppContext* AppContext::getInstance() {
	return instance;
}

AppContext::AppContext() : app(App()), running(true) {
	instance = this;
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
		return new AppLoadingState(&app, this);
	case AppState::RUNNING:
		return new AppRunningState(&app, this);
	case AppState::PAUSED:
		return new AppPausedState(&app, this);
	default:
		return nullptr;
	}
}

void AppContext::addUsers(const _TSTRING& fileName) {
	atual->addUsers(fileName);
}

int AppContext::addCompanies(const _TSTRING& fileName) {
	return atual->addCompany(fileName);
}

int AppContext::addCompanies(const _TSTRING& companyName, const int total_shares, const double share_price) {
	return atual->addCompany(companyName, total_shares, share_price);
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

bool AppContext::close() {
	running = false;
	return atual->close();
}

bool AppContext::update() {
	return atual->update();
}

bool AppContext::updateBoard(WindowsSharedMemory& memory) {
	return atual->updateBoard(memory);
}

App& AppContext::getApp() {
	return app;
}

bool AppContext::isRunning() const {
	return running;
}