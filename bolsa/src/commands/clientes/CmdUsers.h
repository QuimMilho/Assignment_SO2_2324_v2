#pragma once

#include "commands/Command.h"

struct CmdUsers : public Command {
protected:
	int function(std::vector<_TSTRING>& args, AppContext& app) {
		int n = app.getApp().nUsers();
		_TCOUT << _T("Há ") << n << _T(" utilizadores registados:") << _TENDL;
		User* usrs = app.getApp().getUsers();
		for (int i = 0; i < n; i++) {
			User& u = usrs[i];
			_TCOUT << u << _TENDL;
		}
		return CMD_OK;
	}
};