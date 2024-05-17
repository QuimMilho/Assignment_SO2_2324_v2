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
					_TCOUT << _T("A aplica��o foi pausada durante ") << t << _T(" segundos!") << _TENDL;
				} else {
					_TCOUT << _T("A aplica��o j� est� em pausa!") << _TENDL;
				}
			} catch (std::invalid_argument& e) {
				_TCOUT << _T("O n�mero de segundos introduzido � inv�lido!") << _TENDL;
				return CMD_INVALID_ARGS;
			} catch (std::out_of_range& e) {
				_TCOUT << _T("O n�mero de segundos introduzido est� fora do intervalo permitido!") << _TENDL;
				return CMD_INVALID_ARGS;
			}
		} else {
			_TCOUT << _T("Os argumentos introduzidos n�o s�o v�lidos!\n") << 
					_T("Experimenta \"pause <segundos>\"") << _TENDL;
		}
		return CMD_OK;
	}
};