#pragma once

#include "commands/Command.h"

struct CmdStock : public Command {
protected:
	int function(std::vector<_TSTRING>& args, AppContext& app) {
		if (args.size() == 3) {
			try {
				double t = std::stod(args.at(2));
				if (app.getApp().setCompanyPrice(args.at(1), t)) {
					_TCOUT << _T("Os valores da bolsa da empresa ") << args.at(1) 
							<< _T(" foram atualizados com sucesso para ") << t << _T("!") << _TENDL;
				}
			} catch (CompanyNotFound& e) {
				_TCOUT << _T("Essa empresa n�o existe!") << _TENDL;
				return CMD_INVALID_ARGS;
			} catch (std::invalid_argument& e) {
				_TCOUT << _T("O pre�o das a��es introduzido � inv�lido!") << _TENDL;
				return CMD_INVALID_ARGS;
			} catch (std::out_of_range& e) {
				_TCOUT << _T("O pre�o das a��es introduzido est� fora do intervalo permitido!") << _TENDL;
				return CMD_INVALID_ARGS;
			}
		}
		else {
			_TCOUT << _T("Os argumentos introduzidos n�o s�o v�lidos!\n") <<
				_T("Experimenta \"stock <nome da empresa> <novo pre�o>\"") << _TENDL;
		}
		return CMD_OK;
	}
};