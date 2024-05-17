#include "pch/so2pch.h"

#include "WindowsTimer.h"

WindowsTimer::WindowsTimer(const double tps, const long precision) : delta(precision / tps), precision(precision),
			elapsedTime(0) {
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&now);
	last = now;
}

bool WindowsTimer::check() {
	QueryPerformanceCounter(&now);
	elapsedTime = floor((now.QuadPart - last.QuadPart) / (double)frequency.QuadPart * precision);
	return elapsedTime >= delta;
}

void WindowsTimer::reset() {
	last = now;
}