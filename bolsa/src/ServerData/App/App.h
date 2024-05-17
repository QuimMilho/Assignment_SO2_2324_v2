#pragma once

#include "pch/so2pch.h"
#include "dynamicLib.h"

#include "ServerData/Company/Company.h"
#include "ServerData/User/User.h"

#define APP_ACCESS_MUTEX _T("BolsaAppMutex")

#define MAX_COMPANY_UPDATE 50
#define COMPANY_UPDATE_UNIT 1000
#define COMPANY_UPDATE_CHANCE 10

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

	[[nodiscard]] bool update();
	[[nodiscard]] bool updateBoard(WindowsSharedMemory& memory);
	[[nodiscard]] int getBestCompanies(SharedCompany* comps);

	void startThreads();
	void stopThreads();

	[[nodiscard]] bool setCompanyPrice(const _TSTRING& cName, double new_price);
	[[nodiscard]] bool setCompanyPrice(Company& c, double new_price);

	void readUsers(_TIFSTREAM& file);
	[[nodiscard]] Company* getCompanies();
	[[nodiscard]] User* getUsers();

private:
	[[nodiscard]] int findCompanySpot(Company& c, SharedCompany* comps);

	std::vector<User> users;
	std::vector<Company> companies;

	std::unique_ptr<WindowsThread> pipeThread;
	std::unique_ptr<WindowsThread> timerThread;

	Random randomGenerator;

	bool updatedCompanies;
	int nClientes;
	long timePaused;
	_TSTRING ultimaEmpresa;
};
