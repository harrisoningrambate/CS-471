#include <random>
#include "Population.h"

/*
 * global scope mersenne twister random number generator
 * used to generate population data
*/
mt19937 gen(23);

Population::Population(size_t pop_size, size_t dimensions, float dist_low, float dist_high): population(pop_size, vector<float>(dimensions)), fitness(pop_size) {
	uniform_real_distribution<float> distribution(dist_low, dist_high);

	// populates the population matrix with values within the given distribution domain
	for (int i = 0; i < population.size(); i++) {
		for (int j = 0; j < population[i].size(); j++) {
			population[i][j] = distribution(gen);
		}
	}
};
