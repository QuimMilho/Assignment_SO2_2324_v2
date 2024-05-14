#include "pch/so2pch.h"

#include "AppUI.h"
#include "commands/Command.h"

AppUI::AppUI(AppContext& app) : app(app) {}

void AppUI::start() {
	int exit = 0;
	while (!exit) {
		switch (app.getState()) {
		case AppState::LOADING:
			exit = loadingUI();
			break;
		case AppState::PAUSED:
		case AppState::RUNNING:
			exit = commandUI();
			break;
		default:
			break;
		}
	}
	_TCOUT << _T("O programa fechou!") << _TENDL;
}

int AppUI::loadingUI() {
	_TSTRING fileName;
	_TCOUT << _T("Insere o nome do ficheiro com os utilizadores:");
	_TCOUT.flush();
	std::getline(_TCIN, fileName);

	if (fileName == _T("close"))
		return 1;

	app.addUsers(fileName);
	return 0;
}

int AppUI::commandUI() {
	_TSTRING cmd;

	_TCOUT << "\n\n\t-->";
	_TCOUT.flush();

	std::getline(_TCIN, cmd);

	int err = Command::executeCommand(app, cmd);

	if (err) {
		if (err == CMD_EXIT)
			return 1;
		else
			printError(err);
	}

	return 0;
}


void AppUI::printError(const int err) {
	
}