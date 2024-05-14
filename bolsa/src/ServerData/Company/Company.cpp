#include "pch/so2pch.h"

#include "Company.h"

Company::Company(const _TSTRING& name, const int n_shares, const double share_price) : name(name),
		total_shares(n_shares), available_shares(n_shares), share_price(share_price), 
		total_value(n_shares * share_price), requests() {}

_TSTRING Company::getName() const {
	return name;
}