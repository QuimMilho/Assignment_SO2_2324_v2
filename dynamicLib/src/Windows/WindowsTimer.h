#pragma once

#include "macros.h"

#define PRECISION_NANO 1000000000
#define PRECISION_MICRO 1000000
#define PRECISION_MILLIS 1000

struct SO2_API WindowsTimer {
	WindowsTimer(const double tps, const long precision = PRECISION_MICRO);

	[[nodiscard]] bool check();
	void reset();

private:
	LARGE_INTEGER frequency, last, now;
	long precision;
	double delta, elapsedTime;
};