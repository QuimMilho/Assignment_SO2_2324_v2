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

void Console::print(const BoardData& data) {
	CHAR_INFO info[1496];
	COORD pos = {0, 0}, size = {68, 22};
	SMALL_RECT rect = {0, 0, 68, 22};
	processBoardData(info, data);
	WriteConsoleOutput(handle, info, size, pos, &rect);
}

void Console::setCursor(const int x, const int y) {
	COORD c = { x, y };
	SetConsoleCursorPosition(handle, c);
}

void Console::processBoardData(CHAR_INFO* info, const BoardData& data) {
	for (int i = 0; i < 22; i++) {
		for (int h = 0; h < 68; h++) {
			int index = i * 68 + h;
			_TCHAR_INFO_CHAR(index) = _T(' ');
			if (i == 1 || h == 34 || h == 35 || h == 49 || h == 50) {
				info[index].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED |
					(FOREGROUND_BLUE & FOREGROUND_GREEN & FOREGROUND_RED);
			} else {
				info[index].Attributes = (BACKGROUND_BLUE & BACKGROUND_GREEN & BACKGROUND_RED) |
					(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			}
		}
	}

	printString(info, _T("Nome"), 4, 1, 0);
	printString(info, _T("Preço Ações"), 11, 37, 0);
	printString(info, _T("Valor total"), 11, 52, 0);

	for (int i = 0; i < data.nCompanies; i++) {
		const SharedCompany& c = data.companies[i];
		printInfo(info, i * 2 + 2, c.nome, c.share_price, c.total_value);
	}
}

void Console::printInfo(CHAR_INFO* info, const int linha, const TCHAR* nome, const double share_price, 
		const double total_price) {
	TCHAR buf[64];
	printString(info, nome, _TSTRLEN(nome), 1, linha);
	printString(info, NumberFormatter::format(buf, 64, share_price, 6, 3), 10, 38, linha);
	printString(info, NumberFormatter::format(buf, 64, total_price, 12, 2), 15, 52, linha);
}

void Console::printString(CHAR_INFO* info, const TCHAR* str, const int size, const int x, const int y) {
	int index = y * 68 + x;
	for (int i = 0; i < size; i++) {
		_TCHAR_INFO_CHAR(index + i) = str[i];
	}
}