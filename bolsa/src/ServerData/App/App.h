#pragma once

#include "pch/so2pch.h"
#include "dynamicLib.h"

#include "ServerData/Company/Company.h"
#include "ServerData/User/User.h"

#define APP_MUTEX _T("BolsaAppMutex")

struct App {
	App();

	[[nodiscard]] bool addUser(const _TSTRING& name, const _TSTRING& password, const double balance);
	[[nodiscard]] bool addCompany(const _TSTRING& name, const int n_shares, const double share_price);

	[[nodiscard]] User& findUser(_TSTRING username);
	[[nodiscard]] Company& findCompany(_TSTRING companyName);

	[[nodiscard]] int nUsers() const;
	[[nodiscard]] int nCompanies() const;

	[[nodiscard]] bool pause(long n);
	[[nodiscard]] bool resume();

	[[nodiscard]] int checkStock();
	[[nodiscard]] int checkStock(_TSTRING companyName);

	bool update();
	bool updateBoard(WindowsSharedMemory& memory);
	int getBestCompanies(SharedCompany* comps);

	void startThreads();
	void stopThreads();

	void readUsers(_TIFSTREAM& file);
	Company* getCompanies();

private:
	int findCompanySpot(Company& c, SharedCompany* comps);

	std::vector<User> users;
	std::vector<Company> companies;

	std::unique_ptr<WindowsThread> pipeThread;
	std::unique_ptr<WindowsThread> timerThread;

	bool updatedCompanies;
	int nClientes;
	long timePaused;
};
