#pragma once

#include "commands/Command.h"

struct CmdAddC : public Command {
protected:
	int function(std::vector<_TSTRING>& args, AppContext& app) {
		if (args.size() == 2) {
			int r = app.addCompanies(args.at(1));
			if (r == -1) {
				_TCOUT << _T("A bolsa está atualmente em pausa! Nenhuma empresa foi adicionada!") << _TENDL;
				return CMD_OK;
			} else if (r == -2) {
				_TCOUT << _T("O ficheiro não existe!") << _TENDL;
				return CMD_INVALID_ARGS;
			} else if (r) {
				_TCOUT << _T("Foram lidas ") << r << _T(" empresas a partir do ficheiro ") << args.at(1) 
						<< _TENDL;
				return CMD_OK;
			} else {
				_TCOUT << _T("Nenhuma empresa foi lida a partir do ficheiro ") << args.at(1) << _TENDL;
				return CMD_OK;
			}
		} else if (args.size() == 4) {
			try {
				int total_shares = std::stoi(args.at(2));
				double share_price = std::stod(args.at(3));
				int r = app.addCompanies(args.at(1), total_shares, share_price);
				if (r == -1) {
					_TCOUT << _T("A bolsa está atualmente em pausa! Nenhuma empresa foi adicionada!") << _TENDL;
					return CMD_OK;
				} else if (r) {
					_TCOUT << _T("A empresa ") << args.at(1) << _T(" foi adicionada com sucesso!") << _TENDL;
					return CMD_OK;
				} else {
					LOG_ERRO(_T("A empresa não foi adicionada. Erro: %d - N:%d"), r, app.getApp().nCompanies());
					_TCOUT << _T("A empresa ") << args.at(1) << _T(" não foi adicionada!") << _TENDL;
					return CMD_INVALID_ARGS;
				}
			} catch (std::invalid_argument& e) {
				_TCOUT << _T("Algum dos argumentos introduzidos é inválido!") << _TENDL;
				return CMD_INVALID_ARGS;
			} catch (std::out_of_range& e) {
				_TCOUT << _T("Algum dos argumentos introduzidos está fora do intervalo perimitido!") << _TENDL;
				return CMD_INVALID_ARGS;
			}
		} else {
			_TCOUT << _T("O comando foi mal utilizado!\n") << _T("Deves usar \"addc <nomeficheiro>\" ou\n") 
					<< _T("\"addc <nome empresa> <total de ações> <preço da ação>\"") << _TENDL;
			return CMD_INVALID_ARGS;
		}
		return CMD_OK;
	}
};