#include "pch/so2pch.h"

#include "CompanyNotFound.h"
#include "UserNotFound.h"

_TSTRING Exception::what() {
	return _T("Erro padr�o!");
};

_TSTRING CompanyNotFound::what() {
	_TSTRINGSTREAM ss;
	ss << _T("Empresa n�o encontrada! Nome: ") << name << _T(".");
	return ss.str();
}

_TSTRING UserNotFound::what() {
	_TSTRINGSTREAM ss;
	ss << _T("Utilizador n�o encontrado! Username: ") << name << _T(".");
	return ss.str();
}