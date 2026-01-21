#include <random>
#include "Population.h"

/*
 * global scope mersenne twister random number generator
 * used to generate population data
*/
mt19937 gen(23);

Population::Population(size_t pop_size, size_t dimensions) : population(pop_size, vector<float>(dimensions, 0.0f)) {
	uniform_real_distribution<float> distribution(-1.0f, 1.0f);

	for (int i = 0; i < population.size(); i++) {
		for (int j = 0; j < population[i].size(); j++) {
			population[i][j] = distribution(gen);
		}
	}
};
