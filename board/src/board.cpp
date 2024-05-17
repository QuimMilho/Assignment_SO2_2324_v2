#include "pch/so2pch.h"

#include "dynamicLib.h"
#include "console/console.h"

int _tmain(int argc, TCHAR** argv) {
	DEFINE_UNICODE;
	BoardData data;

	Console console;
	console.clear();

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
	console.print(data);
	console.setCursor(0, 25);

	while (1) {
		if ((res = updateEvent.wait(0)) == WAIT_OBJECT_0) {
			if (!triggered) {
				boardMemory.read(&data);
				console.print(data);
				triggered = true;
			}
		} else if (triggered && res == WAIT_TIMEOUT) {
			triggered = false;
		}

		if (appExitEvent.wait(0) == WAIT_OBJECT_0) {
			break;
		}

		Sleep(10);
	}

	boardMemory.unmap();

	return 0;
}