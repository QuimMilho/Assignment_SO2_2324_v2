#include "pch/so2pch.h"

#include "AppUI.h"
#include "commands/Command.h"

AppUI::AppUI(AppContext& app) : app(app), appMutex(WindowsMutex(APP_ACCESS_MUTEX)) {}

void AppUI::start() {
	int exit = 0;
	WindowsEvent exitEvent(APP_CLOSE_EVENT, true);
	if (!exitEvent.create()) {
		LOG_ERRO(_T("Erro ao criar evento de saída!"));
		return;
	}
	while (!exit && app.isRunning()) {
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
	app.close();
	exitEvent.set();
	Sleep(100);
	exitEvent.reset();
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

	// STACK OVERFLOW -> https://stackoverflow.com/questions/19955617/win32-read-from-stdin-with-timeout

	DWORD fdwMode, fdwOldMode;

	HANDLE stdinHandle = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(stdinHandle, &fdwOldMode);
	// disable mouse and window input
	fdwMode = fdwOldMode ^ ENABLE_MOUSE_INPUT ^ ENABLE_WINDOW_INPUT;
	SetConsoleMode(stdinHandle, fdwMode);
	// flush to remove existing events
	FlushConsoleInputBuffer(stdinHandle);
	
	// END STACK OVERFLOW

	while (WaitForSingleObject(stdinHandle, 100) == WAIT_TIMEOUT) {
		if (!app.isRunning()) {
			SetConsoleMode(stdinHandle, fdwOldMode);
			return CMD_EXIT;
		}
	}

	std::getline(_TCIN, cmd);

	SetConsoleMode(stdinHandle, fdwOldMode);

	int err;

	if ((err = appMutex.wait(1000)) != WAIT_OBJECT_0) {
		LOG_ERRO(_T("Não foi possível desbloquear a aplicação! Erro: %d"), err);
		return 1;
	}

	err = Command::executeCommand(app, cmd);

	appMutex.release();

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