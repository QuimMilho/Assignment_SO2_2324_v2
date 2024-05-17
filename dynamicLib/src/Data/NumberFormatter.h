#pragma once

#include "macros.h"

struct SO2_API NumberFormatter {
	static TCHAR* format(TCHAR* str, const int max_size, const double d, const int casasDecimais);
	static TCHAR* format(TCHAR* str, const int max_size, const float d, const int casasDecimais);
	static TCHAR* format(TCHAR* str, const int max_size, const double d, const int dezenas,
			const int casasDecimais);
	static TCHAR* format(TCHAR* str, const int max_size, const float d, const int dezenas,
			const int casasDecimais);
	static TCHAR* format(TCHAR* str, const int max_size, const int d, const int dezenas);
	static TCHAR* format(TCHAR* str, const int max_size, const long d, const int dezenas);
};