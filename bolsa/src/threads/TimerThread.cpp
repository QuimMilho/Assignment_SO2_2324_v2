#include "pch/so2pch.h"

#include "TimerThread.h"

DWORD WINAPI TimerThread::function(LPVOID lpParam) {
	LOG_DEBUG("TimerThread criada!");
	TimerThread& data = *(TimerThread*)lpParam;
	AppContext& context = *(AppContext*) data.getData();

	WindowsMutex mutex(APP_MUTEX);

	WindowsSharedMemory sharedMemory(BOARD_SHARED_MEMORY, sizeof(BoardData));
	if (!sharedMemory.create(PAGE_READWRITE)) {
		context.close();
		return -1;
	}

	WindowsTimer updateBoardTimer(10);
	WindowsTimer updateValuesTimer(0.1);
	int i = 0;

	WindowsEvent boardUpdate(BOARD_UPDATE_EVENT, true);
	if (!boardUpdate.create()) {
		context.close();
		return -1;
	}

	while (data.running()) {
		// Every 0.10 seconds
		if (updateBoardTimer.check()) {
			updateBoardTimer.reset();

			if (boardUpdate.triggered()) {
				boardUpdate.reset();
				continue;
			}

			if (context.getState() == AppState::PAUSED) {
				if (context.resume()) {
					_TCOUT << _T("A aplicação já não está em pausa!") << _TENDL;
				}
			} else if (context.getState() == AppState::RUNNING) {
				if (context.updateBoard(sharedMemory)) {
					boardUpdate.set();
				}
			}
		}
		// Every 10.0 seconds
		if (updateValuesTimer.check()) {
			updateValuesTimer.reset();
			// update companies shares
		}
		Sleep(10);
	}

	sharedMemory.unmap();

	return 0;
}

TimerThread * TimerThread::createThread(AppContext& app) {
	return new TimerThread(app);
}

TimerThread::TimerThread(AppContext& app) : WindowsThread(&app) {}

TimerThread::~TimerThread() {}