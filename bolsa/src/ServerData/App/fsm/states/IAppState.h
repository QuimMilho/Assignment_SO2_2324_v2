#pragma once

#include "dynamicLib.h"
#include "ServerData/App/fsm/AppState.h"

struct IAppState {
	virtual AppState getState() = 0;

	virtual int addUsers(const _TSTRING& fileName) = 0;
	virtual int addCompany() = 0;

	virtual bool resume() = 0;
	virtual bool pause(int n) = 0;

	virtual bool update() = 0;
	virtual bool updateBoard() = 0;

	virtual bool buy(const _TSTRING& username, const _TSTRING& companyName, const int nShares, 
			const double sharePrice) = 0;
	virtual bool sell(const _TSTRING& username, const _TSTRING& companyName, const int nShares,
			const double sharePrice) = 0;
};