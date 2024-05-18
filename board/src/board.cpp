#include "pch/so2pch.h"

#include "dynamicLib.h"
#include "console/console.h"
#include "threads/PrintThread.h"

int _tmain(int argc, TCHAR** argv) {
	DEFINE_UNICODE;

	int n, k;

	if (argc != 2) {
		_TCOUT << _T("") << _TENDL;
		return -1;
	}

	try {
		n = std::stoi(argv[1]);
	} catch (std::exception& e) {
		_TCOUT << _T("") << _TENDL;
		return -1;
	}

	if (n <= 0 || n > 10) {
		n = 10;
	}

	BoardData data;

	Console console;
	console.clear();

	HWND consoleWindow = GetConsoleWindow();

	WindowsSharedMemory boardMemory(BOARD_SHARED_MEMORY, sizeof(BoardData));
	if (!boardMemory.open(FILE_MAP_ALL_ACCESS)) {
		LOG_ERRO(_T("Erro a abrir memória partilhada!"));
		return -1;
	};
		 
	WindowsEvent updateEvent(BOARD_UPDATE_EVENT);
	if (!updateEvent.open()) {
		LOG_ERRO(_T("Não foi possível abrir o evento de update!"));
		return 1;
	}

	WindowsEvent appExitEvent(APP_CLOSE_EVENT);
	if (!appExitEvent.open()) {
		LOG_ERRO(_T("Não foi possível abrir o evento de saída do servidor!"));
		return 1;
	}

	bool triggered = false;
	int res;

	boardMemory.read(&data);
	console.clear();
	console.print(data, n);
	console.setCursor(0, 25);

	std::unique_ptr<PrintThread> printThread(PrintThread::createThread());

	while (1) {
		if ((res = updateEvent.wait(0)) == WAIT_OBJECT_0) {
			if (!triggered) {
				boardMemory.read(&data);
				console.print(data, n);
				triggered = true;
			}
		} else if (triggered && res == WAIT_TIMEOUT) {
			triggered = false;
		}

		if (appExitEvent.wait(0) == WAIT_OBJECT_0) {
			_TCOUT << _T("A aplicação bolsa parou de estar em execução!") << _TENDL;
			break;
		}

		if (!printThread->running()) {
			break;
		}

		Sleep(10);
	}

	if (printThread->running()) {
		printThread->terminate();
	}

	boardMemory.unmap();

	return 0;
}