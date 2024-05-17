#pragma once

#include "commands/Command.h"

struct CmdCListC : public Command {
protected:
	int function(std::vector<_TSTRING>& args, AppContext& app) {
		return CMD_OK;
	}
};