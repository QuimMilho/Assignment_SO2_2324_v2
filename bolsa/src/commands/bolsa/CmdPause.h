#pragma once

#include "commands/Command.h"

struct CmdPause : public Command {
protected:
	int function(std::vector<_TSTRING>& args, AppContext& app) {
		if (args.size() == 2) {
			try {
				int t = std::stoi(args.at(1));
				if (t < 5) {
					_TCOUT << _T("O valor introduzido deve ser maior ou igual a 5!") << _TENDL;
					return CMD_INVALID_ARGS;
				}
				if (app.pause(t)) {
					_TCOUT << _T("A aplicação foi pausada durante ") << t << _T(" segundos!") << _TENDL;
				} else {
					_TCOUT << _T("A aplicação já está em pausa!") << _TENDL;
				}
			} catch (std::invalid_argument& e) {
				_TCOUT << _T("O número de segundos introduzido é inválido!") << _TENDL;
				return CMD_INVALID_ARGS;
			} catch (std::out_of_range& e) {
				_TCOUT << _T("O número de segundos introduzido está fora do intervalo permitido!") << _TENDL;
				return CMD_INVALID_ARGS;
			}
		} else {
			_TCOUT << _T("Os argumentos introduzidos não são válidos!\n") << 
					_T("Experimenta \"pause <segundos>\"") << _TENDL;
		}
		return CMD_OK;
	}
};