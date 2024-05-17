#pragma once

#include "commands/Command.h"

struct CmdListC : public Command {
protected:
	int function(std::vector<_TSTRING>& args, AppContext& app) {
		int n = app.getApp().nCompanies();
		if (n == 0) {
			_TCOUT << _T("N�o h� empresas registadas no sistema!") << _TENDL;
			return CMD_OK;
		}
		_TCOUT << _T("H� ") << n << _T(" empresas registadas:") << _TENDL;
		Company* comps = app.getApp().getCompanies();
		for (int i = 0; i < n; i++) {
			Company& c = comps[i];
			_TCOUT << c << _TENDL;
		}
		return CMD_OK;
	}
};