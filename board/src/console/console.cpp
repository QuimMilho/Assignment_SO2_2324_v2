#include "pch/so2pch.h"

#include "console.h"

Console::Console() : WindowsHandle(NULL) {
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(handle, &consoleInfo);
}

Console::~Console() {

}

void Console::clear() {
	DWORD charsWritten;
	COORD c = { 0, 0 };
	FillConsoleOutputCharacter(handle, _T(' '), consoleInfo.dwSize.X * consoleInfo.dwSize.Y,
			c, & charsWritten);
	FillConsoleOutputAttribute(handle, consoleInfo.wAttributes, consoleInfo.dwSize.X * consoleInfo.dwSize.Y,
			c, & charsWritten);
}

void Console::print(const BoardData& data, const int n) {
	printTable(data, n);
	printLast(data, n);
}

void Console::setCursor(const int x, const int y) {
	COORD c = { x, y };
	SetConsoleCursorPosition(handle, c);
}

void Console::processBoardData(CHAR_INFO* info, const BoardData& data) {
	for (int i = 0; i < 22; i++) {
		for (int h = 0; h < XDIM; h++) {
			int index = i * XDIM + h;
			_TCHAR_INFO_CHAR(index) = _T(' ');
			if (i == 1 || h == 34 || h == 35 || h == 49 || h == 50 || h == 64 || h == 65) {
				info[index].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED |
					(FOREGROUND_BLUE & FOREGROUND_GREEN & FOREGROUND_RED);
			} else {
				info[index].Attributes = (BACKGROUND_BLUE & BACKGROUND_GREEN & BACKGROUND_RED) |
					(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			}
		}
	}

	printString(info, _T("Nome"), 4, 1, 0);
	printString(info, _T("Total ações"), 11, 37, 0);
	printString(info, _T("Preço Ações"), 11, 52, 0);
	printString(info, _T("Valor total"), 11, 67, 0);

	for (int i = 0; i < data.nCompanies; i++) {
		const SharedCompany& c = data.companies[i];
		printInfo(info, i * 2 + 2, c.nome, c.total_acoes, c.share_price, c.total_value);
	}
}

void Console::printInfo(CHAR_INFO* info, const int linha, const TCHAR* nome, const int total_shares, 
		const double share_price, const double total_price) {
	TCHAR buf[64];
	int length = _TSTRLEN(nome);
	printString(info, length ? nome : _T("-"), length ? length : 1, 1, linha);
	printString(info, NumberFormatter::format(buf, 64, total_shares, 11), 11, 37, linha);
	printString(info, NumberFormatter::format(buf, 64, share_price, 6, 3), 10, 53, linha);
	printString(info, NumberFormatter::format(buf, 64, total_price, 12, 2), 15, 67, linha);
}

void Console::printString(CHAR_INFO* info, const TCHAR* str, const int size, const int x, const int y) {
	int index = y * XDIM + x;
	for (int i = 0; i < size; i++) {
		_TCHAR_INFO_CHAR(index + i) = str[i];
	}
}

void Console::printTable(const BoardData& data, const int n) {
	CHAR_INFO info[XDIM * 22];
	COORD pos = { 0, 0 }, size = { XDIM, 2 + n * 2 };
	SMALL_RECT rect = { 0, 0, XDIM, 2 + n * 2 };
	processBoardData(info, data);
	WriteConsoleOutput(handle, info, size, pos, &rect);
}

void Console::printLast(const BoardData& data, const int n) {
	CHAR_INFO info[XDIM * 4];
	for (int i = 0; i < XDIM * 2; i++) {
		int index = i;
		_TCHAR_INFO_CHAR(index) = _T(' ');
		info[index].Attributes = (BACKGROUND_BLUE | (BACKGROUND_GREEN & BACKGROUND_RED)) |
			(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	}
	for (int i = 0; i < XDIM; i++) {
		int index = i + XDIM * 2;
		_TCHAR_INFO_CHAR(index) = _T(' ');
		info[index].Attributes = (BACKGROUND_GREEN | (BACKGROUND_BLUE & BACKGROUND_RED)) |
			(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	}
	for (int i = 0; i < XDIM; i++) {
		int index = i + XDIM * 3;
		_TCHAR_INFO_CHAR(index) = _T(' ');
		info[index].Attributes = (BACKGROUND_RED | (BACKGROUND_BLUE & BACKGROUND_GREEN)) |
			(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	}
	printString(info, _T("Última transação:"), 19, 1);
	const SharedCompany& last = data.last;
	printInfo(info, 1, last.nome, last.total_acoes, last.share_price, last.total_value);

	printString(info, _T("Última Empresa com preço alterado:"), 35, 1, 2);
	printString(info, data.ultimaEmpresa, _TSTRLEN(data.ultimaEmpresa), 36, 2);

	printString(info, _T("Pressione 'Enter' para sair!"), 28, 1, 3);
	COORD pos = { 0, 0 }, size = { XDIM, 4 };
	SMALL_RECT rect = { 0, 2 + n * 2, XDIM, 6 + n * 2 };
	WriteConsoleOutput(handle, info, size, pos, &rect);
}