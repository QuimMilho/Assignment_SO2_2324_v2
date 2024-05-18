#include "pch/so2pch.h"

#include "Company.h"

Company::Company(const _TSTRING& name, const int n_shares, const double share_price) : name(name),
		total_shares(n_shares), available_shares(n_shares), share_price(share_price), 
		total_value(n_shares * share_price), requests() {}

void Company::setPrice(const double p) {
	share_price = p;
	total_value = p * total_shares;
}

_TSTRING Company::getName() const {
	return name;
}

double Company::getSharedPrice() const {
	return share_price;
}

Company& operator>>(Company& c, SharedCompany& sc) {
	_TSTRCPY_S(sc.nome, MAX_STRING, c.name.c_str());
	sc.share_price = c.share_price;
	sc.total_value = c.total_value;
	sc.total_acoes = c.total_shares;
	return c;
}

_TOSTREAM& operator<<(_TOSTREAM& o, Company& c) {
	TCHAR str[512];
	_TSPRINTF(str, _T("Nome: %32s - Total de ações: %6d - Preço das ações: %.3f - Valor total: %.2f"),
			c.name.c_str(), c.total_shares, c.share_price, c.total_value);
	return o << str;
}

