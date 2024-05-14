#pragma once

#include "macros.h"

struct SO2_API Exception : public std::exception {

	Exception() = default;

	virtual _TSTRING what();
};