#include "pch/so2pch.h"

#include "Command.h"
#include "Commands.h"

std::unordered_map<_TSTRING, std::unique_ptr<Command>> Command::bolsaCommands = {};
std::unordered_map<_TSTRING, std::unique_ptr<Command>> Command::clienteCommands = {};

void Command::registerCommands() {
	// Bolsa
	registerCommand(_T("addc"), new CmdAddC());
	registerCommand(_T("close"), new CmdClose());
	registerCommand(_T("listc"), new CmdListC());
	registerCommand(_T("pause"), new CmdPause());
	registerCommand(_T("stock"), new CmdStock());
	registerCommand(_T("users"), new CmdUsers());

	// Cliente
	registerCommand(_T("balance"), new CmdBalance(), true);
	registerCommand(_T("buy"), new CmdBuy(), true);
	registerCommand(_T("exit"), new CmdExit(), true);
	registerCommand(_T("listc"), new CmdCListC(), true);
	registerCommand(_T("login"), new CmdLogin(), true);
	registerCommand(_T("sell"), new CmdSell(), true);
}

int Command::executeCommand(AppContext& app, const _TSTRING& cmdStr, const bool cliente) {
	_TSTRINGSTREAM ss(cmdStr);
	std::vector<_TSTRING> args;
	_TSTRING temp, cmdName;

	while (ss >> temp)
		args.push_back(temp);

	cmdName = args.at(0);

	std::unordered_map<_TSTRING, std::unique_ptr<Command>>* map;
	if (cliente)
		map = &clienteCommands;
	else 
		map = &bolsaCommands;

	auto cmd = map->find(cmdName);

	if (cmd == map->end()) {
		LOG_ERRO(_T("Comando não encontrado! %s, modo: %s"), cmdName.c_str(), cliente ? 
				_T("Cliente") : _T("Bolsa"));
		return CMD_NOT_FOUND;
	}

	return cmd->second->function(args, app);
}

void Command::registerCommand(const _TSTRING& name, Command* cmd, const bool cliente) {
	std::pair<_TSTRING, Command *> par(name, cmd);
	if (cliente)
		Command::clienteCommands.insert(par);
	else
		Command::bolsaCommands.insert(par);
}