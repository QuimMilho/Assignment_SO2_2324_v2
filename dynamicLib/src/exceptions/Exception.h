#pragma once

#include "macros.h"

struct SO2_API Exception : public std::exception {

	Exception() = default;

	[[nodiscard]] virtual _TSTRING what() = 0;
};