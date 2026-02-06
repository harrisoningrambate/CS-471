// Name: Harrison Ingram-Bate
#include "Blind.h"

Population Blind(std::unique_ptr<vector<uniform_real_distribution<float>>>  distribution_vec, // distribution for each dimension
				 float (*fitness)(const vector<float>&), // fitness function to evaluation
				 size_t pop_size) // number of iterations
{
	// setup
	size_t dimensions = distribution_vec->size();
	Population blind_pop(pop_size, dimensions);
	mt19937 rand_gen(std::chrono::system_clock::now().time_since_epoch().count());

	for (int i = 0; i < pop_size; i++) {
		// generate random vector
		for (int j = 0; j < dimensions; j++) {
			blind_pop.population[i][j] = (*distribution_vec)[j](rand_gen);
		}
		// evaluate fitness
		blind_pop.fitness[i] = fitness(blind_pop.population[i]);
	}

	return blind_pop;
}
