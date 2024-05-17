#pragma once

#include "dynamicLib.h"

#include "ServerData/Request/Request.h"

struct Company {
	Company(const _TSTRING& name, const int n_shares, const double share_price);

	[[nodiscard]] _TSTRING getName() const;
	[[nodiscard]] double getSharedPrice() const;

	friend Company& operator >> (Company& c, SharedCompany& sc);
	friend _TOSTREAM& operator << (_TOSTREAM& o, Company& c);

private:
	_TSTRING name;
	int total_shares, available_shares;
	double share_price, total_value;
	std::vector<Request> requests;
};
