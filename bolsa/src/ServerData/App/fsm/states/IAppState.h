#pragma once

#include "dynamicLib.h"
#include "ServerData/App/fsm/AppState.h"

struct IAppState {
	[[nodiscard]] virtual AppState getState() = 0;

	[[nodiscard]] virtual int addUsers(const _TSTRING& fileName) = 0;
	[[nodiscard]] virtual int addCompany(const _TSTRING& fileName) = 0;
	[[nodiscard]] virtual int addCompany(const _TSTRING& companyName, const int total_shares, const double share_price) = 0;

	[[nodiscard]] virtual bool resume() = 0;
	[[nodiscard]] virtual bool pause(int n) = 0;

	[[nodiscard]] virtual bool update() = 0;
	[[nodiscard]] virtual bool updateBoard(WindowsSharedMemory& memory) = 0;

	[[nodiscard]] virtual bool buy(const _TSTRING& username, const _TSTRING& companyName, const int nShares,
			const double sharePrice) = 0;
	[[nodiscard]] virtual bool sell(const _TSTRING& username, const _TSTRING& companyName, const int nShares,
			const double sharePrice) = 0;

	[[nodiscard]] virtual bool close() = 0;
};