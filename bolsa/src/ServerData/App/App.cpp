#include "pch/so2pch.h"

#include "App.h"
#include "commands/Command.h"
#include "threads/Threads.h"

#define KEY_PATH _T("Software\\BolsaApp")
#define KEY_NAME _T("BolsaValoresSettings")
#define KEY_VALUE _T("NCLIENTES")

App::App() : timePaused(0), nClientes(0), updated(false) {
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

bool App::addUser(const _TSTRING& name, const _TSTRING& password, const double balance) {
	try {
		User& u = this->findUser(name);
		LOG_ERRO("Já existe um utilizador com esse nome! %s", name.c_str());
		return false;
	} catch (UserNotFound& e) {
		users.push_back(std::unique_ptr<User>(new User(name, password, balance)));
		return true;
	}
}

bool App::addCompany(const _TSTRING& name, const int n_shares, const double share_price) {
	try {
		Company& c = this->findCompany(name);
		LOG_ERRO("Já existe uma empresa com esse nome! %s", name.c_str());
		return false;
	} catch (CompanyNotFound& e) {
		companies.push_back(std::unique_ptr<Company>(new Company(name, n_shares, share_price)));
		return true;
	}
}

User& App::findUser(_TSTRING username) {
	for (auto& u : users) 
		if (u->getName() == username) 
			return *u.get();
	throw UserNotFound(username);
}

Company& App::findCompany(_TSTRING companyName) {
	for (auto& c : companies)
		if (c->getName() == companyName)
			return *c.get();
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
			this->addUser(user, pass, balance);
		} else {
			LOG_ERRO("Ocorreu um erro ao ler um dos utilizadores. Linha: %d", i);
		}
	}

	LOG_DEBUG("Lidos %d utilizadores em %d linhas.", users.size(), i);
}

bool App::pause(long n) {
	if (n <= 0)
		return false;
	timePaused = n;
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
	timerThread = std::unique_ptr<WindowsThread>(TimerThread::createThread(*this));
}

void App::stopThreads() {
	pipeThread->stop();
	timerThread->stop();
}

bool App::update() {

}

bool App::updateBoard() {
	SharedCompany comps[10];
	getBestCompanies(comps);

}

int App::getBestCompanies(SharedCompany * comps) {
	
	return 0;
}