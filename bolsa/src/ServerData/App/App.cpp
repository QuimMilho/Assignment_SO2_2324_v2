#include "pch/so2pch.h"

#include "App.h"
#include "commands/Command.h"
#include "threads/Threads.h"

#define KEY_PATH _T("Software\\BolsaApp")
#define KEY_NAME _T("BolsaValoresSettings")
#define KEY_VALUE _T("NCLIENTES")

App::App() : timePaused(0), nClientes(0), updatedCompanies(false), randomGenerator(), ultimaEmpresa() {
	Command::registerCommands();
	std::unique_ptr<WindowsRegistryKey> key = std::unique_ptr<WindowsRegistryKey>(
			WindowsRegistryKey::openKey(KEY_PATH, KEY_NAME, KEY_VALUE, 5, KEY_READ));
	if (!key) {
		LOG_ERRO("Erro ao abrir chave do NCLIENTES!");
		return;
	}
	int n = key->readInt();
	LOG_DEBUG("Obtido valor %d da chave NCLIENTES!", n);
	nClientes = n;
}

bool App::setCompanyPrice(const _TSTRING& cName, double new_price) {
	if (new_price < 0.001)
		return false;
	Company& c = findCompany(cName);
	c.setPrice(new_price);
	ultimaEmpresa = c.getName();
	updatedCompanies = true;
	return true;
}

bool App::setCompanyPrice(Company& c, double new_price) {
	if (new_price < 0.001)
		return false;
	c.setPrice(new_price);
	ultimaEmpresa = c.getName();
	updatedCompanies = true;
	return true;
}

bool App::addUser(const _TSTRING& name, const _TSTRING& password, const double balance) {
	try {
		User& u = this->findUser(name);
		LOG_ERRO("Já existe um utilizador com esse nome! %s", name.c_str());
		return false;
	} catch (UserNotFound& e) {
		if (balance < 0)
			return false;
		users.push_back(User(name, password, balance));
		return true;
	}
}

bool App::addCompany(const _TSTRING& name, const int n_shares, const double share_price) {
	try {
		Company& c = this->findCompany(name);
		LOG_ERRO("Já existe uma empresa com esse nome! %s", name.c_str());
		return false;
	} catch (CompanyNotFound& e) {
		if (n_shares < 100) {
			LOG_ERRO(_T("A empresa deve ter mais de 100 ações!"));
			return false;
		}
		if (share_price < 0.001) {
			LOG_ERRO(_T("O preço das ações deve ser superior a 0.001!"));
			return false;
		}
		companies.push_back(Company(name, n_shares, share_price));
		ultimaEmpresa = name;
		updatedCompanies = true;
		return true;
	}
}

User& App::findUser(_TSTRING username) {
	for (auto& u : users) 
		if (u.getName() == username) 
			return u;
	throw UserNotFound(username);
}

Company& App::findCompany(_TSTRING companyName) {
	for (auto& c : companies)
		if (c.getName() == companyName)
			return c;
	throw CompanyNotFound(companyName);
}

int App::nUsers() const {
	return users.size();
}

int App::nCompanies() const {
	return companies.size();
}

void App::readUsers(_TIFSTREAM& file) {
	_TSTRING str;
	int i = 0;

	while (std::getline(file, str)) {
		i++;

		_TSTRINGSTREAM ss(str);
		_TSTRING user, pass;
		double balance;

		if (ss >> user >> pass >> balance) {
			LOG_INFO("Adicionado utilizador com dados: %s %s %lf", user.c_str(), pass.c_str(), balance);
			if (!this->addUser(user, pass, balance)) {
				LOG_ERRO(_T("Ocorreu um erro ao ler um utilizador na linha %d!"), i);
			}
		} else {
			LOG_ERRO("Ocorreu um erro ao ler um dos utilizadores. Linha: %d", i);
		}
	}

	LOG_DEBUG("Lidos %d utilizadores em %d linhas.", users.size(), i);
}

bool App::pause(long n) {
	if (n <= 0)
		return false;
	timePaused = n * 10;
	return true;
}

bool App::resume() {
	timePaused--;
	if (timePaused <= 0)
		return true;
	return false;
}

int App::checkStock() {
	int n = 0;

	return 0;
}

int App::checkStock(_TSTRING companyName) {
	int n = 0;

	return 0;
}

void App::startThreads() {
	pipeThread = std::unique_ptr<WindowsThread>(PipeThread::createThread(*this));
	timerThread = std::unique_ptr<WindowsThread>(TimerThread::createThread(*AppContext::getInstance()));
}

void App::stopThreads() {
	LOG_DEBUG(_T("Closing threads!"));
	pipeThread->stop();
	timerThread->stop();
	Sleep(1000);
	LOG_DEBUG(_T("Threads closed!"));
}

bool App::update() {
	bool upd = false;
	for (Company& c : companies) {
		if (randomGenerator.random(100) < COMPANY_UPDATE_CHANCE) {
			int r = randomGenerator.random(-MAX_COMPANY_UPDATE, MAX_COMPANY_UPDATE);
			double d = c.getSharedPrice() * (r / (double) COMPANY_UPDATE_UNIT + 1);
			LOG_INFO(_T("A atualizar valor de empresa %s de %lf para %lf"), c.getName().c_str(), 
					c.getSharedPrice(), d);
			if (setCompanyPrice(c, d))
				upd = true;
		}
	}
	if (upd)
		updatedCompanies = true;
	return upd;
}

bool App::updateBoard(WindowsSharedMemory& memory) {
	if (updatedCompanies) {
		BoardData data;
		_TSTRCPY_S(data.ultimaEmpresa, MAX_STRING - 1, ultimaEmpresa.c_str());
		getBestCompanies(data.companies);
		LOG_INFO("Melhores empresas encontradas!");
		data.nCompanies = companies.size() > 10 ? 10 : companies.size();
		memory.write(&data);
		updatedCompanies = false;
		return true;
	}
	return false;
}

int App::getBestCompanies(SharedCompany * comps) {
	memset(comps, 0, sizeof(SharedCompany) * 10);
	for (int i = 0; i < companies.size(); i++) {
		Company& c = companies.at(i);
		int p = findCompanySpot(c, comps);
		if (p < 0) {
			continue;
		}
		if (comps[p].share_price == 0) {
			c >> comps[p];
		} else {
			for (int h = 9; h > p; h--) 
				memcpy(&comps[h], &comps[h - 1], sizeof(SharedCompany));
			c >> comps[p];
		}
	}
	for (int i = 0; i < 10; i++)
		_TCOUT << comps[i].nome << _TENDL;
	return 0;
}

int App::findCompanySpot(Company& c, SharedCompany* comps) {
	for (int i = 0; i < 10; i++) {
		if (comps[i].share_price == 0)
			return i;
		if (comps[i].share_price < c.getSharedPrice())
			return i;
	}
	return -1;
}

Company* App::getCompanies() {
	return companies.data();
}

User* App::getUsers() {
	return users.data();
}