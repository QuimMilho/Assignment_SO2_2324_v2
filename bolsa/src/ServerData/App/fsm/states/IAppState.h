#pragma once

#include "ServerData/App/fsm/AppState.h"

struct IAppState {
	virtual AppState getState() = 0;

	virtual int addUsers(const _TSTRING& fileName) = 0;
	virtual int addCompany() = 0;

	virtual bool resume() = 0;
	virtual bool pause(int n) = 0;
};