#pragma once

#include "pch/so2pch.h"
#include "dynamicLib.h"
#include "ServerData/ServerData.h"

constexpr int CMD_EXIT = -2;
constexpr int CMD_NOT_FOUND = -1;
constexpr int CMD_OK = 0;
constexpr int CMD_INVALID_ARGS = 1;
constexpr int CMD_ERROR = 2;

struct Command {
	Command() = default;

	static void registerCommands();
	[[nodiscard]] static int executeCommand(AppContext& app, const _TSTRING& cmdStr, const bool cliente = false);

protected:
	[[nodiscard]] virtual int function(std::vector<_TSTRING>& args, AppContext& app) = 0;

private:
	static std::unordered_map<_TSTRING, std::unique_ptr<Command>> bolsaCommands;
	static std::unordered_map<_TSTRING, std::unique_ptr<Command>> clienteCommands;

	static void registerCommand(const _TSTRING& name, Command* cmd, const bool cliente = false);
};
