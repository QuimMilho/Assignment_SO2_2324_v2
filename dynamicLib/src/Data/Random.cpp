#include "pch/so2pch.h"

#include "Random.h"

Random::Random() : generator(std::default_random_engine(time(NULL))), 
		dist(std::uniform_real_distribution<double>(0, 1)) {}

Random::Random(const int seed) : generator(std::default_random_engine(seed)),
		dist(std::uniform_real_distribution<double>(0, 1)) {}

double Random::random() {
	return dist(generator);
}

int Random::random(const int n) {
	return (int) floor(random() * n);
}

int Random::random(const int a, const int b) {
	return (int) floor(random() * (b - a) + a);
}