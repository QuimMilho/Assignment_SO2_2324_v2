#pragma once

#include "dynamicLib.h"

#include "ServerData/Request/Request.h"

struct Company {
	Company(const _TSTRING& name, const int n_shares, const double share_price);

	[[nodiscard]] _TSTRING getName() const;

private:
	_TSTRING name;
	int total_shares, available_shares;
	double share_price, total_value;
	std::vector<Request> requests;
};