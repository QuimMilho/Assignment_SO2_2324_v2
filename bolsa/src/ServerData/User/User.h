#pragma once

#include "dynamicLib.h"

#include "ServerData/Wallet/Wallet.h"

struct User {
	User(const _TSTRING& name, const _TSTRING& password, const double balance);

	[[nodiscard]] _TSTRING getName() const;

	friend _TOSTREAM& operator << (_TOSTREAM& o, User& c);

private:
	_TSTRING username, password;
	double balance;
	bool loggedIn;
	std::vector<Wallet> wallet;
};