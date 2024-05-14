#pragma once

#include "commands/Command.h"

struct CmdBalance : public Command {
protected:
	int function(std::vector<_TSTRING>& args, AppContext& app) {
		return CMD_OK;
	}
};