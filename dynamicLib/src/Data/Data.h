#pragma once

#include "macros.h"
#include "pch/so2pch.h"

#define BOARD_SHARED_MEMORY _T("BoardSharedMemory")

#define BOARD_WRITE_MUTEX _T("BoardWriteEvent")
#define BOARD_READ_MUTEX _T("BoardReadEvent")
#define BOARD_UPDATE_EVENT _T("BoardUpdateEvent")
#define APP_CLOSE_EVENT _T("AppCloseEvent")

struct SharedCompany {
	TCHAR nome[MAX_STRING];
	double share_price, total_value;
	int total_acoes;
};

struct BoardData {
	TCHAR ultimaEmpresa[MAX_STRING];
	SharedCompany last;
	SharedCompany companies[10];
	int nCompanies;
};
