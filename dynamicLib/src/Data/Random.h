#pragma once

#include "pch/so2pch.h"

#include "macros.h"

struct SO2_API Random {
	Random();
	Random(const int seed);

	[[nodiscard]] int random(const int n);
	[[nodiscard]] int random(const int a, const int b);
	[[nodiscard]] double random();

private:
	std::default_random_engine generator;
	std::uniform_real_distribution<double> dist;
};