#pragma once

#include "commands/Command.h"

struct CmdUsers : public Command {
protected:
	int function(std::vector<_TSTRING>& args, AppContext& app) {
		return CMD_OK;
	}
};