#pragma once

#include "dynamicLib.h"

#define XDIM 83

struct Console : public WindowsHandle {
	Console();
	virtual ~Console();

	void clear();
	void print(const BoardData& data, const int n);
	void setCursor(const int x, const int y);

private:
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

	void processBoardData(CHAR_INFO* info, const BoardData& data);
	void printInfo(CHAR_INFO* info, const int linha, const TCHAR * nome, const int total_shares, 
			const double share_price, const double total_price);
	void printString(CHAR_INFO* info, const TCHAR * str, const int size, const int x, const int y = 0);

	void printTable(const BoardData& data, const int n);
	void printLast(const BoardData& data, const int n);
};