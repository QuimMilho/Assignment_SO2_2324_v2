#pragma once

#include "dynamicLib.h"

#include "ServerData/Wallet/Wallet.h"

struct User {
	User(const _TSTRING& name, const _TSTRING& password, const double balance);

	[[nodiscard]] _TSTRING getName() const;

private:
	_TSTRING username, password;
	double balance;
	std::vector<Wallet> wallet;
};