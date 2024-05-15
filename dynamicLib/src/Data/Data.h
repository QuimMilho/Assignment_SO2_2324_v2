#pragma once

#include "macros.h"
#include "pch/so2pch.h"

struct SO2_API SharedCompany {
	TCHAR nome[32];
	double share_price, total_value;
};