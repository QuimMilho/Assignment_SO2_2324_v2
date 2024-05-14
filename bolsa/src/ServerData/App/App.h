#pragma once

#include "pch/so2pch.h"
#include "dynamicLib.h"

#include "ServerData/Company/Company.h"
#include "ServerData/User/User.h"

struct App {
	App();

	[[nodiscard]] bool addUser(const _TSTRING& name, const _TSTRING& password, const double balance);
	[[nodiscard]] bool addCompany(const _TSTRING& name, const int n_shares, const double share_price);

	[[nodiscard]] User& findUser(_TSTRING username);
	[[nodiscard]] Company& findCompany(_TSTRING companyName);

	[[nodiscard]] int nUsers() const;
	[[nodiscard]] int nCompanies() const;

	[[nodiscard]] bool pause(int n);
	[[nodiscard]] bool resume();

	[[nodiscard]] int checkStock();
	[[nodiscard]] int checkStock(_TSTRING companyName);

	void readUsers(_TIFSTREAM& file);

private:
	std::vector<std::unique_ptr<User>> users;
	std::vector<std::unique_ptr<Company>> companies;

	int timePaused, nClientes;
};
