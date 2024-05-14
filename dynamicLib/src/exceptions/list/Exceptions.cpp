#include "pch/so2pch.h"

#include "CompanyNotFound.h"
#include "UserNotFound.h"

_TSTRING Exception::what() {
	return _T("Erro padrão!");
};

_TSTRING CompanyNotFound::what() {
	_TSTRINGSTREAM ss;
	ss << _T("Empresa não encontrada! Nome: ") << name << _T(".");
	return ss.str();
}

_TSTRING UserNotFound::what() {
	_TSTRINGSTREAM ss;
	ss << _T("Utilizador não encontrado! Username: ") << name << _T(".");
	return ss.str();
}